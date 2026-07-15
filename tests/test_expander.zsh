#!/usr/bin/env zsh

###############################################################################
# minishell expander tests
# Version: v1-expander-argv
#
# Test cases source: tests/posix_expander_test_cases.md
#
# Usage from minishell/ project root:
#   tests/test_expander.zsh [path/to/minishell] [id-prefix-filter]
#
# Examples:
#   tests/test_expander.zsh                 # run everything
#   tests/test_expander.zsh minishell 3.    # only field-splitting section
#   tests/test_expander.zsh minishell 5.1   # only ids starting with 5.1
#
# Default tested binary:
#   ./minishell
#
# Logs:
#   tests/logs/test_expander.N/   (one log per test: script + raw output)
#
# Fixtures:
#   tests/fixtures/test_expander/ (test_exec binary + glob trees; cwd of runs)
#
# How it works:
#   Each test pipes a small script (setup + command) into a fresh minishell
#   whose cwd is the fixture dir. tests/test_exec.c prints argv as
#   "[TEST] argv[i] => [value]" lines; the harness parses every exec'd argv
#   block (multi-line values supported) and compares against the expectation.
#
# On failure it prints: section, input script, expected argv, actual argv.
# "unspecified POSIX" rows of the md are intentionally not tested.
###############################################################################

emulate -R zsh
setopt NO_NOMATCH

SCRIPT_DIR="${0:A:h}"
PROJECT_ROOT="${SCRIPT_DIR:h}"

