#!/usr/bin/env zsh

###############################################################################
# minishell POSIX behavior test suite — main runner
#
# Usage from the project root:
#   tests/test_posix_suite.zsh [path/to/minishell] [options]
#
# Options:
#   --leak            run every case under valgrind (leaks fail the case)
#   --td              also run the TD cases (-e/-u/-v, not implemented yet)
#   --filter PREFIX   only run cases whose ID starts with PREFIX
#   --suite LIST      comma-separated: options,builtins,ast,complex,custom
#   --timeout N       per-case timeout in seconds (default 20; 60 with --leak)
#                     NOTE: the shell currently burns ~2.6s of CPU at startup
#                     (before reading any input), so keep timeouts generous.
#   --list            list suites and exit
#
# Examples:
#   tests/test_posix_suite.zsh                          # everything
#   tests/test_posix_suite.zsh --suite builtins         # one suite
#   tests/test_posix_suite.zsh minishell --filter CD-   # only cd cases
#   tests/test_posix_suite.zsh --leak                   # valgrind run
#
# Add your own cases in tests/suites/90_custom.zsh (see examples there).
#
# Suites (tests/suites/):
#   10_options.zsh    shell options: -a -C -e -f -h -i -n -u -v -x -c -s,
#                     -o pipefail, -o ignoreeof, set/+o management
#   20_builtins.zsh   alias cd unalias wait echo pwd env readonly : set
#                     trap exit unset export (+ special-builtin semantics)
#   30_ast.zsh        one section per AST node type: simple command,
#                     pipeline, and-or, list/&, subshell, brace group,
#                     if, while/until, for, case, function, redirections
#   40_complex.zsh    nested combinations of everything above
#   90_custom.zsh     your own scratchpad cases
#
# Per-case logs: tests/logs/posix_suite.N/<ID>/
#   report.txt          command + expected/obtained stdout/stderr + verdict
#   stdout.txt          raw captured stdout
#   stderr.raw.txt      raw captured stderr (includes debug noise)
#   stderr.txt          stderr after debug-noise filtering (what is asserted)
#   stdout.expected.txt exact expectation, when the case uses one
#   valgrind.*.log      with --leak
###############################################################################

emulate -R zsh
setopt NO_NOMATCH

SCRIPT_DIR="${0:A:h}"
PROJECT_ROOT="${SCRIPT_DIR:h}"
SUITES_DIR="${SCRIPT_DIR}/suites"

MINISHELL="./minishell"
FILTER=""
LEAK=0
RUN_TD=0
# NOTE: the shell burns ~2.6s of pure CPU at startup (before reading input);
# under valgrind (~30x) that alone is 1-2 minutes per case, hence the large
# VG_TIMEOUT. Prefer --leak together with --filter/--suite until fixed.
RUN_TIMEOUT=20
VG_TIMEOUT=300
SUITE_SEL="options,builtins,ast,complex,custom"

while (( $# )); do
	case "$1" in
		--leak)     LEAK=1 ;;
		--td)       RUN_TD=1 ;;
		--filter)   shift; FILTER="$1" ;;
		--suite)    shift; SUITE_SEL="$1" ;;
		--timeout)  shift; RUN_TIMEOUT="$1"; VG_TIMEOUT="$1" ;;
		--list)
			echo "suites: options builtins ast complex custom"
			exit 0 ;;
		-*)
			echo "unknown option: $1" >&2
			exit 2 ;;
		*)          MINISHELL="$1" ;;
	esac
	shift
done

if [[ "$MINISHELL" != */* ]]; then
	MINISHELL="./$MINISHELL"
fi
MINISHELL_ABS="${MINISHELL:A}"

if [[ ! -x "$MINISHELL_ABS" ]]; then
	echo "✖ Error: $MINISHELL not found or not executable (run make first)" >&2
	exit 1
fi
if (( LEAK )) && ! command -v valgrind >/dev/null; then
	echo "✖ Error: --leak requested but valgrind is not installed" >&2
	exit 1
fi

# build the test_exec helper if needed (also rebuilds a foreign-arch binary,
# e.g. a Mach-O test_exec committed from a mac)
if [[ ! -x "${SCRIPT_DIR}/test_exec" || "${SCRIPT_DIR}/test_exec.c" -nt "${SCRIPT_DIR}/test_exec" ]] \
	|| ! "${SCRIPT_DIR}/test_exec" >/dev/null 2>&1 </dev/null; then
	cc -Wall -Wextra -o "${SCRIPT_DIR}/test_exec" "${SCRIPT_DIR}/test_exec.c" || exit 1
fi

# log dir: tests/logs/posix_suite.N (first free N)
LOG_ROOT="${SCRIPT_DIR}/logs"
mkdir -p "$LOG_ROOT" || exit 1
n=1
while [[ -e "${LOG_ROOT}/posix_suite.${n}" ]]; do
	n=$((n + 1))
done
LOG_DIR="${LOG_ROOT}/posix_suite.${n}"
mkdir -p "$LOG_DIR" || exit 1

WORK_ROOT="${SCRIPT_DIR}/fixtures/posix_suite"
rm -rf "$WORK_ROOT"
mkdir -p "$WORK_ROOT" || exit 1

source "${SUITES_DIR}/harness.zsh"

echo -e "${GRAY}minishell POSIX suite${NC}"
echo -e "${GRAY}binary : $MINISHELL_ABS${NC}"
echo -e "${GRAY}logs   : $LOG_DIR${NC}"
(( LEAK ))   && echo -e "${GRAY}mode   : valgrind (--leak), timeout ${VG_TIMEOUT}s${NC}"
[[ -n "$FILTER" ]] && echo -e "${GRAY}filter : ids starting with '$FILTER'${NC}"

for s in ${(s:,:)SUITE_SEL}; do
	case "$s" in
		options)  SUITE_NAME="options";  source "${SUITES_DIR}/10_options.zsh" ;;
		builtins) SUITE_NAME="builtins"; source "${SUITES_DIR}/20_builtins.zsh" ;;
		ast)      SUITE_NAME="ast";      source "${SUITES_DIR}/30_ast.zsh" ;;
		complex)  SUITE_NAME="complex";  source "${SUITES_DIR}/40_complex.zsh" ;;
		custom)   SUITE_NAME="custom";   source "${SUITES_DIR}/90_custom.zsh" ;;
		*)        echo "unknown suite: $s" >&2; exit 2 ;;
	esac
done

t_summary
