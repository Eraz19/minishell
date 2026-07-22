#!/usr/bin/env zsh

###############################################################################
# minishell error-system tests
# Version: v1-error-system
#
# Test cases source: BUGS_ERROR_SYSTEM.md (bug IDs = test ID prefixes)
#
# Usage from minishell/ project root:
#   tests/test_error_system.zsh [path/to/minishell] [id-prefix-filter]
#
# Examples:
#   tests/test_error_system.zsh                    # run everything
#   tests/test_error_system.zsh minishell RUN-1    # only RUN-1 cases
#   tests/test_error_system.zsh minishell FIXED    # only regression guards
#
# How to read the results:
#   - IDs prefixed FIXED-*  : behaviors implemented during the error-system
#     pass. They are REGRESSION GUARDS: they should be green; a red one
#     means a fix regressed (or was never runtime-correct).
#   - IDs matching a bug ID (RUN-1, SHELL-1, B3, HD-1, ALIAS-1, ...) :
#     TARGET behaviors of OPEN bugs. They are EXPECTED TO FAIL until the
#     bug is fixed; fixing the bug should turn them green.
#   - B2/B3 stub guards (FIXED-STUB-*) assert the CURRENT contract
#     (printed not-implemented + exit 110). When you implement arithmetic
#     or command substitution, update those cases to the real behavior.
#
# Exit-code map (error.h):
#   110 ERR_INTERNAL | 111 ERR_LIBC | 121 ERR_POSIX_SYNTAX
#   124 ERR_POSIX_ASSIGNMENT | 125 ERR_POSIX_EXPANSION
#   126 CMD_NOT_EXECUTABLE | 127 CMD_NOT_FOUND | 128 ERR_POSIX_READ
#
# Logs: tests/logs/test_error_system.N/ (one log per test)
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
WORK_DIR="${SCRIPT_DIR}/fixtures/test_error_system"

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

###############################################################################
# Infrastructure
###############################################################################

check_program_exists()
{
	local program="$1"

	if [ ! -f "$program" ]; then
		echo -e "${RED}✖ Error: $program not found (BUILD-1 not fixed yet?)${NC}"
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
	while true; do
		LOG_DIR="${LOG_ROOT}/test_error_system.${n}"
		mkdir "$LOG_DIR" 2>/dev/null && break
		n=$((n + 1))
	done
}

setup_fixtures()
{
	WORK_DIR="${SCRIPT_DIR}/fixtures/test_error_system.${LOG_DIR:t}"
	mkdir -p "$WORK_DIR" || exit 1

	# scripts for invocation tests
	: > "$WORK_DIR/empty.sh"
	printf '/bin/echo from_script\n' > "$WORK_DIR/ok.sh"
	printf '/bin/echo secret\n' > "$WORK_DIR/unreadable.sh"
	chmod 000 "$WORK_DIR/unreadable.sh"

	# io_location / redirection targets
	printf 'redir_content\n' > "$WORK_DIR/redir_in"
}