MINISHELL="${1:-./minishell}"
if [[ "$MINISHELL" != */* ]]; then
	MINISHELL="./$MINISHELL"
fi
MINISHELL_ABS="${MINISHELL:A}"
FILTER="${2:-}"

BLUE=$'\033[0;34m'
GREEN=$'\033[0;32m'
RED=$'\033[0;31m'
YELLOW=$'\033[0;33m'
GRAY=$'\033[0;90m'
NC=$'\033[0m'
GREY=$'\033[0;90m'

LOG_ROOT="${SCRIPT_DIR}/logs"
LOG_DIR=""
WORK_DIR="${SCRIPT_DIR}/fixtures/test_expander"

TOTAL=0
FAILED=0
SKIPPED=0

CURRENT_ID=""
CURRENT_SECTION=""
CURRENT_SCRIPT=""
CURRENT_LABEL=""
CURRENT_LOG=""
OUTPUT=""
RET=0
CASE_FAILED=0
CASE_DETAILS=()
typeset -a BLOCKS

###############################################################################
# Infrastructure
###############################################################################

check_program_exists()
{
	local program="$1"

	if [ ! -f "$program" ]; then
		echo -e "${RED}✖ Error: $program not found${NC}"
		exit 1
	fi
	if [ ! -x "$program" ]; then
		echo -e "${RED}✖ Error: $program is not executable${NC}"
		exit 1
	fi
}

setup_logs()
{
	local n=1

	mkdir -p "$LOG_ROOT" || exit 1
	while [ -e "${LOG_ROOT}/test_expander.${n}" ]; do
		n=$((n + 1))
	done
	LOG_DIR="${LOG_ROOT}/test_expander.${n}"
	mkdir -p "$LOG_DIR" || exit 1
}

setup_fixtures()
{
	rm -rf "$WORK_DIR"
	mkdir -p "$WORK_DIR" || exit 1

	cc "${SCRIPT_DIR}/test_exec.c" -o "${WORK_DIR}/test_exec" || {
		echo -e "${RED}✖ Error: cannot compile tests/test_exec.c${NC}"
		exit 1
	}

	# --- Section 2: pathname expansion tree (md setup) ---
	mkdir -p "$WORK_DIR"/g/base "$WORK_DIR"/g/tree/dir/sub \
		"$WORK_DIR"/g/tree/empty "$WORK_DIR"/g/lit

	local f
	for f in 1 10 2 a aa ab ac b ba file.c file.h main.c main.o notes.txt \
		.a .hidden; do
		: > "$WORK_DIR/g/base/$f"
	done
	: > "$WORK_DIR/g/tree/dir/x"
	: > "$WORK_DIR/g/tree/dir/y.c"
	: > "$WORK_DIR/g/tree/dir/.z"
	: > "$WORK_DIR/g/tree/dir/sub/deep"
	: > "$WORK_DIR/g/lit/star*name"
	: > "$WORK_DIR/g/lit/quest?name"
	: > "$WORK_DIR/g/lit/brack[abc]"
	: > "$WORK_DIR/g/lit/normal"

	# --- Section 3.11: field splitting + glob interaction ---
	mkdir -p "$WORK_DIR/fs_glob"
	: > "$WORK_DIR/fs_glob/a.c"
	: > "$WORK_DIR/fs_glob/b.c"
	: > "$WORK_DIR/fs_glob/a.h"

	# --- Section 5: dollar-single-quote glob interaction ---
	mkdir -p "$WORK_DIR/dsq"
	: > "$WORK_DIR/dsq/a.c"
	: > "$WORK_DIR/dsq/b.c"
}

section()
{
	echo ""
	echo -e "${GREY}--- $1 ---${NC}\n"
}

skip_by_filter()
{
	[[ -n "$FILTER" && "$1" != "$FILTER"* ]]
}

###############################################################################
# Core: run a script in minishell, parse test_exec argv blocks
###############################################################################

run_case()
{
	CURRENT_ID="$1"
	CURRENT_SECTION="$2"
	CURRENT_SCRIPT="$3"
	CURRENT_LABEL="$4"

	CASE_FAILED=0
	CASE_DETAILS=()
	CURRENT_LOG="${LOG_DIR}/test_${CURRENT_ID//[^A-Za-z0-9._-]/_}.log"

	local raw
	raw="$(printf '%s\n' "$CURRENT_SCRIPT" \
		| ( cd "$WORK_DIR" && LC_ALL=C "$MINISHELL_ABS" ) 2>&1)"
	RET=$?

	{
		printf '### SCRIPT ###\n%s\n\n### RET ###\n%d\n\n### OUTPUT ###\n%s\n' \
			"$CURRENT_SCRIPT" "$RET" "$raw"
	} > "$CURRENT_LOG"

	OUTPUT="$(printf '%s' "$raw" | sed -e $'s/\x1b\\[[0-9;]*m//g')"
	parse_blocks
}

# Extract every exec'd argv as one BLOCKS entry (values joined by \x1f).
# A value may span several lines (embedded newlines); continuation lines are
# the only non-"[TEST] " lines that can appear inside an argv block.
parse_blocks()
{
	BLOCKS=()
	local -a cur=()
	local line entry=""
	local have_entry=0 in_block=0

	while IFS= read -r line || [[ -n "$line" ]]; do
		if [[ "$line" == "[TEST] argv["*"] => ["* ]]; then
			if (( have_entry )); then
				cur+=("${entry%\]}")
				have_entry=0
			fi
			if [[ "$line" == "[TEST] argv[0] => ["* ]]; then
				if (( in_block )); then
					BLOCKS+=("${(pj:\x1f:)cur}")
				fi
				cur=()
				in_block=1
			fi
			entry="${line#*"=> ["}"
			have_entry=1
		elif [[ "$line" == "[TEST] "* ]]; then
			if (( have_entry )); then
				cur+=("${entry%\]}")
				have_entry=0
			fi
			if (( in_block )); then
				BLOCKS+=("${(pj:\x1f:)cur}")
				in_block=0
				cur=()
			fi
		else
			if (( have_entry )); then
				entry+=$'\n'"$line"
			fi
		fi
	done <<< "$OUTPUT"

	if (( have_entry )); then
		cur+=("${entry%\]}")
	fi
	if (( in_block )); then
		BLOCKS+=("${(pj:\x1f:)cur}")
	fi
}

###############################################################################
# Expectations
###############################################################################

fail_current()
{
	CASE_FAILED=1
	CASE_DETAILS+=("$1")
}

render_joined_argv()
{
	local joined="$1"
	local -a items=("${(@ps:\x1f:)joined}")
	local out="" e

	for e in "${items[@]}"; do
		out+="${out:+, }${(q+)e}"
	done
	printf '[%s]' "$out"
}

expect_exec_count()
{
	local n="$1"

	if (( ${#BLOCKS} != n )); then
		fail_current "exec count: expected $n, got ${#BLOCKS}"
		local i
		for (( i = 1; i <= ${#BLOCKS}; i++ )); do
			fail_current "actual exec #$i : $(render_joined_argv "${BLOCKS[$i]}")"
		done
	fi
}

expect_argv_block()
{
	local bi="$1"
	shift
	local -a exp=("$@")
	local exp_j="${(pj:\x1f:)exp}"

	if (( bi > ${#BLOCKS} )); then
		fail_current "expected : $(render_joined_argv "$exp_j")"
		fail_current "actual   : (no exec #$bi)"
		return
	fi
	if [[ "${BLOCKS[$bi]}" != "$exp_j" ]]; then
		fail_current "expected : $(render_joined_argv "$exp_j")"
		fail_current "actual   : $(render_joined_argv "${BLOCKS[$bi]}")"
	fi
}

expect_status()
{
	local expected="$1"

	if [ "$RET" -ne "$expected" ]; then
		fail_current "status: expected $expected, got $RET"
	fi
}

expect_status_nonzero()
{
	if [ "$RET" -eq 0 ]; then
		fail_current "status: expected non-zero, got 0"
	fi
}

expect_no_exec()
{
	if (( ${#BLOCKS} != 0 )); then
		fail_current "expected : no command executed"
		local i
		for (( i = 1; i <= ${#BLOCKS}; i++ )); do
			fail_current "actual exec #$i : $(render_joined_argv "${BLOCKS[$i]}")"
		done
	fi
}

expect_output_contains()
{
	local needle="$1"

	if [[ "$OUTPUT" != *"$needle"* ]]; then
		fail_current "stderr: expected diagnostic containing '${needle}'"
	fi
}

###############################################################################
# Reporting
###############################################################################

finish_case()
{
	TOTAL=$((TOTAL + 1))

	if [ "$CASE_FAILED" -eq 0 ]; then
		printf "${GREEN}✔${NC} [%s] ${BLUE}%s${NC}\n" "$CURRENT_ID" "$CURRENT_LABEL"
		return 0
	fi

	FAILED=$((FAILED + 1))
	printf "${RED}✖${NC} [%s] ${BLUE}%s${NC}\n" "$CURRENT_ID" "$CURRENT_LABEL"
	printf "      ${GRAY}section${NC}  : %s\n" "$CURRENT_SECTION"
	local first=1 line
	while IFS= read -r line; do
		if [ "$first" -eq 1 ]; then
			printf "      ${GRAY}input${NC}    : %s\n" "$line"
			first=0
		else
			printf "               : %s\n" "$line"
		fi
	done <<< "$CURRENT_SCRIPT"
	local detail
	for detail in "${CASE_DETAILS[@]}"; do
		printf "      ${RED}%s${NC}\n" "$detail"
	done
	printf "      ${GRAY}log${NC}      : %s\n" "$CURRENT_LOG"
	return 1
}

skip_case()
{
	local id="$1" label="$2" reason="$3"

	SKIPPED=$((SKIPPED + 1))
	printf "${YELLOW}○${NC} [%s] ${BLUE}%s${NC} ${GRAY}skipped: %s${NC}\n" \
		"$id" "$label" "$reason"
}

###############################################################################
# Test wrappers
###############################################################################

# tc ID SECTION SETUP COMMAND EXPECTED_ARGV...
# One exec expected; argv compared exactly.
tc()
{
	local id="$1" sec="$2" setup="$3" cmd="$4"
	shift 4

	skip_by_filter "$id" && return 0
	local script="$cmd"
	[[ -n "$setup" ]] && script="$setup"$'\n'"$cmd"
	run_case "$id" "$sec" "$script" "${cmd%%$'\n'*}"
	expect_exec_count 1
	if (( ${#BLOCKS} >= 1 )); then
		expect_argv_block 1 "$@"
	fi
	finish_case
}

# tc_multi ID SECTION SETUP COMMAND -- argv... -- argv...
# N execs expected, each block compared in order.
tc_multi()
{
	local id="$1" sec="$2" setup="$3" cmd="$4"
	shift 4

	skip_by_filter "$id" && return 0
	local script="$cmd"
	[[ -n "$setup" ]] && script="$setup"$'\n'"$cmd"
	run_case "$id" "$sec" "$script" "${cmd%%$'\n'*} (+)"

	local -a groups=()
	local -a cur=()
	local arg
	for arg in "$@"; do
		if [[ "$arg" == "--" ]]; then
			if (( ${#cur} > 0 )); then
				groups+=("${(pj:\x1f:)cur}")
				cur=()
			fi
		else
			cur+=("$arg")
		fi
	done
	if (( ${#cur} > 0 )); then
		groups+=("${(pj:\x1f:)cur}")
	fi

	expect_exec_count ${#groups}
	local i
	for (( i = 1; i <= ${#groups}; i++ )); do
		if (( i <= ${#BLOCKS} )); then
			expect_argv_block $i "${(@ps:\x1f:)groups[$i]}"
		fi
	done
	finish_case
}

# tc_status ID SECTION SETUP COMMAND STATUS
# No exec expected + exact exit status (command not found / not executable).
tc_status()
{
	local id="$1" sec="$2" setup="$3" cmd="$4" st="$5"

	skip_by_filter "$id" && return 0
	local script="$cmd"
	[[ -n "$setup" ]] && script="$setup"$'\n'"$cmd"
	run_case "$id" "$sec" "$script" "${cmd%%$'\n'*}"
	expect_no_exec
	expect_status "$st"
	finish_case
}

# tc_err ID SECTION SETUP COMMAND NEEDLE
# ${...?word} style: no exec, non-zero status, diagnostic on stderr.
tc_err()
{
	local id="$1" sec="$2" setup="$3" cmd="$4" needle="$5"

	skip_by_filter "$id" && return 0
	local script="$cmd"
	[[ -n "$setup" ]] && script="$setup"$'\n'"$cmd"
	run_case "$id" "$sec" "$script" "${cmd%%$'\n'*}"
	expect_no_exec
	expect_status_nonzero
	expect_output_contains "$needle"
	finish_case
}

###############################################################################
# 1. Parameter Expansion
###############################################################################

run_param_tests()
{
	section "1. PARAMETER EXPANSION"

	local SEC="1. Parameter Expansion"
	local S1
	S1="$(cat <<'EOF'
unset IFS
unset U
A='a b'
B='c  d'
EMPTY=
CMD=./test_exec
CMD_SPLIT='./test_exec from_var'
EOF
)"

	tc 1.01 "$SEC" "$S1" './test_exec $A'                ./test_exec a b
	tc 1.02 "$SEC" "$S1" './test_exec "$A"'              ./test_exec 'a b'
	tc 1.03 "$SEC" "$S1" './test_exec $B'                ./test_exec c d
	tc 1.04 "$SEC" "$S1" './test_exec "$B"'              ./test_exec 'c  d'
	tc 1.05 "$SEC" "$S1" './test_exec before $U after'   ./test_exec before after
	tc 1.06 "$SEC" "$S1" './test_exec before "$U" after' ./test_exec before '' after
	tc 1.07 "$SEC" "$S1" './test_exec before $EMPTY after' ./test_exec before after
	tc 1.08 "$SEC" "$S1" './test_exec before "$EMPTY" after' ./test_exec before '' after
	tc 1.09 "$SEC" "$S1" './test_exec pre${A}post'       ./test_exec prea bpost
	tc 1.10 "$SEC" "$S1" './test_exec pre"$A"post'       ./test_exec 'prea bpost'
	tc 1.11 "$SEC" "$S1" './test_exec pre${EMPTY}post'   ./test_exec prepost
	tc 1.12 "$SEC" "$S1" './test_exec pre"$EMPTY"post'   ./test_exec prepost
	tc 1.13 "$SEC" "$S1" '$CMD ok'                       ./test_exec ok
	tc 1.14 "$SEC" "$S1" '"$CMD" ok'                     ./test_exec ok
	tc 1.15 "$SEC" "$S1" '$U ./test_exec ok'             ./test_exec ok
	tc_status 1.16 "$SEC" "$S1" '"$U" ./test_exec ok'    127
	tc 1.17 "$SEC" "$S1" '$CMD_SPLIT end'                ./test_exec from_var end
	tc_status 1.18 "$SEC" "$S1" '"$CMD_SPLIT" end'       127
	tc 1.19 "$SEC" "$S1" './test_exec ${U:-fallback}'    ./test_exec fallback
	tc 1.20 "$SEC" "$S1" './test_exec ${EMPTY:-fallback}' ./test_exec fallback
	tc 1.21 "$SEC" "$S1" './test_exec ${U-fallback}'     ./test_exec fallback
	tc 1.22 "$SEC" "$S1" './test_exec before ${EMPTY-fallback} after' \
		./test_exec before after
	tc 1.23 "$SEC" "$S1" './test_exec before "${EMPTY-fallback}" after' \
		./test_exec before '' after
	tc 1.24 "$SEC" "$S1" './test_exec ${U:-"$A"}'        ./test_exec 'a b'
	tc 1.25 "$SEC" "$S1" './test_exec ${A:+alt}'         ./test_exec alt
	tc 1.26 "$SEC" "$S1" './test_exec before ${EMPTY:+alt} after' \
		./test_exec before after
	tc 1.27 "$SEC" "$S1" './test_exec ${EMPTY+alt}'      ./test_exec alt
	tc 1.28 "$SEC" "$S1" './test_exec before ${U+alt} after' \
		./test_exec before after
	tc 1.29 "$SEC" "$S1" './test_exec before "${U+alt}" after' \
		./test_exec before '' after

	local SECM="1. Parameter Expansion — multi-command"
	tc_multi 1.M1 "$SECM" 'unset NEW1' \
		$'./test_exec "${NEW1:=default}"\n./test_exec "$NEW1"' \
		-- ./test_exec default -- ./test_exec default
	tc_multi 1.M2 "$SECM" 'NEW2=' \
		$'./test_exec "${NEW2:=default}"\n./test_exec "$NEW2"' \
		-- ./test_exec default -- ./test_exec default
	tc_multi 1.M3 "$SECM" 'NEW3=' \
		$'./test_exec before "${NEW3=default}" after\n./test_exec before "$NEW3" after' \
		-- ./test_exec before '' after -- ./test_exec before '' after
	tc_err 1.M4 "$SECM" 'unset U' \
		'./test_exec before ${U:?missing} after' missing
	tc_err 1.M5 "$SECM" 'EMPTY=' \
		'./test_exec before ${EMPTY:?missing} after' missing
	tc 1.M6 "$SECM" 'EMPTY=' \
		'./test_exec before "${EMPTY?missing}" after' \
		./test_exec before '' after

	local SECA="1. Parameter Expansion — assignment context"
	tc 1.A1 "$SECA" "$S1" $'C=$A\n./test_exec "$C"'      ./test_exec 'a b'
	tc 1.A2 "$SECA" "$S1" './test_exec C=$A'             ./test_exec 'C=a' b
	tc 1.A3 "$SECA" "$S1" $'unset D\nexport D=$A\n./test_exec "$D"' \
		./test_exec 'a b'
	tc 1.A4 "$SECA" "$S1" $'unset R\nreadonly R=$A\n./test_exec "$R"' \
		./test_exec 'a b'

	local SECT="1. Parameter Expansion — pièges"
	tc 1.T1 "$SECT" "$S1" './test_exec X${A}Y${B}Z'      ./test_exec Xa bYc dZ
	tc 1.T2 "$SECT" "$S1" './test_exec X"$A"Y"$B"Z'      ./test_exec 'Xa bYc  dZ'
	tc 1.T3 "$SECT" "$S1" './test_exec X"$A"Y${B}Z'      ./test_exec 'Xa bYc' dZ
	tc 1.T4 "$SECT" "$S1"$'\nunset DEF' './test_exec "${DEF:-$A}"' \
		./test_exec 'a b'
	tc 1.T5 "$SECT" "$S1"$'\nunset DEF' './test_exec ${DEF:-$A}' \
		./test_exec a b
	tc 1.T6 "$SECT" "$S1"$'\nunset U1\nunset U2' '$U1 $U2 ./test_exec ok' \
		./test_exec ok

	local SECO="1. Parameter Expansion — operator edge cases"
	tc 1.E1 "$SECO" "$S1" './test_exec before ${U:-} after' \
		./test_exec before after
	tc 1.E2 "$SECO" "$S1" './test_exec before "${U:-}" after' \
		./test_exec before '' after
	tc 1.E3 "$SECO" "$S1" "./test_exec \${U:-'a b'}"    ./test_exec 'a b'
	tc 1.E4 "$SECO" "$S1" './test_exec "${U:-a b}"'     ./test_exec 'a b'
	tc 1.E5 "$SECO" "$S1"$'\nunset U2' './test_exec ${U:-${U2:-nested}}' \
		./test_exec nested
	tc 1.E6 "$SECO" "$S1" './test_exec ${A:+$A}'        ./test_exec a b
	tc 1.E7 "$SECO" "$S1" './test_exec "${A:+$A}"'      ./test_exec 'a b'
	tc 1.E8 "$SECO" "$S1" './test_exec ${A-fallback}'   ./test_exec a b
	tc_multi 1.E9 "$SECO" 'unset NEWA' \
		$'./test_exec ${NEWA:=a b}\n./test_exec "$NEWA"' \
		-- ./test_exec a b -- ./test_exec 'a b'
}

###############################################################################
# 2. Pathname Expansion
###############################################################################

run_pathname_tests()
{
	section "2. PATHNAME EXPANSION"

	local SEC="2. Pathname Expansion — *"
	tc 2.S1 "$SEC" '' './test_exec g/base/*' \
		./test_exec g/base/1 g/base/10 g/base/2 g/base/a g/base/aa \
		g/base/ab g/base/ac g/base/b g/base/ba g/base/file.c g/base/file.h \
		g/base/main.c g/base/main.o g/base/notes.txt
	tc 2.S2 "$SEC" '' './test_exec g/base/a*' \
		./test_exec g/base/a g/base/aa g/base/ab g/base/ac
	tc 2.S3 "$SEC" '' './test_exec g/base/*.c' \
		./test_exec g/base/file.c g/base/main.c
	tc 2.S4 "$SEC" '' './test_exec g/base/*o' \
		./test_exec g/base/main.o
	tc 2.S5 "$SEC" '' './test_exec g/base/*.*' \
		./test_exec g/base/file.c g/base/file.h g/base/main.c g/base/main.o \
		g/base/notes.txt

	SEC="2. Pathname Expansion — ?"
	tc 2.Q1 "$SEC" '' './test_exec g/base/?' \
		./test_exec g/base/1 g/base/2 g/base/a g/base/b
	tc 2.Q2 "$SEC" '' './test_exec g/base/??' \
		./test_exec g/base/10 g/base/aa g/base/ab g/base/ac g/base/ba
	tc 2.Q3 "$SEC" '' './test_exec g/base/a?' \
		./test_exec g/base/aa g/base/ab g/base/ac
	tc 2.Q4 "$SEC" '' './test_exec g/base/*.?' \
		./test_exec g/base/file.c g/base/file.h g/base/main.c g/base/main.o

	SEC="2. Pathname Expansion — bracket expressions"
	tc 2.B1 "$SEC" '' './test_exec g/base/[ab]' \
		./test_exec g/base/a g/base/b
	tc 2.B2 "$SEC" '' './test_exec g/base/a[abc]' \
		./test_exec g/base/aa g/base/ab g/base/ac
	tc 2.B3 "$SEC" '' './test_exec g/base/[a-b]' \
		./test_exec g/base/a g/base/b
	tc 2.B4 "$SEC" '' './test_exec g/base/[0-9]' \
		./test_exec g/base/1 g/base/2
	tc 2.B5 "$SEC" '' './test_exec g/base/[!ab]' \
		./test_exec g/base/1 g/base/2
	tc 2.B6 "$SEC" '' './test_exec g/base/a[!a]' \
		./test_exec g/base/ab g/base/ac

	SEC="2. Pathname Expansion — no match keeps pattern"
	tc 2.N1 "$SEC" '' './test_exec g/base/no_match_*' \
		./test_exec 'g/base/no_match_*'
	tc 2.N2 "$SEC" '' './test_exec g/base/z[abc]' \
		./test_exec 'g/base/z[abc]'
	tc 2.N3 "$SEC" '' './test_exec g/base/???' \
		./test_exec 'g/base/???'

	SEC="2. Pathname Expansion — dotfiles"
	tc 2.D1 "$SEC" '' './test_exec g/base/.*' \
		./test_exec g/base/.a g/base/.hidden
	tc 2.D2 "$SEC" '' './test_exec g/base/.?' \
		./test_exec g/base/.a

	SEC="2. Pathname Expansion — patterns do not cross /"
	tc 2.SL1 "$SEC" '' './test_exec g/tree/*' \
		./test_exec g/tree/dir g/tree/empty
	tc 2.SL2 "$SEC" '' './test_exec g/tree/*/*' \
		./test_exec g/tree/dir/sub g/tree/dir/x g/tree/dir/y.c
	tc 2.SL3 "$SEC" '' './test_exec g/tree/*/*/*' \
		./test_exec g/tree/dir/sub/deep
	tc 2.SL4 "$SEC" '' './test_exec g/tree/dir/.*' \
		./test_exec g/tree/dir/.z

	SEC="2. Pathname Expansion — quotes/escapes disable metachars"
	tc 2.QT1 "$SEC" '' './test_exec "g/base/*"'   ./test_exec 'g/base/*'
	tc 2.QT2 "$SEC" '' "./test_exec 'g/base/?'"   ./test_exec 'g/base/?'
	tc 2.QT3 "$SEC" '' './test_exec "g/base/[ab]"' ./test_exec 'g/base/[ab]'
	tc 2.QT4 "$SEC" '' './test_exec g/base/"a"*' \
		./test_exec g/base/a g/base/aa g/base/ab g/base/ac
	tc 2.QT5 "$SEC" '' './test_exec g/base/\*'    ./test_exec 'g/base/*'

	SEC="2. Pathname Expansion — filenames containing glob chars"
	tc 2.L1 "$SEC" '' './test_exec g/lit/*' \
		./test_exec 'g/lit/brack[abc]' g/lit/normal 'g/lit/quest?name' \
		'g/lit/star*name'
	tc 2.L2 "$SEC" '' "./test_exec 'g/lit/star*name'" \
		./test_exec 'g/lit/star*name'
	tc 2.L3 "$SEC" '' './test_exec g/lit/star*' \
		./test_exec 'g/lit/star*name'
	tc 2.L4 "$SEC" '' './test_exec g/lit/quest?name' \
		./test_exec 'g/lit/quest?name'
	tc 2.L5 "$SEC" '' './test_exec g/lit/brack[abc]' \
		./test_exec 'g/lit/brack[abc]'
	tc 2.L6 "$SEC" '' "./test_exec 'g/lit/brack[abc]'" \
		./test_exec 'g/lit/brack[abc]'

	SEC="2. Pathname Expansion — after parameter expansion"
	tc 2.P1 "$SEC" "P='g/base/*.c'" './test_exec $P' \
		./test_exec g/base/file.c g/base/main.c
	tc 2.P2 "$SEC" "P='g/base/*.c'" './test_exec "$P"' \
		./test_exec 'g/base/*.c'
	tc 2.P3 "$SEC" 'EXT=c' './test_exec g/base/*.$EXT' \
		./test_exec g/base/file.c g/base/main.c
	tc 2.P4 "$SEC" 'EXT=c' './test_exec g/base/*."$EXT"' \
		./test_exec g/base/file.c g/base/main.c
	tc 2.P5 "$SEC" "P='g/base/*.c g/base/*.h'" './test_exec $P' \
		./test_exec g/base/file.c g/base/main.c g/base/file.h

	SEC="2. Pathname Expansion — assignment context"
	tc 2.AS1 "$SEC" 'unset GLOB' \
		$'GLOB=g/base/*.c\n./test_exec "$GLOB"' \
		./test_exec 'g/base/*.c'
	tc 2.AS2 "$SEC" 'unset GLOB' \
		'GLOB=g/base/*.c ./test_exec "$GLOB"' \
		./test_exec ''
	tc 2.AS3 "$SEC" 'unset GLOB' \
		$'export GLOB=g/base/*.c\n./test_exec "$GLOB"' \
		./test_exec 'g/base/*.c'

	SEC="2. Pathname Expansion — command-name position"
	tc 2.C1 "$SEC" '' './test_exec g/base/a' ./test_exec g/base/a
	tc_status 2.C2 "$SEC" '' 'g/base/no_match_*' 127
	tc_status 2.C3 "$SEC" '' 'g/base/a' 126
}

###############################################################################
# 3. Field Splitting
###############################################################################

run_field_splitting_tests()
{
	section "3. FIELD SPLITTING"

	local SEC="3.1 default IFS: whitespace splitting"
	local S31
	S31="$(cat <<'EOF'
unset IFS
X='  a  b  '
Y='a b c'
EMPTY=
UNSET_ME=
unset UNSET_ME
EOF
)"
	tc 3.1.1 "$SEC" "$S31" './test_exec $X'   ./test_exec a b
	tc 3.1.2 "$SEC" "$S31" './test_exec $Y'   ./test_exec a b c
	tc 3.1.3 "$SEC" "$S31" './test_exec "$X"' ./test_exec '  a  b  '
	tc 3.1.4 "$SEC" "$S31" './test_exec before $UNSET_ME after' \
		./test_exec before after
	tc 3.1.5 "$SEC" "$S31" './test_exec before "$UNSET_ME" after' \
		./test_exec before '' after
	tc 3.1.6 "$SEC" "$S31" './test_exec before $EMPTY after' \
		./test_exec before after
	tc 3.1.7 "$SEC" "$S31" './test_exec before "$EMPTY" after' \
		./test_exec before '' after

	SEC="3.2 empty IFS: no field splitting"
	local S32
	S32="$(cat <<'EOF'
IFS=
X='  a  b  '
Y='a:b:c'
EOF
)"
	tc 3.2.1 "$SEC" "$S32" './test_exec $X' ./test_exec '  a  b  '
	tc 3.2.2 "$SEC" "$S32" './test_exec $Y' ./test_exec 'a:b:c'
	tc 3.2.3 "$SEC" "$S32"$'\nunset U' './test_exec before $U after' \
		./test_exec before after

	SEC="3.3 IFS=: non-whitespace separator"
	local S33
	S33="$(cat <<'EOF'
