#!/usr/bin/env zsh

###############################################################################
# minishell POSIX test harness (engine)
#
# Sourced by tests/test_posix_suite.zsh — not runnable on its own.
#
# Every test case:
#   - runs the shell with stdout and stderr captured in SEPARATE files
#   - is killed after $RUN_TIMEOUT seconds (TIMEOUT clearly reported)
#   - reports SEGFAULTS explicitly (exit 139 / SIGSEGV)
#   - can run under valgrind (--leak), leaks/errors fail the case
#   - writes a full report in tests/logs/posix_suite.N/<ID>/
#
# stderr NOTE: the default build prints unconditional debug noise on stderr
# ([PARSER]/[CMD]/[RUNNER]/[WALKER] lines, AST dumps, ### banners, and a
# trailing "end of file" line). Assertions on stderr therefore use a FILTERED
# copy (known debug patterns removed, ANSI stripped). The raw stderr is always
# kept in the case log dir as stderr.raw.txt. [TEST] lines from
# tests/test_exec survive the filter.
#
# Case API (low level):
#   t_section "title"
#   t_begin ID "label"          start a case (honors --filter)
#   t_setup 'zsh commands'      run host-side setup inside the case workdir
#   t_run 'script'              pipe script into minishell (non-interactive)
#   t_run_argv args...          run minishell with explicit argv
#                               (stdin = $T_STDIN, cleared afterwards)
#   expect_status N             exact exit status
#   expect_status_nonzero
#   expect_lines [l1 l2 ...]    stdout is EXACTLY these lines (none = empty)
#   expect_out_exact 'raw'      stdout is exactly this string (no \n added)
#   expect_out_contains 'x'     stdout contains x
#   expect_out_lacks 'x'        stdout does not contain x
#   expect_err_contains 'x'     filtered stderr contains x
#   expect_err_lacks 'x'        filtered stderr does not contain x
#   expect_err_empty            filtered stderr is empty
#   expect_file_lines f [l...]  file f (in workdir) is exactly these lines
#   expect_file_absent f        file f does not exist in workdir
#   t_end                       verdict + report
#
# Compact wrappers (one case per call):
#   tt  ID LABEL SCRIPT STATUS [line...]          exact stdout lines
#   tth ID LABEL SCRIPT STATUS NEEDLE...          stdout contains each needle
#   tte ID LABEL SCRIPT STATUS ERR_NEEDLE [line...]
#                                                 stderr needle + stdout lines
#   tta ID LABEL STATUS OUT_NEEDLE -- argv...     argv mode ('' = skip needle)
#   t_manual ID LABEL REASON                      not automatable, print note
#
# To-be-done options (-e -u -v): cases are wrapped in `td_guard ID LABEL`;
# they are OFF by default (yellow TD) and enabled with --td.
###############################################################################

emulate -R zsh
setopt NO_NOMATCH PIPE_FAIL

# ---------------------------------------------------------------------------
# Globals (set by the runner before sourcing suites)
# ---------------------------------------------------------------------------
: ${MINISHELL_ABS:?harness: MINISHELL_ABS not set}
: ${LOG_DIR:?harness: LOG_DIR not set}
: ${WORK_ROOT:?harness: WORK_ROOT not set}
: ${PROJECT_ROOT:?harness: PROJECT_ROOT not set}
: ${FILTER:=}
: ${LEAK:=0}
: ${RUN_TD:=0}
: ${RUN_TIMEOUT:=10}
: ${VG_TIMEOUT:=60}

TEST_EXEC="${PROJECT_ROOT}/tests/test_exec"
VG_SUPP="${PROJECT_ROOT}/readline.supp"
OUTPUT_CAP_BLOCKS=2048          # ulimit -f unit = 512B blocks -> 1 MiB cap

BLUE=$'\033[0;34m'
GREEN=$'\033[0;32m'
RED=$'\033[0;31m'
YELLOW=$'\033[0;33m'
GRAY=$'\033[0;90m'
MAGENTA=$'\033[0;35m'
NC=$'\033[0m'

typeset -g  TOTAL=0 FAILED=0 SKIPPED=0 TD_SKIPPED=0 SEGV_COUNT=0 TIMEOUT_COUNT=0
typeset -g  SUITE_NAME="?"
typeset -g  CURRENT_SECTION=""
typeset -gA SUITE_TOTAL SUITE_FAILED
typeset -ga FAILED_IDS