teardown_fixtures()
{
	:
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
# Core runners
###############################################################################

# Pipe a script into minishell (stdin, non-interactive), like test_expander.
# Output is capped at 256 KiB and runs are killed after 10s so a runaway
# minishell (infinite loop / infinite print) fails its test cleanly
# (status 124 = timeout, 141 = SIGPIPE past the cap) instead of OOM-killing
# the harness.
OUTPUT_CAP=262144
RUN_TIMEOUT=10
run_pipe()
{
	CURRENT_ID="$1"
	CURRENT_SECTION="$2"
	CURRENT_SCRIPT="$3"
	CURRENT_LABEL="$4"

	CASE_FAILED=0
	CASE_DETAILS=()
	CURRENT_LOG="${LOG_DIR}/test_${CURRENT_ID//[^A-Za-z0-9._-]/_}.log"

	local raw
	printf '%s\n' "$CURRENT_SCRIPT" \
		| ( cd "$WORK_DIR" && LC_ALL=C exec timeout "$RUN_TIMEOUT" "$MINISHELL_ABS" ) 2>&1 \
		| head -c "$OUTPUT_CAP" > "${CURRENT_LOG}.raw"
	RET=${pipestatus[2]}
	raw="$(<"${CURRENT_LOG}.raw")"
	save_log "$raw"
}

# Run minishell with explicit argv (invocation-mode tests: -c, script, -s -i).
# stdin comes from $STDIN_DATA ('' => closed via /dev/null unless set).
STDIN_DATA=""
run_argv()
{
	CURRENT_ID="$1"
	CURRENT_SECTION="$2"
	CURRENT_LABEL="$3"
	shift 3

	CASE_FAILED=0
	CASE_DETAILS=()
	CURRENT_SCRIPT="minishell $*"
	CURRENT_LOG="${LOG_DIR}/test_${CURRENT_ID//[^A-Za-z0-9._-]/_}.log"

	local raw
	printf '%s' "$STDIN_DATA" \
		| ( cd "$WORK_DIR" && LC_ALL=C exec timeout "$RUN_TIMEOUT" "$MINISHELL_ABS" "$@" ) 2>&1 \
		| head -c "$OUTPUT_CAP" > "${CURRENT_LOG}.raw"
	RET=${pipestatus[2]}
	raw="$(<"${CURRENT_LOG}.raw")"
	STDIN_DATA=""
	save_log "$raw"
}

save_log()
{
	local raw="$1"

	{
		printf '### SCRIPT ###\n%s\n\n### RET ###\n%d\n\n### OUTPUT ###\n%s\n' \
			"$CURRENT_SCRIPT" "$RET" "$raw"
	} > "$CURRENT_LOG"
	OUTPUT="$(printf '%s' "$raw" | sed -e $'s/\x1b\\[[0-9;]*m//g')"
}

###############################################################################
# Expectations
###############################################################################

fail_current()
{
	CASE_FAILED=1
	CASE_DETAILS+=("$1")
}

expect_status()
{
	if [ "$RET" -ne "$1" ]; then
		fail_current "status: expected $1, got $RET"
	fi
}

expect_status_nonzero()
{
	if [ "$RET" -eq 0 ]; then
		fail_current "status: expected non-zero, got 0"
	fi
}

expect_output_contains()
{
	if [[ "$OUTPUT" != *"$1"* ]]; then
		fail_current "output: expected to contain '$1'"
	fi
}

expect_output_lacks()
{
	if [[ "$OUTPUT" == *"$1"* ]]; then
		fail_current "output: expected NOT to contain '$1'"
	fi
}

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

	skip_by_filter "$id" && return 0
	SKIPPED=$((SKIPPED + 1))
	printf "${YELLOW}○${NC} [%s] ${BLUE}%s${NC} ${GRAY}skipped: %s${NC}\n" \
		"$id" "$label" "$reason"
}

# tp ID SECTION SCRIPT STATUS [NEEDLE [LACKS]]
# Piped script; exact status; optional output needle / anti-needle.
tp()
{
	local id="$1" sec="$2" script="$3" st="$4" needle="${5:-}" lacks="${6:-}"

	skip_by_filter "$id" && return 0
	run_pipe "$id" "$sec" "$script" "${script%%$'\n'*}"
	expect_status "$st"
	[[ -n "$needle" ]] && expect_output_contains "$needle"
	[[ -n "$lacks" ]] && expect_output_lacks "$lacks"
	finish_case
}

# ta ID SECTION STATUS NEEDLE -- argv...
# Explicit-argv invocation; exact status; optional needle ('' to skip).
ta()
{
	local id="$1" sec="$2" st="$3" needle="$4"
	shift 4
	[[ "$1" == "--" ]] && shift

	skip_by_filter "$id" && return 0
	run_argv "$id" "$sec" "minishell $*" "$@"
	expect_status "$st"
	[[ -n "$needle" ]] && expect_output_contains "$needle"
	finish_case
}

###############################################################################
# FIXED — regression guards (should all be green once BUILD-1 links)
###############################################################################