IFS=:
X='a:b:c'
Y='a::b:'
Z=':a::b:'
ONLY=':'
DOUBLE='::'
EOF
)"
	tc 3.3.1 "$SEC" "$S33" './test_exec $X'      ./test_exec a b c
	tc 3.3.2 "$SEC" "$S33" './test_exec $Y'      ./test_exec a '' b
	tc 3.3.3 "$SEC" "$S33" './test_exec $Z'      ./test_exec '' a '' b
	tc 3.3.4 "$SEC" "$S33" './test_exec $ONLY'   ./test_exec ''
	tc 3.3.5 "$SEC" "$S33" './test_exec $DOUBLE' ./test_exec '' ''
	tc 3.3.6 "$SEC" "$S33" './test_exec "$Z"'    ./test_exec ':a::b:'

	SEC="3.4 IFS=' ,' whitespace + non-whitespace"
	local S34
	S34="$(cat <<'EOF'
IFS=' ,'
X=' a , b ,, c , '
Y=',a,,b,'
Z='  ,  a  ,  b  '
EOF
)"
	tc 3.4.1 "$SEC" "$S34" './test_exec $X' ./test_exec a b '' c
	tc 3.4.2 "$SEC" "$S34" './test_exec $Y' ./test_exec '' a '' b
	tc 3.4.3 "$SEC" "$S34" './test_exec $Z' ./test_exec '' a b

	SEC="3.5 IFS=' ' explicit whitespace only"
	local S35
	S35="$(cat <<'EOF'