# per-case state
typeset -g T_ACTIVE=0 T_ID="" T_LABEL="" T_SCRIPT="" T_MODE="" T_STDIN=""
typeset -g T_DIR="" T_LOG="" T_RET=0 T_FAILED=0 T_SEGV=0 T_TIMEOUT=0
typeset -ga T_DETAILS T_ENV
typeset -g T_OUT_FILE T_ERR_RAW_FILE T_ERR_FILE T_EXP_OUT_FILE

# ---------------------------------------------------------------------------
# stderr filter: strip ANSI codes + known unconditional debug noise
# ---------------------------------------------------------------------------
msh_filter_stderr()
{
	sed -e $'s/\x1b\\[[0-9;]*m//g' \
		-e '/^\[PARSER\] /d' \
		-e '/^\[CMD   \] /d' \
		-e '/^\[RUNNER\] /d' \
		-e '/^\[WALKER\] /d' \
		-e '/^\[PARAMS\] /d' \
		-e '/^\[ERROR \] /d' \
		-e '/^####/d' \
		-e '/^-\{40,\}$/d' \
		-e '/^AST_ROOT/d' \
		-e '/──/d' \
		-e '/^ *│/d' \
		-e '/: end of file$/d' \
		-e '/^SPECIAL /d'
}

# ---------------------------------------------------------------------------
# Sections / filtering
# ---------------------------------------------------------------------------
t_section()
{
	CURRENT_SECTION="$1"
	echo ""
	echo -e "${GRAY}--- [$SUITE_NAME] $1 ---${NC}"
}

t_skip_by_filter()
{
	[[ -n "$FILTER" && "$1" != "$FILTER"* ]]
}

# ---------------------------------------------------------------------------
# Case lifecycle
# ---------------------------------------------------------------------------
t_begin()
{
	T_ID="$1"
	T_LABEL="$2"
	T_ACTIVE=1
	T_FAILED=0
	T_SEGV=0
	T_TIMEOUT=0
	T_RET=0
	T_SCRIPT=""
	T_MODE=""
	T_DETAILS=()
	T_ENV=()
	T_EXP_OUT_FILE=""

	if t_skip_by_filter "$T_ID"; then
		T_ACTIVE=0
		return 0
	fi
	T_DIR="${WORK_ROOT}/${T_ID//[^A-Za-z0-9._-]/_}"
	T_LOG="${LOG_DIR}/${T_ID//[^A-Za-z0-9._-]/_}"
	mkdir -p "$T_DIR" "$T_LOG" || exit 1
	T_OUT_FILE="${T_LOG}/stdout.txt"
	T_ERR_RAW_FILE="${T_LOG}/stderr.raw.txt"
	T_ERR_FILE="${T_LOG}/stderr.txt"
}

t_setup()
{
	(( T_ACTIVE )) || return 0
	( cd "$T_DIR" && eval "$1" ) >/dev/null 2>&1
}

