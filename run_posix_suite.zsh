#!/usr/bin/env zsh

###############################################################################
# Download and run the minishell POSIX test suite from a 42 submission repo.
#
# From the directory containing the minishell binary:
#   curl -fsSL \
#     https://raw.githubusercontent.com/Eraz19/minishell/submission/run_posix_suite.zsh \
#     | zsh -s -- [path/to/minishell] [test_posix_suite options]
#
# Examples:
#   curl -fsSL "$URL" | zsh
#   curl -fsSL "$URL" | zsh -s -- ./minishell --suite builtins
#   curl -fsSL "$URL" | zsh -s -- ./minishell --filter CD-
#
# The downloaded suite and its reports are kept in:
#   .minishell-posix-suite/tests/logs/
#
# Optional environment overrides:
#   MINISHELL_TEST_REPO      GitHub owner/repository (default: Eraz19/minishell)
#   MINISHELL_TEST_REF       branch, tag or commit (default: submission)
#   MINISHELL_TEST_DIR       local download directory
#   MINISHELL_TEST_BASE_URL  complete raw-content base URL (useful for mirrors)
###############################################################################

emulate -R zsh
setopt ERR_EXIT NO_UNSET PIPE_FAIL

typeset -r DEFAULT_REPO="Eraz19/minishell"
typeset -r DEFAULT_REF="submission"
typeset -r DEFAULT_DIR="${PWD}/.minishell-posix-suite"

typeset repo="${MINISHELL_TEST_REPO:-$DEFAULT_REPO}"
typeset ref="${MINISHELL_TEST_REF:-$DEFAULT_REF}"
typeset suite_dir="${MINISHELL_TEST_DIR:-$DEFAULT_DIR}"
typeset base_url="${MINISHELL_TEST_BASE_URL:-https://raw.githubusercontent.com/${repo}/${ref}}"
typeset minishell="./minishell"
typeset staging=""

typeset -ra suite_files=(
	readline.supp
	tests/test_exec.c
	tests/test_posix_suite.zsh
	tests/suites/harness.zsh
	tests/suites/10_options.zsh
	tests/suites/20_builtins.zsh
	tests/suites/30_ast.zsh
	tests/suites/40_complex.zsh
	tests/suites/50_words.zsh
	tests/suites/60_semantics.zsh
	tests/suites/90_custom.zsh
)

die()
{
	print -u2 -r -- "posix-suite: $*"
	exit 1
}

cleanup()
{
	if [[ -n "$staging" && -d "$staging" ]]; then
		rm -rf -- "$staging"
	fi
}

download_file()
{
	typeset relative="$1"
	typeset destination="$2"

	if (( $+commands[curl] )); then
		curl -fsSL --retry 3 --connect-timeout 10 \
			"${base_url}/${relative}" -o "$destination"
	elif (( $+commands[wget] )); then
		wget -q --tries=3 --timeout=10 \
			"${base_url}/${relative}" -O "$destination"
	else
		die "curl or wget is required to download the test suite"
	fi
}

trap cleanup EXIT HUP INT TERM

if (( $# > 0 )) && [[ "$1" != -* ]]; then
	minishell="$1"
	shift
fi
minishell="${minishell:A}"

[[ -x "$minishell" ]] \
	|| die "${minishell} is not executable; build minishell first"
(( $+commands[cc] )) || die "cc is required to build tests/test_exec.c"
(( $+commands[timeout] )) \
	|| die "timeout is required (install coreutils on macOS)"

staging="$(mktemp -d "${TMPDIR:-/tmp}/minishell-posix-suite.XXXXXX")" \
	|| die "could not create a temporary download directory"

print -r -- "Downloading minishell POSIX suite (${repo}@${ref})..."
for relative in "${suite_files[@]}"; do
	mkdir -p -- "$staging/${relative:h}"
	download_file "$relative" "$staging/$relative" \
		|| die "failed to download ${relative} from ${base_url}"
done

for relative in "${suite_files[@]}"; do
	mkdir -p -- "$suite_dir/${relative:h}"
	mv -f -- "$staging/$relative" "$suite_dir/$relative"
done
cleanup
staging=""

print -r -- "Tests installed in: $suite_dir"
print -r -- "Running against:    $minishell"
print -r -- ""

zsh "$suite_dir/tests/test_posix_suite.zsh" "$minishell" "$@"