IFS=' '
X='  a  b  '
Y='a::b'
EOF
)"
	tc 3.5.1 "$SEC" "$S35" './test_exec $X' ./test_exec a b
	tc 3.5.2 "$SEC" "$S35" './test_exec $Y' ./test_exec 'a::b'

	SEC="3.6 splitting in a word glued to text"
	local S36
	S36="$(cat <<'EOF'
unset IFS
A='x y'
EMPTY=
EOF
)"
	tc 3.6.1 "$SEC" "$S36" './test_exec pre${A}post'     ./test_exec prex ypost
	tc 3.6.2 "$SEC" "$S36" './test_exec pre"$A"post'     ./test_exec 'prex ypost'
	tc 3.6.3 "$SEC" "$S36" './test_exec pre${EMPTY}post' ./test_exec prepost
	tc 3.6.4 "$SEC" "$S36" './test_exec pre"$EMPTY"post' ./test_exec prepost

	SEC="3.7 several expansions in the same word"
	local S37
	S37="$(cat <<'EOF'
unset IFS
A='a b'
B='c d'
EOF
)"
	tc 3.7.1 "$SEC" "$S37" './test_exec X${A}Y${B}Z'  ./test_exec Xa bYc dZ
	tc 3.7.2 "$SEC" "$S37" './test_exec X"$A"Y"$B"Z'  ./test_exec 'Xa bYc dZ'
	tc 3.7.3 "$SEC" "$S37" './test_exec X"$A"Y${B}Z'  ./test_exec 'Xa bYc' dZ

	SEC="3.8 command-name position"
	local S38
	S38="$(cat <<'EOF'
unset IFS
CMD='./test_exec ok'
EMPTY=
unset U
EOF
)"
	tc 3.8.1 "$SEC" "$S38" '$CMD end'            ./test_exec ok end
	tc_status 3.8.2 "$SEC" "$S38" '"$CMD" end'   127
	tc 3.8.3 "$SEC" "$S38" '$U ./test_exec ok'   ./test_exec ok
	tc_status 3.8.4 "$SEC" "$S38" '"$U" ./test_exec ok' 127

	SEC="3.9 assignment context: no field splitting"
	local S39
	S39="$(cat <<'EOF'
unset IFS
A='a b'
EOF
)"
	tc 3.9.1 "$SEC" "$S39" $'C=$A\n./test_exec "$C"' ./test_exec 'a b'
	tc 3.9.2 "$SEC" "$S39" './test_exec C=$A'        ./test_exec 'C=a' b
	tc 3.9.3 "$SEC" "$S39" $'unset D\nexport D=$A\n./test_exec "$D"' \
		./test_exec 'a b'
	tc 3.9.4 "$SEC" "$S39" $'unset R\nreadonly R=$A\n./test_exec "$R"' \
		./test_exec 'a b'

	SEC="3.10 IFS modified in the same simple command"
	local S310
	S310="$(cat <<'EOF'
unset IFS
X='a:b c'
EOF
)"
	tc 3.10.1 "$SEC" "$S310" 'IFS=: ./test_exec $X' \
		./test_exec 'a:b' c
	tc 3.10.2 "$SEC" "$S310" $'IFS=:\n./test_exec $X' \
		./test_exec a 'b c'

	SEC="3.11 field splitting then pathname expansion"
	local S311
	S311="$(cat <<'EOF'
unset IFS
P='fs_glob/*.c fs_glob/*.h'
EOF
)"
	tc 3.11.1 "$SEC" "$S311" './test_exec $P' \
		./test_exec fs_glob/a.c fs_glob/b.c fs_glob/a.h
	tc 3.11.2 "$SEC" "$S311" './test_exec "$P"' \
		./test_exec 'fs_glob/*.c fs_glob/*.h'

	SEC="3.12 tricky IFS=: empty-field cases"
	local S312
	S312="$(cat <<'EOF'