run_fixed_tokenization()
{
	section "FIXED: tokenization & scanner qualification (should be green)"

	# empty input = zero commands, exit 0 (scanner TOKEN_EOF shortcut)
	ta "FIXED-EMPTY.1" "empty -c" 0 "" -- -c ""
	ta "FIXED-EMPTY.2" "empty script" 0 "" -- ./empty.sh
	STDIN_DATA=""
	tp "FIXED-EMPTY.3" "empty stdin pipe" "" 0

	# script invocation errors (POSIX sh: 127 not found / 126 not readable)
	ta "FIXED-INVOC.1" "script not found -> 127" 127 "" -- ./noexist.sh
	ta "FIXED-INVOC.2" "script unreadable -> 126" 126 "" -- ./unreadable.sh
	ta "FIXED-INVOC.3" "script runs" 0 "from_script" -- ./ok.sh

	# unterminated constructs, non-interactive -> printed + 121
	tp "FIXED-SYNTAX.1" "unterminated dquote" \
		'/bin/echo "oops' 121 "unterminated double quotes"
	tp "FIXED-SYNTAX.2" "unterminated squote" \
		"/bin/echo 'oops" 121 "unterminated single quotes"
	tp "FIXED-SYNTAX.3" "unterminated param" \
		'/bin/echo ${oops' 121 "unterminated"

	# IO_NUMBER digits-only fix: +2 is a WORD, not a redirection fd
	tp "FIXED-IONUM.1" "+2 stays an argument" \
		'/bin/echo +2>ionum_out
/bin/cat ionum_out' 0 "+2"

	# heredoc: unterminated -> missing delimiter + 121 (via scanner)
	tp "FIXED-HD.1" "unterminated heredoc" \
		'/bin/cat <<EOF
no delimiter here' 121 "missing delimiter"

	# heredoc: quoted delimiter -> body NOT expanded (HD-2 verifies converter)
	tp "FIXED-HD.2" "quoted delim, no expansion" \
		"/bin/cat <<'Q'
\$HOME
Q" 0 '$HOME'

	# heredoc: unquoted delimiter -> body expanded
	tp "FIXED-HD.3" "unquoted delim, expansion" \
		'X=hello
/bin/cat <<Q
$X
Q' 0 "hello"

	# heredoc: POSIX escape set in body (\" stays literal backslash+quote)
	tp "FIXED-HD.4" "backslash-dquote literal in body" \
		'/bin/cat <<Q
a\"b
Q' 0 'a\"b'

	# empty heredoc body (expansion_load_empty guard: no crash)
	tp "FIXED-HD.5" "empty heredoc body" \
		'/bin/cat <<Q
Q' 0
}

run_fixed_expander()
{
	section "FIXED: expander qualification (should be green)"

	# bad substitution -> printed + 125
	tp "FIXED-EXP.1" '${} -> 125' \
		'/bin/echo ${}' 125 "bad substitution"
	tp "FIXED-EXP.2" 'invalid operator -> 125' \
		'/bin/echo ${x^}' 125 "bad substitution"

	# ${var?word}: custom message printed, 125
	tp "FIXED-EXP.3" '${UNSET?msg} -> 125 + msg' \
		'/bin/echo ${UNSETVAR_42?custom_diag}' 125 "custom_diag"
	tp "FIXED-EXP.4" '${UNSET?} -> 125' \
		'/bin/echo ${UNSETVAR_42?}' 125 "null or not set"

	# assignment to unassignable name -> 125
	tp "FIXED-EXP.5" '${1=x} -> 125' \
		'/bin/echo ${1=x}' 125

	# quoted tilde stays literal (ERR_QUOTED_TILDE contained, no error)
	tp "FIXED-TILDE.1" "quoted tilde literal" \
		"/bin/echo '~'/x" 0 "~/x"

	# unset-var expansion is NOT an error
	tp "FIXED-EXP.6" "unset var -> empty, exit 0" \
		'/bin/echo a${UNSETVAR_42}b' 0 "ab"
}

run_fixed_stubs()
{
	section "FIXED-STUB: not-implemented contracts (update when implementing B2/B3)"

	# backtick: was an INFINITE LOOP; now printed not-implemented + 110
	tp "FIXED-STUB.1" "backtick -> 110 (B3 target: real substitution)" \
		'/bin/echo `ls`' 110 "not implemented"

	# $(...) tokenization blocked on LEX-1 -> printed + 110 (not a hang)
	tp "FIXED-STUB.2" '$(...) -> 110 (LEX-1 target: tokenizes)' \
		'/bin/echo $(ls)' 110 "not implemented"

	# arithmetic evaluation stub -> 110 (B2 target: computes)
	tp "FIXED-STUB.3" '$((1+1)) -> 110 (B2 target: prints 2)' \
		'/bin/echo $((1+1))' 110 "not implemented"
}

###############################################################################
# OPEN BUGS — target behaviors, EXPECTED TO FAIL until fixed
###############################################################################

run_open_runner_shell()
{
	section "OPEN: RUN-* / SHELL-* (expected to fail until fixed)"

	# RUN-1: interactive EOF (Ctrl-D at prompt) -> clean exit, last status
	# -s -i forces SCAN_MODE_STDIN_TTY; empty stdin = immediate EOF.
	STDIN_DATA=""
	ta "RUN-1.1" "interactive EOF -> exit 0" 0 "" -- -s -i
	STDIN_DATA='true
'
	ta "RUN-1.2" "cmds then EOF -> exit 0" 0 "" -- -s -i

	# RUN-2: interactive shell survives an expansion error
	STDIN_DATA='/bin/echo ${}
/bin/echo survived
'
	ta "RUN-2.1" "expansion error, shell continues" 0 "survived" -- -s -i

	# RUN-3 (+ POSIX table): non-interactive cmd-not-found does NOT exit
	tp "RUN-3.1" "cmd not found, script continues" \
		'nosuchcommand_xyz_42
/bin/echo survived' 0 "survived"

	# SHELL-1: exit status of the shell = $? of the last command
	ta "SHELL-1.1" "-c false -> 1" 1 "" -- -c "false"
	ta "SHELL-1.2" "-c cmd-not-found -> 127" 127 "" -- -c "nosuchcommand_xyz_42"
	tp "SHELL-1.3" "last status via pipe" 'false' 1
}

