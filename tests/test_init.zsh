#!/usr/bin/env zsh

###############################################################################
# minishell initialization dump tests
#
# Usage:
#   ./test_minishell_init.zsh [path/to/minishell]
#
# The tested shell is expected to dump initialization state only; these tests do
# not require parser/runner execution. Every invocation redirects stdin from
# /dev/null so the test runner does not block if execution later becomes enabled.
#
# Assumed dump formats:
#   VAR name='NAME' value='VALUE' exported=true readonly=false
#   OPTION e=true
#   SPECIAL ?=0
#   POSITIONALS #=2
#   PARAMS 'NAME'='VALUE'
#
# IFS is intentionally matched with a dedicated multi-line literal because its
# value is <space><tab><newline> and the dump does not escape values.
# PARAMS '-' checks never require c or s because POSIX leaves their presence
# in $- unspecified.
###############################################################################

emulate -R zsh
setopt NO_NOMATCH

MINISHELL="${1:-./minishell}"
if [[ "$MINISHELL" != */* ]]; then
	MINISHELL="./$MINISHELL"
fi

BLUE=$'\033[0;34m'
GREEN=$'\033[0;32m'
RED=$'\033[0;31m'
YELLOW=$'\033[0;33m'
GRAY=$'\033[0;90m'
NC=$'\033[0m'
GREY=$'\033[0;90m'

COL1_WIDTH=54
COL2_WIDTH=25

LOG_DIR="${TMPDIR:-/tmp}/minishell_init_tests.$$"
SCRIPT_FILE="${LOG_DIR}/script.sh"
PLUS_SCRIPT_FILE="${LOG_DIR}/+script.sh"

TOTAL=0
FAILED=0

CURRENT_ID=""
CURRENT_INVOCATION=""
CURRENT_SCOPE=""
CURRENT_MSG=""
CURRENT_LOG=""
OUTPUT=""
RET=0
CASE_FAILED=0
CASE_DETAILS=()

cleanup()
{
	if [ "$FAILED" -eq 0 ]; then
		rm -rf "$LOG_DIR"
	else
		echo ""
		echo -e "${YELLOW}⚠ Logs kept in: $LOG_DIR${NC}"
	fi
}

trap cleanup EXIT

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

setup_files()
{
	mkdir -p "$LOG_DIR" || {
		echo -e "${RED}✖ Error: cannot create log dir: $LOG_DIR${NC}"
		exit 1
	}

	printf ':\n' > "$SCRIPT_FILE"
	printf ':\n' > "$PLUS_SCRIPT_FILE"
}

section()
{
	local title="$1"

	echo ""
	echo -e "${GREY}--- $title ---${NC}\n"
}

print_result()
{
	local status="$1"
	local color="$2"
	local symbol="$3"

	local col1=$(printf "%-${COL1_WIDTH}s" "$CURRENT_INVOCATION")
	local col2=$(printf "%-${COL2_WIDTH}s" "$CURRENT_SCOPE")

	printf "Test %s: ${BLUE}%s${NC} ⇢ %s ⇢ %s ${GRAY}...${NC} ${color}%s${NC}\n" \
		"$CURRENT_ID" "$col1" "$col2" "$CURRENT_MSG" "$symbol"

	if [ "$status" != "ok" ]; then
		for detail in "${CASE_DETAILS[@]}"; do
			echo -e "    ${RED}${detail}${NC}"
		done
		echo -e "    ${GRAY}Dump: $CURRENT_LOG${NC}"
	fi
}

begin_case()
{
	CURRENT_ID="$1"
	CURRENT_INVOCATION="$2"
	CURRENT_SCOPE="$3"
	CURRENT_MSG="$4"
	shift 4

	CASE_FAILED=0
	CASE_DETAILS=()
	CURRENT_LOG="${LOG_DIR}/test_${CURRENT_ID// /_}.log"

	"$@" < /dev/null > "$CURRENT_LOG" 2>&1
	RET=$?
	OUTPUT="$(< "$CURRENT_LOG")"

	expect_ret 0
}

finish_case()
{
	TOTAL=$((TOTAL + 1))

	if [ "$CASE_FAILED" -eq 0 ]; then
		print_result "ok" "$GREEN" "✔"
		return 0
	fi

	FAILED=$((FAILED + 1))
	print_result "ko" "$RED" "✖"
	return 1
}

fail_current()
{
	CASE_FAILED=1
	CASE_DETAILS+=("$1")
}

expect_ret()
{
	local expected="$1"

	if [ "$RET" -ne "$expected" ]; then
		fail_current "return code: got $RET, expected $expected"
	fi
}

expect_contains()
{
	local needle="$1"
	local label="$2"

	if [[ "$OUTPUT" != *"$needle"* ]]; then
		fail_current "missing: $label"
	fi
}

expect_not_contains()
{
	local needle="$1"
	local label="$2"

	if [[ "$OUTPUT" == *"$needle"* ]]; then
		fail_current "unexpected: $label"
	fi
}

expect_var()
{
	local name="$1"
	local value="$2"
	local exported="$3"
	local readonly="$4"

	expect_contains \
		"VAR name='${name}' value='${value}' exported=${exported} readonly=${readonly}" \
		"VARIABLES ${name}=${value} exported=${exported} readonly=${readonly}"
}

expect_no_var()
{
	local name="$1"

	expect_not_contains "VAR name='${name}' " "VARIABLES must not contain ${name}"
	expect_not_contains "PARAMS '${name}'=" "PARAMS must not contain ${name}"
}

expect_param()
{
	local name="$1"
	local value="$2"

	expect_contains "PARAMS '${name}'='${value}'" "PARAMS ${name}=${value}"
}

expect_param_null()
{
	local name="$1"

	expect_contains "PARAMS '${name}'=NULL" "PARAMS ${name}=NULL"
}

expect_option()
{
	local name="$1"
	local value="$2"

	expect_contains "OPTION ${name}=${value}" "OPTIONS ${name}=${value}"
}

expect_special_raw()
{
	local name="$1"
	local value="$2"

	expect_contains "SPECIAL ${name}=${value}" "SPECIAL ${name}=${value}"
}

expect_special_string()
{
	local name="$1"
	local value="$2"

	expect_contains "SPECIAL ${name}='${value}'" "SPECIAL ${name}=${value}"
}

expect_positionals_count()
{
	local count="$1"

	expect_contains "POSITIONALS #=${count}" "POSITIONALS #=${count}"
	expect_param "#" "$count"
}

expect_positional()
{
	local index="$1"
	local value="$2"

	if [[ "$OUTPUT" != *"POSITIONAL ${index}='${value}'"* ]] \
		&& [[ "$OUTPUT" != *"POSITIONALS ${index}='${value}'"* ]] \
		&& [[ "$OUTPUT" != *"POSITIONAL index=${index} value='${value}'"* ]] \
		&& [[ "$OUTPUT" != *"POSITIONAL[${index}]='${value}'"* ]]; then
		fail_current "missing POSITIONALS entry for \$${index}='${value}'"
	fi

	expect_param "$index" "$value"
}

expect_ifs_default()
{
	local ifs_default=$' \t\n'
	local var_line="VAR name='IFS' value='${ifs_default}' exported=false readonly=false"
	local param_line="PARAMS 'IFS'='${ifs_default}'"

	expect_contains "$var_line" "VARIABLES IFS=<space><tab><newline> exported=false readonly=false"
	expect_contains "$param_line" "PARAMS IFS=<space><tab><newline>"
}

get_dash_flags()
{
	if [[ "$OUTPUT" =~ "PARAMS '-'='([^']*)'" ]]; then
		printf '%s' "$match[1]"
		return 0
	fi
	return 1
}

expect_dash_has()
{
	local flag="$1"
	local flags

	flags="$(get_dash_flags)"
	if [ $? -ne 0 ]; then
		fail_current "missing PARAMS '-'"
		return
	fi

	if [[ "$flags" != *"$flag"* ]]; then
		fail_current "PARAMS '-'='$flags' does not contain '$flag'"
	fi
}

expect_dash_lacks()
{
	local flag="$1"
	local flags

	flags="$(get_dash_flags)"
	if [ $? -ne 0 ]; then
		fail_current "missing PARAMS '-'"
		return
	fi

	if [[ "$flags" == *"$flag"* ]]; then
		fail_current "PARAMS '-'='$flags' unexpectedly contains '$flag'"
	fi
}

expect_pid_consistency()
{
	local special_pid=""
	local params_pid=""

	if [[ "$OUTPUT" =~ 'SPECIAL \$=([0-9]+)' ]]; then
		special_pid="$match[1]"
	else
		fail_current "missing numeric SPECIAL $"
		return
	fi

	if [[ "$OUTPUT" =~ "PARAMS '\\$'='([0-9]+)'" ]]; then
		params_pid="$match[1]"
	else
		fail_current "missing numeric PARAMS '$'"
		return
	fi

	if [ "$special_pid" != "$params_pid" ]; then
		fail_current "SPECIAL \$=$special_pid but PARAMS '$'=$params_pid"
	fi
}

test_imported_var()
{
	begin_case "V01" "env -i TEST_VAR=alpha $MINISHELL -c ':'" "variables" \
		"imports valid env var" \
		env -i TEST_VAR=alpha "$MINISHELL" -c ":"

	expect_var "TEST_VAR" "alpha" "true" "false"
	expect_param "TEST_VAR" "alpha"
	finish_case
}

test_empty_var()
{
	begin_case "V02" "env -i EMPTY= $MINISHELL -c ':'" "variables" \
		"imports empty env var" \
		env -i EMPTY= "$MINISHELL" -c ":"

	expect_var "EMPTY" "" "true" "false"
	expect_param "EMPTY" ""
	finish_case
}

test_complex_value_var()
{
	begin_case "V03" "env -i MIXED='a b=c:d' $MINISHELL -c ':'" "variables" \
		"preserves ordinary bytes" \
		env -i "MIXED=a b=c:d" "$MINISHELL" -c ":"

	expect_var "MIXED" "a b=c:d" "true" "false"
	expect_param "MIXED" "a b=c:d"
	finish_case
}

test_invalid_env_names()
{
	begin_case "V04" "env -i GOOD=ok 1BAD=no BAD-NAME=no $MINISHELL -c ':'" "variables" \
		"ignores invalid env names" \
		env -i GOOD=ok "1BAD=no" "BAD-NAME=no" "$MINISHELL" -c ":"

	expect_var "GOOD" "ok" "true" "false"
	expect_param "GOOD" "ok"
	expect_no_var "1BAD"
	expect_no_var "BAD-NAME"
	finish_case
}

test_ifs_reset()
{
	begin_case "V05" "env -i IFS=evil $MINISHELL -c ':'" "variables" \
		"resets IFS on invocation" \
		env -i IFS=evil "$MINISHELL" -c ":"

	expect_ifs_default
	expect_not_contains "VAR name='IFS' value='evil'" "IFS must not keep env value"
	expect_not_contains "PARAMS 'IFS'='evil'" "PARAMS IFS must not keep env value"
	finish_case
}

test_ppid()
{
	local expected_ppid="$$"

	begin_case "V06" "env -i $MINISHELL -c ':'" "variables" \
		"initializes PPID" \
		env -i "$MINISHELL" -c ":"

	expect_var "PPID" "$expected_ppid" "false" "false"
	expect_param "PPID" "$expected_ppid"
	finish_case
}

test_prompt_var()
{
	local id="$1"
	local name="$2"
	local value="$3"

	begin_case "$id" "env -i $MINISHELL -c ':'" "variables" \
		"initializes ${name}" \
		env -i "$MINISHELL" -c ":"

	expect_var "$name" "$value" "false" "false"
	expect_param "$name" "$value"
	finish_case
}

test_default_options_stdin()
{
	begin_case "O01" "env -i $MINISHELL" "options" \
		"defaults to stdin mode" \
		env -i "$MINISHELL"

	expect_option "s" "true"
	expect_option "c" "false"
	expect_option "i" "false"
	expect_option "a" "false"
	expect_option "b" "false"
	expect_option "C" "false"
	expect_option "e" "false"
	expect_option "f" "false"
	expect_option "h" "false"
	expect_option "n" "false"
	expect_option "u" "false"
	expect_option "v" "false"
	expect_option "x" "false"
	expect_option "ignoreeof" "false"
	expect_option "nolog" "false"
	expect_option "pipefail" "false"
	expect_option "vi" "false"
	expect_special_raw "source" "NULL"
	finish_case
}

test_c_option()
{
	begin_case "O02" "env -i $MINISHELL -c 'echo hello'" "options/source" \
		"initializes command_string source" \
		env -i "$MINISHELL" -c "echo hello"

	expect_option "c" "true"
	expect_option "s" "false"
	expect_special_string "source" "echo hello"
	finish_case
}

test_s_option()
{
	begin_case "O03" "env -i $MINISHELL -s arg1" "options" \
		"explicit stdin mode" \
		env -i "$MINISHELL" -s arg1

	expect_option "s" "true"
	expect_option "c" "false"
	expect_special_raw "source" "NULL"
	expect_positionals_count "1"
	expect_positional "1" "arg1"
	finish_case
}

test_short_option()
{
	local id="$1"
	local flag="$2"

	begin_case "$id" "env -i $MINISHELL -${flag} -c ':'" "options" \
		"sets -${flag}" \
		env -i "$MINISHELL" "-${flag}" -c ":"

	expect_option "$flag" "true"
	expect_dash_has "$flag"
	finish_case
}

test_long_option()
{
	local id="$1"
	local optname="$2"
	local dump_name="$3"

	begin_case "$id" "env -i $MINISHELL -o ${optname} -c ':'" "options" \
		"sets -o ${optname}" \
		env -i "$MINISHELL" -o "$optname" -c ":"

	expect_option "$dump_name" "true"
	finish_case
}

test_long_alias_option()
{
	local id="$1"
	local optname="$2"
	local dump_name="$3"
	local dash_flag="$4"

	begin_case "$id" "env -i $MINISHELL -o ${optname} -c ':'" "options" \
		"sets -o ${optname}" \
		env -i "$MINISHELL" -o "$optname" -c ":"

	expect_option "$dump_name" "true"
	expect_dash_has "$dash_flag"
	finish_case
}

test_plus_option_turns_off()
{
	begin_case "O23" "env -i $MINISHELL -e +e -c ':'" "options" \
		"+e overrides -e" \
		env -i "$MINISHELL" -e +e -c ":"

	expect_option "e" "false"
	expect_dash_lacks "e"
	finish_case
}

test_option_order_last_wins()
{
	begin_case "O24" "env -i $MINISHELL +e -e -c ':'" "options" \
		"last option wins" \
		env -i "$MINISHELL" +e -e -c ":"

	expect_option "e" "true"
	expect_dash_has "e"
	finish_case
}

test_plus_long_option_turns_off()
{
	begin_case "O25" "env -i $MINISHELL -o pipefail +o pipefail -c ':'" "options" \
		"+o reverses -o" \
		env -i "$MINISHELL" -o pipefail +o pipefail -c ":"

	expect_option "pipefail" "false"
	finish_case
}

test_special_status()
{
	begin_case "S01" "env -i $MINISHELL -c ':'" "specials" \
		"initializes \$? to 0" \
		env -i "$MINISHELL" -c ":"

	expect_special_raw "?" "0"
	expect_param "?" "0"
	finish_case
}

test_special_bang_unset()
{
	begin_case "S02" "env -i $MINISHELL -c ':'" "specials" \
		"abstracts \$! unset" \
		env -i "$MINISHELL" -c ":"

	expect_special_raw "!" "-1"
	expect_param_null "!"
	finish_case
}

test_special_pid()
{
	begin_case "S03" "env -i $MINISHELL -c ':'" "specials" \
		"keeps \$\$ consistent" \
		env -i "$MINISHELL" -c ":"

	expect_pid_consistency
	finish_case
}

test_zero_no_operand()
{
	begin_case "S04" "env -i $MINISHELL" "specials" \
		"sets \$0 to argv[0]" \
		env -i "$MINISHELL"

	expect_special_string "0" "$MINISHELL"
	expect_param "0" "$MINISHELL"
	finish_case
}

test_zero_c_no_command_name()
{
	begin_case "S05" "env -i $MINISHELL -c ':'" "specials" \
		"keeps argv[0] as \$0" \
		env -i "$MINISHELL" -c ":"

	expect_special_string "0" "$MINISHELL"
	expect_param "0" "$MINISHELL"
	finish_case
}

test_zero_c_command_name()
{
	begin_case "S06" "env -i $MINISHELL -c ':' cmd_name" "specials" \
		"uses command_name as \$0" \
		env -i "$MINISHELL" -c ":" cmd_name

	expect_special_string "0" "cmd_name"
	expect_param "0" "cmd_name"
	finish_case
}

test_zero_c_command_name_dash()
{
	begin_case "S07" "env -i $MINISHELL -c ':' -cmd" "specials" \
		"allows dash command_name" \
		env -i "$MINISHELL" -c ":" -cmd

	expect_special_string "0" "-cmd"
	expect_param "0" "-cmd"
	finish_case
}

test_zero_command_file()
{
	begin_case "S08" "env -i $MINISHELL $SCRIPT_FILE" "specials" \
		"uses command_file as \$0" \
		env -i "$MINISHELL" "$SCRIPT_FILE"

	expect_special_string "0" "$SCRIPT_FILE"
	expect_param "0" "$SCRIPT_FILE"
	finish_case
}

test_zero_plus_command_file()
{
	begin_case "S09" "env -i $MINISHELL -- $PLUS_SCRIPT_FILE" "specials" \
		"protects + command_file" \
		env -i "$MINISHELL" -- "$PLUS_SCRIPT_FILE"

	expect_special_string "0" "$PLUS_SCRIPT_FILE"
	expect_param "0" "$PLUS_SCRIPT_FILE"
	finish_case
}

test_no_positionals()
{
	begin_case "P01" "env -i $MINISHELL -c ':'" "positionals" \
		"starts with zero args" \
		env -i "$MINISHELL" -c ":"

	expect_positionals_count "0"
	finish_case
}

test_c_positionals()
{
	begin_case "P02" "env -i $MINISHELL -c ':' cmd a b" "positionals" \
		"loads args after command_name" \
		env -i "$MINISHELL" -c ":" cmd a b

	expect_positionals_count "2"
	expect_positional "1" "a"
	expect_positional "2" "b"
	finish_case
}

test_c_positionals_beginning_with_sign()
{
	begin_case "P03" "env -i $MINISHELL -c ':' cmd -e +x" "positionals" \
		"keeps signed operands" \
		env -i "$MINISHELL" -c ":" cmd -e +x

	expect_positionals_count "2"
	expect_positional "1" "-e"
	expect_positional "2" "+x"
	finish_case
}

test_s_positionals()
{
	begin_case "P04" "env -i $MINISHELL -s a b" "positionals" \
		"loads -s arguments" \
		env -i "$MINISHELL" -s a b

	expect_positionals_count "2"
	expect_positional "1" "a"
	expect_positional "2" "b"
	finish_case
}

test_command_file_positionals()
{
	begin_case "P05" "env -i $MINISHELL $SCRIPT_FILE a b" "positionals" \
		"loads command_file args" \
		env -i "$MINISHELL" "$SCRIPT_FILE" a b

	expect_positionals_count "2"
	expect_positional "1" "a"
	expect_positional "2" "b"
	finish_case
}

test_hyphen_operand_ignored()
{
	begin_case "P06" "env -i $MINISHELL - a b" "positionals" \
		"ignores single hyphen operand" \
		env -i "$MINISHELL" - a b

	expect_special_string "0" "$MINISHELL"
	expect_param "0" "$MINISHELL"
	expect_positionals_count "2"
	expect_positional "1" "a"
	expect_positional "2" "b"
	finish_case
}

run_variable_tests()
{
	section "VARIABLES / PARAMS getter"
	test_imported_var
	test_empty_var
	test_complex_value_var
	test_invalid_env_names
	test_ifs_reset
	test_ppid
	test_prompt_var "V07" "PS1" '$ '
	test_prompt_var "V08" "PS2" '> '
	test_prompt_var "V09" "PS4" '+ '
}

run_option_tests()
{
	section "OPTIONS / PARAMS '-' getter"
	test_default_options_stdin
	test_c_option
	test_s_option

	test_short_option "O04" "a"
	test_short_option "O05" "b"
	test_short_option "O06" "C"
	test_short_option "O07" "e"
	test_short_option "O08" "f"
	test_short_option "O09" "h"
	test_short_option "O10" "i"
	test_short_option "O11" "m"
	test_short_option "O12" "n"
	test_short_option "O13" "u"
	test_short_option "O14" "v"
	test_short_option "O15" "x"

	test_long_option "O16" "ignoreeof" "ignoreeof"
	test_long_option "O17" "nolog" "nolog"
	test_long_option "O18" "pipefail" "pipefail"
	test_long_option "O19" "vi" "vi"
	test_long_alias_option "O20" "noclobber" "C" "C"
	test_long_alias_option "O21" "notify" "b" "b"
	test_long_alias_option "O22" "nounset" "u" "u"

	test_plus_option_turns_off
	test_option_order_last_wins
	test_plus_long_option_turns_off
}

run_special_tests()
{
	section "SPECIALS / PARAMS getter"
	test_special_status
	test_special_bang_unset
	test_special_pid
	test_zero_no_operand
	test_zero_c_no_command_name
	test_zero_c_command_name
	test_zero_c_command_name_dash
	test_zero_command_file
	test_zero_plus_command_file
}

run_positional_tests()
{
	section "POSITIONALS / PARAMS getter"
	test_no_positionals
	test_c_positionals
	test_c_positionals_beginning_with_sign
	test_s_positionals
	test_command_file_positionals
	test_hyphen_operand_ignored
}

summary()
{
	echo ""
	if [ "$FAILED" -eq 0 ]; then
		echo -e "${GREEN}✔ $TOTAL tests passed${NC}"
		return 0
	fi

	echo -e "${RED}✖ $FAILED / $TOTAL tests failed${NC}"
	return 1
}

main()
{
	check_program_exists "$MINISHELL"
	setup_files

	echo -e "${GREY}minishell init dump tests${NC}"
	echo -e "${GREY}binary: $MINISHELL${NC}"

	run_variable_tests
	run_option_tests
	run_special_tests
	run_positional_tests

	summary
}

main