IFS=:
A=':'
B='::'
C='a::'
D='::a'
E='a:::b'
EOF
)"
	tc 3.12.1 "$SEC" "$S312" './test_exec $A' ./test_exec ''
	tc 3.12.2 "$SEC" "$S312" './test_exec $B' ./test_exec '' ''
	tc 3.12.3 "$SEC" "$S312" './test_exec $C' ./test_exec a ''
	tc 3.12.4 "$SEC" "$S312" './test_exec $D' ./test_exec '' '' a
	tc 3.12.5 "$SEC" "$S312" './test_exec $E' ./test_exec a '' '' b
}

###############################################################################
# 4. Tilde Expansion
###############################################################################

run_tilde_tests()
{
	section "4. TILDE EXPANSION"

	local THOME='/tmp/home with spaces'
	local S4="HOME='/tmp/home with spaces'"
	local VALID_HOME
	VALID_HOME="$(getent passwd root 2>/dev/null | cut -d: -f6)"

	local SEC="4. Tilde — no username, unquoted"
	tc 4.01 "$SEC" "$S4" './test_exec ~'      ./test_exec "$THOME"
	tc 4.02 "$SEC" "$S4" './test_exec ~/dir'  ./test_exec "$THOME/dir"
	tc 4.03 "$SEC" "$S4" './test_exec ~/'     ./test_exec "$THOME/"
	tc 4.04 "$SEC" "$S4" './test_exec pre~'   ./test_exec 'pre~'
	tc 4.05 "$SEC" "$S4" './test_exec a/~'    ./test_exec 'a/~'

	SEC="4. Tilde — no username, quoted"
	tc 4.06 "$SEC" "$S4" './test_exec "~"'    ./test_exec '~'
	tc 4.07 "$SEC" "$S4" "./test_exec '~/dir'" ./test_exec '~/dir'
	tc 4.08 "$SEC" "$S4" './test_exec \~'     ./test_exec '~'
	tc 4.09 "$SEC" "$S4" './test_exec \~/dir' ./test_exec '~/dir'

	SEC="4. Tilde — valid username"
	if [[ -n "$VALID_HOME" ]]; then
		tc 4.10 "$SEC" "$S4" './test_exec ~root'     ./test_exec "$VALID_HOME"
		tc 4.11 "$SEC" "$S4" './test_exec ~root/dir' ./test_exec "$VALID_HOME/dir"
	else
		skip_case 4.10 './test_exec ~root' "no home for root on this machine"
		skip_case 4.11 './test_exec ~root/dir' "no home for root on this machine"
	fi
	tc 4.12 "$SEC" "$S4" './test_exec pre~root'  ./test_exec 'pre~root'
	tc 4.13 "$SEC" "$S4" './test_exec a/~root'   ./test_exec 'a/~root'
	tc 4.14 "$SEC" "$S4" './test_exec "~root"'   ./test_exec '~root'
	tc 4.15 "$SEC" "$S4" "./test_exec '~root/dir'" ./test_exec '~root/dir'
	tc 4.16 "$SEC" "$S4" './test_exec \~root'    ./test_exec '~root'

	SEC="4. Tilde — invalid username, quoted"
	tc 4.17 "$SEC" "$S4" './test_exec "~__nosuchuser__"' \
		./test_exec '~__nosuchuser__'
	tc 4.18 "$SEC" "$S4" "./test_exec '~__nosuchuser__/dir'" \
		./test_exec '~__nosuchuser__/dir'
	tc 4.19 "$SEC" "$S4" './test_exec \~__nosuchuser__' \
		./test_exec '~__nosuchuser__'

	SEC="4. Tilde — assignment context"
	tc 4.20 "$SEC" "$S4" $'T=~\n./test_exec "$T"'      ./test_exec "$THOME"
	tc 4.21 "$SEC" "$S4" $'T=~/dir\n./test_exec "$T"'  ./test_exec "$THOME/dir"
	tc 4.22 "$SEC" "$S4" $'T="~"\n./test_exec "$T"'    ./test_exec '~'
	tc 4.23 "$SEC" "$S4" $'T=\'~/dir\'\n./test_exec "$T"' ./test_exec '~/dir'

	SEC="4. Tilde — assignment: after colon"
	tc 4.24 "$SEC" "$S4" $'T=~/a:~/b\n./test_exec "$T"' \
		./test_exec "$THOME/a:$THOME/b"
	tc 4.25 "$SEC" "$S4" $'T=prefix:~/b\n./test_exec "$T"' \
		./test_exec "prefix:$THOME/b"
	if [[ -n "$VALID_HOME" ]]; then
		tc 4.26 "$SEC" "$S4" $'T=~:~root\n./test_exec "$T"' \
			./test_exec "$THOME:$VALID_HOME"
	else
		skip_case 4.26 'T=~:~root' "no home for root on this machine"
	fi
	tc 4.27 "$SEC" "$S4" $'T=~:"~"\n./test_exec "$T"' \
		./test_exec "$THOME:~"

	SEC="4. Tilde — non-assignment colon"
	tc 4.28 "$SEC" "$S4" './test_exec x:~' ./test_exec 'x:~'

	SEC="4. Tilde — declaration utility context"
	tc 4.29 "$SEC" "$S4" $'unset TD\nexport TD=~/x\n./test_exec "$TD"' \
		./test_exec "$THOME/x"
	tc 4.30 "$SEC" "$S4" $'unset TR\nreadonly TR=~/x\n./test_exec "$TR"' \
		./test_exec "$THOME/x"
	tc 4.31 "$SEC" "$S4" $'unset TD2\nexport TD2="~/x"\n./test_exec "$TD2"' \
		./test_exec '~/x'
}

###############################################################################
# 5. Dollar-Single-Quotes $'...'
###############################################################################