# internal: run "$@" (already includes the shell argv) with stdin from $1
_t_exec()
{
	local stdin_data="$1"
	shift
	local tmo="$RUN_TIMEOUT"
	local -a cmd

	if (( LEAK )); then
		tmo="$VG_TIMEOUT"
		cmd=(valgrind -q --suppressions="$VG_SUPP" --leak-check=full \
			--show-leak-kinds=definite,indirect \
			--log-file="${T_LOG}/valgrind.%p.log" "$@")
	else
		cmd=("$@")
	fi
	if (( ${#T_ENV} )); then
		cmd=(env "${T_ENV[@]}" "${cmd[@]}")
	fi
	printf '%s' "$stdin_data" \
		| ( cd "$T_DIR" && ulimit -f "$OUTPUT_CAP_BLOCKS" 2>/dev/null ; \
			LC_ALL=C exec timeout --signal=KILL "$tmo" "${cmd[@]}" ) \
		> "$T_OUT_FILE" 2> "$T_ERR_RAW_FILE"
	T_RET=$?
	msh_filter_stderr < "$T_ERR_RAW_FILE" > "$T_ERR_FILE"
	if (( T_RET == 139 )); then
		T_SEGV=1
		t_fail "SEGFAULT: shell (or its pipeline) died with SIGSEGV (exit 139)"
	elif (( T_RET == 137 )); then
		# timeout --signal=KILL reports 137; the project's own 124
		# (ERR_POSIX_ASSIGNMENT) must NOT be mistaken for a timeout.
		T_TIMEOUT=1
		t_fail "TIMEOUT: killed after ${tmo}s (exit 137) — possible infinite loop"
	fi
	t_check_valgrind
}

t_run()
{
	(( T_ACTIVE )) || return 0
	T_MODE="pipe"
	T_SCRIPT="$1"
	_t_exec "$1"$'\n' "$MINISHELL_ABS"
}

t_run_argv()
{
	(( T_ACTIVE )) || return 0
	T_MODE="argv"
	T_SCRIPT="minishell $*"
	_t_exec "$T_STDIN" "$MINISHELL_ABS" "$@"
	T_STDIN=""
}

t_check_valgrind()
{
	(( LEAK )) || return 0
	local vg bad=""
	for vg in "${T_LOG}"/valgrind.*.log(N); do
		if grep -Eq "definitely lost: [1-9]|indirectly lost: [1-9]" "$vg"; then
			bad="leak"
		fi
		if grep -Eq "^==[0-9]+== (Invalid (read|write)|Conditional jump|Use of uninitialised|Syscall param)" "$vg"; then
			bad="${bad:+$bad+}error"
		fi
	done
	[[ -n "$bad" ]] && t_fail "VALGRIND ($bad): see ${T_LOG}/valgrind.*.log"
	return 0
}

t_fail()
{
	T_FAILED=1
	T_DETAILS+=("$1")
}

# ---------------------------------------------------------------------------
# Expectations
# ---------------------------------------------------------------------------
expect_status()
{
	(( T_ACTIVE )) || return 0
	if (( T_RET != $1 )); then
		t_fail "status: expected $1, got $T_RET"
	fi
}

expect_status_nonzero()
{
	(( T_ACTIVE )) || return 0
	if (( T_RET == 0 )); then
		t_fail "status: expected non-zero, got 0"
	fi
}

expect_lines()
{
	(( T_ACTIVE )) || return 0
	T_EXP_OUT_FILE="${T_LOG}/stdout.expected.txt"
	if (( $# )); then
		printf '%s\n' "$@" > "$T_EXP_OUT_FILE"
	else
		: > "$T_EXP_OUT_FILE"
	fi
	if ! cmp -s "$T_EXP_OUT_FILE" "$T_OUT_FILE"; then
		t_fail "stdout: differs from expected (see report)"
	fi
}

expect_out_exact()
{
	(( T_ACTIVE )) || return 0
	T_EXP_OUT_FILE="${T_LOG}/stdout.expected.txt"
	printf '%s' "$1" > "$T_EXP_OUT_FILE"
	if ! cmp -s "$T_EXP_OUT_FILE" "$T_OUT_FILE"; then
		t_fail "stdout: differs from expected (see report)"
	fi
}

expect_out_contains()
{
	(( T_ACTIVE )) || return 0
	if [[ "$(<$T_OUT_FILE)" != *"$1"* ]]; then
		t_fail "stdout: expected to contain '$1'"
	fi
}

expect_out_lacks()
{
	(( T_ACTIVE )) || return 0
	if [[ "$(<$T_OUT_FILE)" == *"$1"* ]]; then
		t_fail "stdout: expected NOT to contain '$1'"
	fi
}

expect_err_contains()
{
	(( T_ACTIVE )) || return 0
	if [[ "$(<$T_ERR_FILE)" != *"$1"* ]]; then
		t_fail "stderr: expected to contain '$1'"
	fi
}

expect_err_lacks()
{
	(( T_ACTIVE )) || return 0
	if [[ "$(<$T_ERR_FILE)" == *"$1"* ]]; then
		t_fail "stderr: expected NOT to contain '$1'"
	fi
}

expect_err_empty()
{
	(( T_ACTIVE )) || return 0
	if [[ -s "$T_ERR_FILE" ]]; then
		t_fail "stderr: expected empty (after debug filtering), got content"
	fi
}

expect_file_lines()
{
	(( T_ACTIVE )) || return 0
	local f="$T_DIR/$1"
	shift
	if [[ ! -f "$f" ]]; then
		t_fail "file: expected '$f' to exist"
		return 0
	fi
	local exp="${T_LOG}/file.expected.txt"
	if (( $# )); then
		printf '%s\n' "$@" > "$exp"
	else
		: > "$exp"
	fi
	if ! cmp -s "$exp" "$f"; then
		t_fail "file ${1}: content differs (expected: $(printf '%s ' "$@"))"
	fi
}

expect_file_absent()
{
	(( T_ACTIVE )) || return 0
	if [[ -e "$T_DIR/$1" ]]; then
		t_fail "file: expected '$1' to NOT exist"
	fi
}

# ---------------------------------------------------------------------------
# Verdict + report
# ---------------------------------------------------------------------------
_t_report_file()
{
	local exp_status="$1"
	{
		echo "### ID / LABEL ###"
		echo "[$T_ID] $T_LABEL"
		echo "### SECTION ###"
		echo "[$SUITE_NAME] $CURRENT_SECTION"
		echo ""
		echo "### COMMAND ($T_MODE mode) ###"
		printf '%s\n' "$T_SCRIPT"
		echo ""
		echo "### EXIT STATUS (obtained) ###"
		echo "$T_RET"
		echo ""
		echo "### EXPECTED STDOUT ###"
		if [[ -n "$T_EXP_OUT_FILE" && -f "$T_EXP_OUT_FILE" ]]; then
			cat "$T_EXP_OUT_FILE"
		else
			echo "(no exact stdout expectation — see details)"
		fi
		echo ""
		echo "### OBTAINED STDOUT ###"
		cat "$T_OUT_FILE"
		echo ""
		echo "### OBTAINED STDERR (filtered) ###"
		cat "$T_ERR_FILE"
		echo ""
		echo "### VERDICT ###"
		if (( T_FAILED )); then
			printf 'FAIL\n'
			printf '  - %s\n' "${T_DETAILS[@]}"
		else
			echo "PASS"
		fi
	} > "${T_LOG}/report.txt"
	printf '%s\n' "$T_SCRIPT" > "${T_LOG}/script.txt"
}

# print at most N lines of a file, indented
_t_print_block()
{
	local file="$1" indent="$2" max=12 n=0 line
	while IFS= read -r line; do
		n=$((n + 1))
		if (( n > max )); then
			printf '%s%s\n' "$indent" "${GRAY}(... truncated, see log)${NC}"
			break
		fi
		printf '%s%s\n' "$indent" "$line"
	done < "$file"
	if (( n == 0 )); then
		printf '%s%s\n' "$indent" "${GRAY}(empty)${NC}"
	fi
}

t_end()
{
	(( T_ACTIVE )) || return 0
	T_ACTIVE=0
	TOTAL=$((TOTAL + 1))
	SUITE_TOTAL[$SUITE_NAME]=$(( ${SUITE_TOTAL[$SUITE_NAME]:-0} + 1 ))
	_t_report_file

	if (( T_FAILED == 0 )); then
		printf "${GREEN}✔${NC} [%s] ${BLUE}%s${NC}\n" "$T_ID" "$T_LABEL"
		return 0
	fi

	FAILED=$((FAILED + 1))
	SUITE_FAILED[$SUITE_NAME]=$(( ${SUITE_FAILED[$SUITE_NAME]:-0} + 1 ))
	FAILED_IDS+=("$T_ID")
	(( T_SEGV )) && SEGV_COUNT=$((SEGV_COUNT + 1))
	(( T_TIMEOUT )) && TIMEOUT_COUNT=$((TIMEOUT_COUNT + 1))

	local tag=""
	(( T_SEGV )) && tag=" ${MAGENTA}[SEGFAULT]${NC}"
	(( T_TIMEOUT )) && tag=" ${MAGENTA}[TIMEOUT]${NC}"
	printf "${RED}✖${NC} [%s] ${BLUE}%s${NC}%s\n" "$T_ID" "$T_LABEL" "$tag"

	local first=1 line
	while IFS= read -r line; do
		if (( first )); then
			printf "      ${GRAY}command${NC}  : %s\n" "$line"
			first=0
		else
			printf "               %s\n" "$line"
		fi
	done <<< "$T_SCRIPT"

	local d
	for d in "${T_DETAILS[@]}"; do
		printf "      ${RED}%s${NC}\n" "$d"
	done
	if [[ -n "$T_EXP_OUT_FILE" && -f "$T_EXP_OUT_FILE" ]] \
		&& ! cmp -s "$T_EXP_OUT_FILE" "$T_OUT_FILE"; then
		printf "      ${GRAY}expected stdout:${NC}\n"
		_t_print_block "$T_EXP_OUT_FILE" "        | "
		printf "      ${GRAY}obtained stdout:${NC}\n"
		_t_print_block "$T_OUT_FILE" "        | "
	fi
	if [[ -s "$T_ERR_FILE" ]]; then
		printf "      ${GRAY}obtained stderr (filtered):${NC}\n"
		_t_print_block "$T_ERR_FILE" "        | "
	fi
	printf "      ${GRAY}log${NC}      : %s\n" "${T_LOG}/report.txt"
	return 1
}

# ---------------------------------------------------------------------------
# Compact wrappers
# ---------------------------------------------------------------------------

# tt ID LABEL SCRIPT STATUS [line...] — pipe mode, exact status + exact stdout
tt()
{
	local id="$1" label="$2" script="$3" st="$4"
	shift 4
	t_begin "$id" "$label"
	t_run "$script"
	expect_status "$st"
	expect_lines "$@"
	t_end
}

# tth ID LABEL SCRIPT STATUS NEEDLE... — pipe mode, stdout contains needles
tth()
{
	local id="$1" label="$2" script="$3" st="$4" n
	shift 4
	t_begin "$id" "$label"
	t_run "$script"
	expect_status "$st"
	for n in "$@"; do
		expect_out_contains "$n"
	done
	t_end
}

# tte ID LABEL SCRIPT STATUS ERR_NEEDLE [line...] — stderr needle + stdout
tte()
{
	local id="$1" label="$2" script="$3" st="$4" err="$5"
	shift 5
	t_begin "$id" "$label"
	t_run "$script"
	if [[ "$st" == "!0" ]]; then
		expect_status_nonzero
	else
		expect_status "$st"
	fi
	[[ -n "$err" ]] && expect_err_contains "$err"
	(( $# )) && expect_lines "$@"
	t_end
}

# tta ID LABEL STATUS OUT_NEEDLE -- argv... — argv mode ('' skips the needle)
tta()
{
	local id="$1" label="$2" st="$3" needle="$4"
	shift 4
	[[ "$1" == "--" ]] && shift
	t_begin "$id" "$label"
	t_run_argv "$@"
	expect_status "$st"
	[[ -n "$needle" ]] && expect_out_contains "$needle"
	t_end
}

t_manual()
{
	local id="$1" label="$2" reason="$3"
	t_skip_by_filter "$id" && return 0
	SKIPPED=$((SKIPPED + 1))
	printf "${YELLOW}○${NC} [%s] ${BLUE}%s${NC} ${GRAY}manual: %s${NC}\n" \
		"$id" "$label" "$reason"
}

# td_guard ID LABEL — returns 0 (= run the guarded block) only with --td.
# Usage:   td_guard OPT-E.1 "errexit exits on failure" && {
#              tt OPT-E.1 ... ; }
td_guard()
{
	local id="$1" label="$2"
	if (( RUN_TD )); then
		return 0
	fi
	t_skip_by_filter "$id" && return 1
	TD_SKIPPED=$((TD_SKIPPED + 1))
	printf "${YELLOW}◌${NC} [%s] ${BLUE}%s${NC} ${GRAY}TD: option not implemented — enable with --td${NC}\n" \
		"$id" "$label"
	return 1
}

# ---------------------------------------------------------------------------
# Summary
# ---------------------------------------------------------------------------
t_summary()
{
	local s
	echo ""
	echo -e "${GRAY}==================== SUMMARY ====================${NC}"
	for s in ${(k)SUITE_TOTAL}; do
		local tot=${SUITE_TOTAL[$s]} bad=${SUITE_FAILED[$s]:-0}
		if (( bad )); then
			printf "  %-10s ${RED}%d failed${NC} / %d\n" "$s" "$bad" "$tot"
		else
			printf "  %-10s ${GREEN}all %d passed${NC}\n" "$s" "$tot"
		fi
	done
	(( TD_SKIPPED )) && echo -e "  ${YELLOW}◌ $TD_SKIPPED TD cases skipped (options not implemented; --td to run)${NC}"
	(( SKIPPED )) && echo -e "  ${YELLOW}○ $SKIPPED manual cases skipped${NC}"
	(( SEGV_COUNT )) && echo -e "  ${MAGENTA}⚠ $SEGV_COUNT SEGFAULT(s)${NC}"
	(( TIMEOUT_COUNT )) && echo -e "  ${MAGENTA}⚠ $TIMEOUT_COUNT TIMEOUT(s)${NC}"
	echo ""
	{
		echo "minishell POSIX suite — $(date)"
		echo "binary: $MINISHELL_ABS"
		echo "total: $TOTAL  failed: $FAILED  segv: $SEGV_COUNT  timeout: $TIMEOUT_COUNT"
		(( ${#FAILED_IDS} )) && printf 'failed: %s\n' "${FAILED_IDS[@]}"
	} > "${LOG_DIR}/summary.txt"
	if (( FAILED == 0 )); then
		echo -e "${GREEN}✔ $TOTAL tests passed${NC}"
		echo -e "${GRAY}Logs: $LOG_DIR${NC}"
		return 0
	fi
	echo -e "${RED}✖ $FAILED / $TOTAL tests failed${NC}"
	echo -e "${GRAY}failed IDs: ${FAILED_IDS[*]}${NC}"
	echo -e "${YELLOW}⚠ Logs kept in: $LOG_DIR${NC}"
	return 1
}