run_open_heredoc()
{
	section "OPEN: HD-* (expected to fail until fixed)"

	# HD-1: temp files must not accumulate
	skip_by_filter "HD-1.1" || {
		local before
		before=(/tmp/minishell_heredoc_*(N))
		run_pipe "HD-1.1" "heredoc tmp cleanup" \
			'/bin/cat <<Q
body
Q' "heredoc leaves no tmp file"
		local after f new=0
		after=(/tmp/minishell_heredoc_*(N))
		for f in "${after[@]}"; do
			if (( ${before[(Ie)$f]} == 0 )); then
				new=$((new + 1))
			fi
		done
		if (( new > 0 )); then
			fail_current "leftover: $new new /tmp/minishell_heredoc_* file(s)"
		fi
		finish_case
	}
}

run_open_alias_builtins()
{
	section "OPEN: ALIAS-1 / BUILD-1 builtins (expected to fail until implemented)"

	# needs the real alias builtin (TODO.c stub today) + expansion path
	tp "ALIAS-1.1" "define and use an alias" \
		"alias ll='/bin/echo LL'
ll" 0 "LL"
	tp "ALIAS-1.2" "recursive alias breaks recursion" \
		"alias e='/bin/echo e'
e" 0 "e"
	tp "ALIAS-1.3" "unknown alias name -> diagnostic" \
		'alias nosuchalias_42' 1 "not found"

	# ${RO:=x} -> 124 (needs the readonly builtin through BUILD-1 dispatch)
	tp "B-ASSIGN.1" 'readonly ${R:=x} -> 124' \
		'readonly RDO_42=v
/bin/echo ${RDO_42:=other}' 124
}

run_manual_notes()
{
	section "MANUAL (cannot be automated here)"

	skip_case "MANUAL.1" "PS1/PS2 expansion + ! history number" \
		"needs a real tty (readline prompt display)"
	skip_case "MANUAL.2" "Ctrl-D at PS2 inside a quote -> syntax error, shell continues" \
		"needs a real tty"
	skip_case "MANUAL.3" "HISTFILE=/unwritable -> warning, shell keeps working" \
		"run by hand: HISTFILE=/x ./minishell -s -i"
	skip_case "MANUAL.4" "{a}<file io_location end-to-end" \
		"redirector io_location semantics unverified; try: /bin/cat {a}<redir_in"
}

###############################################################################
# Reporting
###############################################################################

summary()
{
	echo ""
	if [ "$SKIPPED" -gt 0 ]; then
		echo -e "${YELLOW}○ $SKIPPED skipped (manual)${NC}"
	fi
	if [ "$FAILED" -eq 0 ]; then
		echo -e "${GREEN}✔ $TOTAL tests passed${NC}"
		echo -e "${GRAY}Logs: $LOG_DIR${NC}"
		return 0
	fi
	echo -e "${RED}✖ $FAILED / $TOTAL tests failed${NC}"
	echo -e "${GRAY}reminder: FIXED-* red = regression; <BUG-ID> red = open bug (see BUGS_ERROR_SYSTEM.md)${NC}"
	echo -e "${YELLOW}⚠ Logs kept in: $LOG_DIR${NC}"
	return 1
}

main()
{
	check_program_exists "$MINISHELL"
	setup_logs
	setup_fixtures

	echo -e "${GREY}minishell error-system tests${NC}"
	echo -e "${GREY}binary:   $MINISHELL${NC}"
	echo -e "${GREY}logs:     $LOG_DIR${NC}"
	echo -e "${GREY}bug list: BUGS_ERROR_SYSTEM.md${NC}"
	if [ -n "$FILTER" ]; then
		echo -e "${GREY}filter:   ids starting with '$FILTER'${NC}"
	fi

	run_fixed_tokenization
	run_fixed_expander
	run_fixed_stubs
	run_open_runner_shell
	run_open_heredoc
	run_open_alias_builtins
	run_manual_notes

	teardown_fixtures
	summary
}

main