run_dollar_squote_tests()
{
	section "5. DOLLAR-SINGLE-QUOTES \$'...'"

	local S5="unset IFS"
	local c

	local SEC="5. \$'...' — simple literals"
	tc 5.01 "$SEC" "$S5" "./test_exec \$'abc'"       ./test_exec abc
	tc 5.02 "$SEC" "$S5" "./test_exec \$'a b c'"     ./test_exec 'a b c'
	tc 5.03 "$SEC" "$S5" "./test_exec \$'*.c'"       ./test_exec '*.c'
	tc 5.04 "$SEC" "$S5" "./test_exec dsq/\$'*.c'"   ./test_exec 'dsq/*.c'

	SEC="5. \$'...' — no inner expansions"
	tc 5.05 "$SEC" "$S5" "./test_exec \$'\$A'"          ./test_exec '$A'
	tc 5.06 "$SEC" "$S5" "./test_exec \$'\${A}'"        ./test_exec '${A}'
	tc 5.07 "$SEC" "$S5" "./test_exec \$'\$(echo hi)'"  ./test_exec '$(echo hi)'
	tc 5.08 "$SEC" "$S5" "./test_exec \$'\$((1+2))'"    ./test_exec '$((1+2))'

	SEC="5. \$'...' — concatenation in the same word"
	tc 5.09 "$SEC" "$S5" "./test_exec pre\$'MID'post"      ./test_exec preMIDpost
	tc 5.10 "$SEC" "$S5" "./test_exec \$'a b'X"            ./test_exec 'a bX'
	tc 5.11 "$SEC" "$S5" "./test_exec X\$'a b'Y\$'c d'Z"   ./test_exec 'Xa bYc dZ'

	SEC="5. \$'...' — escaped quotes and backslash"
	tc 5.12 "$SEC" "$S5" "./test_exec \$'don\\'t'"     ./test_exec "don't"
	tc 5.13 "$SEC" "$S5" "./test_exec \$'a\\\\b'"      ./test_exec 'a\b'
	tc 5.14 "$SEC" "$S5" "./test_exec \$'a\\\"b'"      ./test_exec 'a"b'
	tc 5.15 "$SEC" "$S5" "./test_exec \$'a\"b'"        ./test_exec 'a"b'

	SEC="5. \$'...' — classic escapes"
	tc 5.16 "$SEC" "$S5" "./test_exec \$'a\nb'" ./test_exec $'a\nb'
	tc 5.17 "$SEC" "$S5" "./test_exec \$'a\tb'" ./test_exec $'a\tb'
	tc 5.18 "$SEC" "$S5" "./test_exec \$'a\rb'" ./test_exec $'a\rb'
	tc 5.19 "$SEC" "$S5" "./test_exec \$'a\bb'" ./test_exec $'a\bb'
	tc 5.20 "$SEC" "$S5" "./test_exec \$'a\fb'" ./test_exec $'a\fb'
	tc 5.21 "$SEC" "$S5" "./test_exec \$'a\vb'" ./test_exec $'a\vb'
	tc 5.22 "$SEC" "$S5" "./test_exec \$'a\ab'" ./test_exec $'a\ab'
	tc 5.23 "$SEC" "$S5" "./test_exec \$'a\eb'" ./test_exec $'a\eb'

	SEC="5. \$'...' — octal escapes"
	tc 5.24 "$SEC" "$S5" "./test_exec \$'\101'"        ./test_exec A
	tc 5.25 "$SEC" "$S5" "./test_exec \$'\141'"        ./test_exec a
	tc 5.26 "$SEC" "$S5" "./test_exec \$'a\040b'"      ./test_exec 'a b'
	tc 5.27 "$SEC" "$S5" "./test_exec \$'a\012b'"      ./test_exec $'a\nb'
	tc 5.28 "$SEC" "$S5" "./test_exec \$'\101\102\103'" ./test_exec ABC

	SEC="5. \$'...' — hex escapes"
	tc 5.29 "$SEC" "$S5" "./test_exec \$'\x41'"    ./test_exec A
	tc 5.30 "$SEC" "$S5" "./test_exec \$'\x61'"    ./test_exec a
	tc 5.31 "$SEC" "$S5" "./test_exec \$'a\x20b'"  ./test_exec 'a b'
	tc 5.32 "$SEC" "$S5" "./test_exec \$'a\x2fb'"  ./test_exec 'a/b'
	tc 5.33 "$SEC" "$S5" "./test_exec \$'a\x0ab'"  ./test_exec $'a\nb'

	SEC="5. \$'...' — control escapes \\cX (if implemented)"
	tc 5.34 "$SEC" "$S5" "./test_exec \$'\cA'"     ./test_exec $'\x01'
	tc 5.35 "$SEC" "$S5" "./test_exec \$'\cZ'"     ./test_exec $'\x1a'
	tc 5.36 "$SEC" "$S5" "./test_exec \$'\c['"     ./test_exec $'\x1b'
	tc 5.37 "$SEC" "$S5" "./test_exec \$'a\cIb'"   ./test_exec $'a\tb'

	SEC="5. \$'...' — several escapes in one argument"
	tc 5.38 "$SEC" "$S5" "./test_exec \$'A\nB\tC'"        ./test_exec $'A\nB\tC'
	tc 5.39 "$SEC" "$S5" "./test_exec \$'\101\x42\103'"   ./test_exec ABC
	tc 5.40 "$SEC" "$S5" \
		"./test_exec \$'quote:\\' backslash:\\\\ tab:\t end'" \
		./test_exec $'quote:\' backslash:\\ tab:\t end'

	SEC="5. \$'...' — interaction with field splitting"
	tc 5.41 "$SEC" "$S5" "./test_exec \$'a b' c" ./test_exec 'a b' c
	tc 5.42 "$SEC" $'IFS=:\n'"X=\$'a:b:c'" './test_exec $X' \
		./test_exec a b c
	tc 5.43 "$SEC" 'IFS=:' "./test_exec \$'a:b:c'" \
		./test_exec 'a:b:c'

	SEC="5. \$'...' — interaction with pathname expansion"
	tc 5.44 "$SEC" "$S5" "./test_exec \$'dsq/*.c'" ./test_exec 'dsq/*.c'
	tc 5.45 "$SEC" "$S5"$'\n'"P=\$'dsq/*.c'" './test_exec $P' \
		./test_exec dsq/a.c dsq/b.c
	tc 5.46 "$SEC" "$S5"$'\n'"P=\$'dsq/*.c'" './test_exec "$P"' \
		./test_exec 'dsq/*.c'

	SEC="5. \$'...' — assignment context"
	tc 5.47 "$SEC" "$S5"$'\n'"D=\$'a b'" './test_exec "$D"' \
		./test_exec 'a b'
	tc 5.48 "$SEC" "$S5"$'\n'"D=\$'a\nb'" './test_exec "$D"' \
		./test_exec $'a\nb'
	tc 5.49 "$SEC" "$S5"$'\n'"export E=\$'x y'" './test_exec "$E"' \
		./test_exec 'x y'
	tc 5.50 "$SEC" "$S5"$'\n'"readonly R=\$'x\ty'" './test_exec "$R"' \
		./test_exec $'x\ty'

	SEC="5. \$'...' — command-name position"
	tc 5.51 "$SEC" "$S5" "\$'./test_exec' ok" ./test_exec ok
	tc_status 5.52 "$SEC" "$S5" "\$'./test_exec arg'" 127
	tc 5.53 "$SEC" "$S5"$'\n'"CMD=\$'./test_exec arg'" '$CMD end' \
		./test_exec arg end
	tc_status 5.54 "$SEC" "$S5"$'\n'"CMD=\$'./test_exec arg'" '"$CMD" end' 127

	SEC="5. \$'...' — inside double quotes is literal"
	tc 5.55 "$SEC" "$S5" "./test_exec \"\$'a\nb'\"" ./test_exec "\$'a\nb'"
	c="$(cat <<'EOF'
./test_exec '$'\''a\nb'\'''
EOF
)"
	tc 5.56 "$SEC" "$S5" "$c" ./test_exec "\$'a\nb'"
}

###############################################################################
# 6. Parameter Length ${#p} and Pattern Removal # ## % %%
###############################################################################

run_length_removal_tests()
{
	section "6. PARAMETER LENGTH \${#p} AND PATTERN REMOVAL # ## % %%"

	local S6
	S6="$(cat <<'EOF'
unset IFS
unset U
A='a b'
EMPTY=
X=file.c
P=posix/src/std
V=abcabc
L='a*c'
S='a b.c'
R='g/base/*.cX'
SUF=.c
PRE=posix/
EOF
)"

	local SEC="6. String length \${#parameter}"
	tc 6.L1 "$SEC" "$S6" './test_exec ${#X}'        ./test_exec 6
	tc 6.L2 "$SEC" "$S6" './test_exec "${#A}"'      ./test_exec 3
	tc 6.L3 "$SEC" "$S6" './test_exec ${#EMPTY}'    ./test_exec 0
	tc 6.L4 "$SEC" "$S6" './test_exec ${#U}'        ./test_exec 0
	tc 6.L5 "$SEC" "$S6" './test_exec pre${#X}post' ./test_exec pre6post

	SEC="6. Smallest prefix removal \${p#pattern}"
	tc 6.P1 "$SEC" "$S6" './test_exec ${X#file}'  ./test_exec .c
	tc 6.P2 "$SEC" "$S6" './test_exec ${X#*.}'    ./test_exec c
	tc 6.P3 "$SEC" "$S6" './test_exec ${P#*/}'    ./test_exec src/std
	tc 6.P4 "$SEC" "$S6" './test_exec ${V#*b}'    ./test_exec cabc
	tc 6.P5 "$SEC" "$S6" './test_exec ${X#????}'  ./test_exec .c
	tc 6.P6 "$SEC" "$S6" './test_exec ${V#[ab]}'  ./test_exec bcabc
	tc 6.P7 "$SEC" "$S6" './test_exec ${X#z}'     ./test_exec file.c
	tc 6.P8 "$SEC" "$S6" './test_exec ${X#}'      ./test_exec file.c
	tc 6.P9 "$SEC" "$S6" './test_exec before "${X#file.c}" after' \
		./test_exec before '' after

	SEC="6. Largest prefix removal \${p##pattern}"
	tc 6.PP1 "$SEC" "$S6" './test_exec ${P##*/}'  ./test_exec std
	tc 6.PP2 "$SEC" "$S6" './test_exec ${V##*b}'  ./test_exec c
	tc 6.PP3 "$SEC" "$S6" './test_exec ${X##*.}'  ./test_exec c
	tc 6.PP4 "$SEC" "$S6" './test_exec before "${X##f*}" after' \
		./test_exec before '' after
	tc 6.PP5 "$SEC" "$S6" './test_exec ${X##z*}'  ./test_exec file.c
	tc 6.PP6 "$SEC" "$S6" './test_exec ${V#a*b} ${V##a*b}' \
		./test_exec cabc c

	SEC="6. Smallest suffix removal \${p%pattern}"
	tc 6.S1 "$SEC" "$S6" './test_exec ${X%.c}'    ./test_exec file
	tc 6.S2 "$SEC" "$S6" './test_exec ${X%.*}'    ./test_exec file
	tc 6.S3 "$SEC" "$S6" './test_exec ${P%/*}'    ./test_exec posix/src
	tc 6.S4 "$SEC" "$S6" './test_exec ${V%b*}'    ./test_exec abca
	tc 6.S5 "$SEC" "$S6" './test_exec ${X%?}'     ./test_exec file.
	tc 6.S6 "$SEC" "$S6" './test_exec ${X%[ch]}'  ./test_exec file.
	tc 6.S7 "$SEC" "$S6" './test_exec ${X%z}'     ./test_exec file.c
	tc 6.S8 "$SEC" "$S6" './test_exec ${X%}'      ./test_exec file.c
	tc 6.S9 "$SEC" "$S6" './test_exec ${X%.c}.o'  ./test_exec file.o

	SEC="6. Largest suffix removal \${p%%pattern}"
	tc 6.SS1 "$SEC" "$S6" './test_exec ${P%%/*}'  ./test_exec posix
	tc 6.SS2 "$SEC" "$S6" './test_exec ${V%%b*}'  ./test_exec a
	tc 6.SS3 "$SEC" "$S6" './test_exec ${X%%.*}'  ./test_exec file
	tc 6.SS4 "$SEC" "$S6" './test_exec before "${X%%f*}" after' \
		./test_exec before '' after
	tc 6.SS5 "$SEC" "$S6" './test_exec ${V%b*} ${V%%b*}' \
		./test_exec abca a

	SEC="6. Pattern removal — quoting the pattern"
	tc 6.Q1 "$SEC" "$S6" "./test_exec \${X%'.c'}" ./test_exec file
	tc 6.Q2 "$SEC" "$S6" './test_exec ${X%".c"}'  ./test_exec file
	tc 6.Q3 "$SEC" "$S6" './test_exec ${L%*c}'    ./test_exec 'a*'
	tc 6.Q4 "$SEC" "$S6" "./test_exec \${L%'*c'}" ./test_exec a
	tc 6.Q5 "$SEC" "$S6" './test_exec ${L%\*c}'   ./test_exec a
	tc 6.Q6 "$SEC" "$S6" './test_exec ${X%"$SUF"}' ./test_exec file
	tc 6.Q7 "$SEC" "$S6" './test_exec ${X%$SUF}'  ./test_exec file
	tc 6.Q8 "$SEC" "$S6" './test_exec ${P#"$PRE"}' ./test_exec src/std

	SEC="6. Pattern removal — unset/empty parameter"
	tc 6.E1 "$SEC" "$S6" './test_exec before "${EMPTY#x}" after' \
		./test_exec before '' after
	tc 6.E2 "$SEC" "$S6" './test_exec before "${U%x}" after' \
		./test_exec before '' after
	tc 6.E3 "$SEC" "$S6" './test_exec before ${U#x} after' \
		./test_exec before after

	SEC="6. Pattern removal — result splitting and globbing"
	tc 6.F1 "$SEC" "$S6" './test_exec ${S%.c}'    ./test_exec a b
	tc 6.F2 "$SEC" "$S6" './test_exec "${S%.c}"'  ./test_exec 'a b'
	tc 6.F3 "$SEC" "$S6" './test_exec ${R%X}' \
		./test_exec g/base/file.c g/base/main.c
	tc 6.F4 "$SEC" "$S6" './test_exec "${R%X}"'   ./test_exec 'g/base/*.c'
}

###############################################################################
# 7. Special Parameters $@ $* $# $? and Positionals
###############################################################################

run_special_param_tests()
{
	section "7. SPECIAL PARAMETERS \$@ \$* \$# \$? AND POSITIONALS"

	local S7
	S7="$(cat <<'EOF'
unset IFS
set -- 'a b' 'c d'
EOF
)"
	local S7C
	S7C="$(cat <<'EOF'
IFS=:
set -- 'a b' 'c d'
EOF
)"
	local S7N
	S7N="$(cat <<'EOF'
IFS=
set -- 'a b' 'c d'
EOF
)"
	local S7CS
	S7CS="$(cat <<'EOF'
IFS=': '
set -- 'a b' 'c d'
EOF
)"

	local SEC="7. Positional parameters"
	tc 7.01 "$SEC" $'unset IFS\nset -- one two three' \
		'./test_exec "$1" "$2" "$3"' ./test_exec one two three
	tc 7.02 "$SEC" $'unset IFS\nset -- one two three' \
		'./test_exec $2' ./test_exec two
	tc 7.03 "$SEC" "$S7" './test_exec "$1"' ./test_exec 'a b'
	tc 7.04 "$SEC" "$S7" './test_exec $1'   ./test_exec a b
	tc 7.05 "$SEC" $'unset IFS\nset -- one' './test_exec ${2:-def}' \
		./test_exec def
	tc 7.06 "$SEC" $'unset IFS\nset -- a b' './test_exec "$11"' \
		./test_exec a1
	tc 7.07 "$SEC" \
		$'unset IFS\nset -- one two three four five six seven eight nine ten eleven' \
		'./test_exec "${11}"' ./test_exec eleven

	SEC="7. \$# parameter count"
	tc 7.10 "$SEC" $'unset IFS\nset -- a b c' './test_exec "$#"' \
		./test_exec 3
	tc 7.11 "$SEC" $'unset IFS\nset --' './test_exec "$#"' ./test_exec 0
	tc 7.12 "$SEC" "$S7" './test_exec $#' ./test_exec 2

	SEC="7. \"\$@\" — one field per parameter"
	tc 7.20 "$SEC" "$S7" './test_exec "$@"' ./test_exec 'a b' 'c d'
	tc 7.21 "$SEC" "$S7" './test_exec $@'   ./test_exec a b c d
	tc 7.22 "$SEC" "$S7" './test_exec pre "$@" post' \
		./test_exec pre 'a b' 'c d' post
	tc 7.23 "$SEC" $'unset IFS\nset --' './test_exec "$@"' ./test_exec
	tc 7.24 "$SEC" $'unset IFS\nset -- ""' './test_exec "$@"' \
		./test_exec ''

	SEC="7. \"\$*\" — joined with first IFS character"
	tc 7.30 "$SEC" "$S7"   './test_exec "$*"' ./test_exec 'a b c d'
	tc 7.31 "$SEC" "$S7C"  './test_exec "$*"' ./test_exec 'a b:c d'
	tc 7.32 "$SEC" "$S7N"  './test_exec "$*"' ./test_exec 'a bc d'
	tc 7.33 "$SEC" "$S7CS" './test_exec "$*"' ./test_exec 'a b:c d'
	tc 7.34 "$SEC" "$S7C"  './test_exec $*'   ./test_exec 'a b' 'c d'

	SEC="7. \$? exit status"
	tc 7.40 "$SEC" 'true' './test_exec "$?"' ./test_exec 0
	tc 7.41 "$SEC" "sh -c 'exit 5'" './test_exec "$?"' ./test_exec 5
}

###############################################################################
# 8. Command Substitution $(...) and `...`
###############################################################################

run_cmd_sub_tests()
{
	section "8. COMMAND SUBSTITUTION \$(...) AND \`...\` (disabled: not implemented)"

	# NOTE: command substitution is not implemented in the expander yet.
	# Uncomment these tests (and the S8/SEC locals) once $(...) and `...`
	# are wired. Expectations are POSIX-based, validated against dash+bash.

	# local S8='unset IFS'

	# local SEC="8. \$() basic"
	# tc 8.01 "$SEC" "$S8" './test_exec $(echo hi)'   ./test_exec hi
	# tc 8.02 "$SEC" "$S8" './test_exec "$(echo hi)"' ./test_exec hi
	# tc 8.03 "$SEC" "$S8" "./test_exec \$(echo 'a  b')"     ./test_exec a b
	# tc 8.04 "$SEC" "$S8" "./test_exec \"\$(echo 'a  b')\"" ./test_exec 'a  b'
	# tc 8.05 "$SEC" "$S8" './test_exec pre"$(echo mid)"post' \
	# 	./test_exec premidpost
	# tc 8.06 "$SEC" "$S8" './test_exec pre$(echo mid)post' \
	# 	./test_exec premidpost

	# SEC="8. trailing newline removal"
	# tc 8.10 "$SEC" "$S8" "./test_exec \"\$(printf 'x\\n\\n\\n')\"" \
	# 	./test_exec x
	# tc 8.11 "$SEC" "$S8" "./test_exec \"\$(printf 'a\\nb\\n')\"" \
	# 	./test_exec $'a\nb'
	# tc 8.12 "$SEC" "$S8" "./test_exec \$(printf 'a\\nb\\n')" \
	# 	./test_exec a b

	# SEC="8. backquotes"
	# tc 8.20 "$SEC" "$S8" './test_exec `echo hi`'   ./test_exec hi
	# tc 8.21 "$SEC" "$S8" './test_exec "`echo hi`"' ./test_exec hi

	# SEC="8. nesting and inner quoting"
	# tc 8.30 "$SEC" "$S8" './test_exec "$(echo $(echo inner))"' \
	# 	./test_exec inner
	# tc 8.31 "$SEC" "$S8" './test_exec "$(echo "a b")"' ./test_exec 'a b'

	# SEC="8. empty output"
	# tc 8.40 "$SEC" "$S8" './test_exec before "$(true)" after' \
	# 	./test_exec before '' after
	# tc 8.41 "$SEC" "$S8" './test_exec before $(true) after' \
	# 	./test_exec before after

	# SEC="8. assignment context: no field splitting"
	# tc 8.50 "$SEC" "$S8"$'\n'"V=\$(echo 'a  b')" './test_exec "$V"' \
	# 	./test_exec 'a  b'

	# SEC="8. with field splitting and pathname expansion"
	# tc 8.60 "$SEC" "$S8" "./test_exec \$(echo 'g/base/*.c')" \
	# 	./test_exec g/base/file.c g/base/main.c
	# tc 8.61 "$SEC" "$S8" "./test_exec \"\$(echo 'g/base/*.c')\"" \
	# 	./test_exec 'g/base/*.c'

	# SEC="8. command-name position"
	# tc 8.70 "$SEC" "$S8" '$(echo ./test_exec) ok' ./test_exec ok
}

###############################################################################
# 9. Arithmetic Expansion $((...))
###############################################################################

run_arith_tests()
{
	section "9. ARITHMETIC EXPANSION \$((...)) (disabled: not implemented)"

	# NOTE: arithmetic expansion is not implemented in the expander yet.
	# Uncomment these tests (and the S9/SEC locals) once $((...)) is wired.
	# Expectations are POSIX-based, validated against dash+bash.

	# local S9='unset IFS'

	# local SEC="9. basic operators"
	# tc 9.01 "$SEC" "$S9" './test_exec $((1+2))'       ./test_exec 3
	# tc 9.02 "$SEC" "$S9" './test_exec $((7-10))'      ./test_exec -3
	# tc 9.03 "$SEC" "$S9" './test_exec $((3*4))'       ./test_exec 12
	# tc 9.04 "$SEC" "$S9" './test_exec $((10/3))'      ./test_exec 3
	# tc 9.05 "$SEC" "$S9" './test_exec $((10%3))'      ./test_exec 1
	# tc 9.06 "$SEC" "$S9" './test_exec $((1+2*3))'     ./test_exec 7
	# tc 9.07 "$SEC" "$S9" './test_exec $(( (1+2)*3 ))' ./test_exec 9
	# tc 9.08 "$SEC" "$S9" './test_exec $((-5+2))'      ./test_exec -3

	# SEC="9. integer constants (ISO C)"
	# tc 9.10 "$SEC" "$S9" './test_exec $((010))'  ./test_exec 8
	# tc 9.11 "$SEC" "$S9" './test_exec $((0x1F))' ./test_exec 31
	# tc 9.12 "$SEC" "$S9" './test_exec $((0))'    ./test_exec 0

	# SEC="9. comparisons and logic"
	# tc 9.20 "$SEC" "$S9" './test_exec $((2<3))'   ./test_exec 1
	# tc 9.21 "$SEC" "$S9" './test_exec $((2>3))'   ./test_exec 0
	# tc 9.22 "$SEC" "$S9" './test_exec $((2==2))'  ./test_exec 1
	# tc 9.23 "$SEC" "$S9" './test_exec $((2!=2))'  ./test_exec 0
	# tc 9.24 "$SEC" "$S9" './test_exec $((1&&0))'  ./test_exec 0
	# tc 9.25 "$SEC" "$S9" './test_exec $((0||3))'  ./test_exec 1
	# tc 9.26 "$SEC" "$S9" './test_exec $((!0))'    ./test_exec 1
	# tc 9.27 "$SEC" "$S9" './test_exec $((0?1:2))' ./test_exec 2

	# SEC="9. bitwise"
	# tc 9.30 "$SEC" "$S9" './test_exec $((5&3))'   ./test_exec 1
	# tc 9.31 "$SEC" "$S9" './test_exec $((5|2))'   ./test_exec 7
	# tc 9.32 "$SEC" "$S9" './test_exec $((5^1))'   ./test_exec 4
	# tc 9.33 "$SEC" "$S9" './test_exec $((1<<4))'  ./test_exec 16
	# tc 9.34 "$SEC" "$S9" './test_exec $((32>>2))' ./test_exec 8
	# tc 9.35 "$SEC" "$S9" './test_exec $((~0))'    ./test_exec -1

	# SEC="9. shell variables in expressions"
	# tc 9.40 "$SEC" "$S9"$'\nN=6' './test_exec $((N))'      ./test_exec 6
	# tc 9.41 "$SEC" "$S9"$'\nN=6' './test_exec $(($N))'     ./test_exec 6
	# tc 9.42 "$SEC" "$S9"$'\nN=6' './test_exec $((N+N/2))'  ./test_exec 9
	# tc 9.43 "$SEC" "$S9"$'\nN=6' './test_exec $((${N}*2))' ./test_exec 12
	# tc_multi 9.44 "$SEC" "$S9" \
	# 	$'./test_exec $((M=7))\n./test_exec "$M"' \
	# 	-- ./test_exec 7 -- ./test_exec 7

	# SEC="9. quoting and concatenation"
	# tc 9.50 "$SEC" "$S9" './test_exec "$((1+2))"'      ./test_exec 3
	# tc 9.51 "$SEC" "$S9" './test_exec pre$((2*2))post' ./test_exec pre4post
	# tc 9.52 "$SEC" "$S9" './test_exec $(( 1 + 2 ))'    ./test_exec 3
}

###############################################################################
# 10. Quote Removal
###############################################################################

run_quote_removal_tests()
{
	section "10. QUOTE REMOVAL"

	local c
	local S10
	S10="$(cat <<'EOF'
unset IFS
A='a b'
Q='"x y"'
SQV="'z'"
EOF
)"

	local SEC="10. adjacent quoted parts form one word"
	tc 10.01 "$SEC" "$S10" './test_exec a"b"c'          ./test_exec abc
	tc 10.02 "$SEC" "$S10" "./test_exec a'b'c"          ./test_exec abc
	tc 10.03 "$SEC" "$S10" "./test_exec 'a'\"b\"'c'"    ./test_exec abc
	tc 10.04 "$SEC" "$S10" './test_exec x""y'           ./test_exec xy
	tc 10.05 "$SEC" "$S10" "./test_exec x''y"           ./test_exec xy

	SEC="10. empty quotes as standalone argument"
	tc 10.10 "$SEC" "$S10" './test_exec ""'    ./test_exec ''
	tc 10.11 "$SEC" "$S10" "./test_exec ''"    ./test_exec ''
	tc 10.12 "$SEC" "$S10" './test_exec "" ""' ./test_exec '' ''

	SEC="10. backslash unquoted"
	tc 10.20 "$SEC" "$S10" './test_exec \a'    ./test_exec a
	tc 10.21 "$SEC" "$S10" './test_exec a\ b'  ./test_exec 'a b'
	tc 10.22 "$SEC" "$S10" './test_exec \$A'   ./test_exec '$A'
	tc 10.23 "$SEC" "$S10" './test_exec \\'    ./test_exec '\'

	SEC="10. backslash inside double quotes"
	tc 10.30 "$SEC" "$S10" './test_exec "\$A"' ./test_exec '$A'
	tc 10.31 "$SEC" "$S10" './test_exec "\\"'  ./test_exec '\'
	tc 10.32 "$SEC" "$S10" './test_exec "\a"'  ./test_exec '\a'
	tc 10.33 "$SEC" "$S10" './test_exec "a\ b"' ./test_exec 'a\ b'
	c="$(cat <<'EOF'
./test_exec "\`"
EOF
)"
	tc 10.34 "$SEC" "$S10" "$c" ./test_exec '`'

	SEC="10. single quotes preserve everything"
	tc 10.40 "$SEC" "$S10" "./test_exec '\$A'"  ./test_exec '$A'
	tc 10.41 "$SEC" "$S10" "./test_exec '\\a'"  ./test_exec '\a'
	tc 10.42 "$SEC" "$S10" "./test_exec 'a  b'" ./test_exec 'a  b'

	SEC="10. quote characters via the other quoting style"
	c="$(cat <<'EOF'
./test_exec "'"
EOF
)"
	tc 10.44 "$SEC" "$S10" "$c" ./test_exec "'"
	c="$(cat <<'EOF'
./test_exec '"'
EOF
)"
	tc 10.45 "$SEC" "$S10" "$c" ./test_exec '"'

	SEC="10. quotes in expansion results are NOT removed"
	tc 10.50 "$SEC" "$S10" './test_exec $Q'    ./test_exec '"x' 'y"'
	tc 10.51 "$SEC" "$S10" './test_exec "$Q"'  ./test_exec '"x y"'
	tc 10.52 "$SEC" "$S10" './test_exec $SQV'  ./test_exec "'z'"

	SEC="10. line continuation"
	tc 10.60 "$SEC" "$S10" $'./test_exec a\\\nb' ./test_exec ab
}

###############################################################################
# Main
###############################################################################

summary()
{
	echo ""
	if [ "$SKIPPED" -gt 0 ]; then
		echo -e "${YELLOW}○ $SKIPPED tests skipped${NC}"
	fi
	if [ "$FAILED" -eq 0 ]; then
		echo -e "${GREEN}✔ $TOTAL tests passed${NC}"
		echo -e "${GRAY}Logs: $LOG_DIR${NC}"
		return 0
	fi
	echo -e "${RED}✖ $FAILED / $TOTAL tests failed${NC}"
	echo -e "${YELLOW}⚠ Logs kept in: $LOG_DIR${NC}"
	return 1
}

main()
{
	check_program_exists "$MINISHELL"
	setup_logs
	setup_fixtures

	echo -e "${GREY}minishell expander tests${NC}"
	echo -e "${GREY}binary:   $MINISHELL${NC}"
	echo -e "${GREY}logs:     $LOG_DIR${NC}"
	echo -e "${GREY}fixtures: tests/fixtures/test_expander/${NC}"
	if [ -n "$FILTER" ]; then
		echo -e "${GREY}filter:   ids starting with '$FILTER'${NC}"
	fi

	run_param_tests
	run_pathname_tests
	run_field_splitting_tests
	run_tilde_tests
	run_dollar_squote_tests
	run_length_removal_tests
	run_special_param_tests
	#run_cmd_sub_tests
	#run_arith_tests
	run_quote_removal_tests

	summary
}

main
