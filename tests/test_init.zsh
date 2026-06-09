#!/usr/bin/env zsh

###############################################################################
# minishell initialization dump tests
# Version: v22-single-allexport-variable-init-test
#
# Intended location after download/rename:
#   tests/test_init.zsh
#
# Usage from minishell/ project root:
#   tests/test_init.zsh [path/to/minishell]
#
# Default tested binary:
#   ./minishell
#
# Logs:
#   tests/logs/test_init.N/
#
# Fixtures:
#   tests/fixtures/test_init/
#
# Current scope of this version:
#   VARIABLES, OPTIONS, SPECIALS, and POSITIONALS initialization.
#
# Each VARIABLES test checks both:
#   - DUMP VARIABLES: presence/absence + value + exported/readonly attributes
#   - DUMP PARAMS:    presence/absence + value through params getter
#
# Variable values are matched using the current dump format:
#   VAR name='NAME' value='VALUE' exported=true readonly=false
#   VAR name='NAME' value=NULL exported=true readonly=false
#   PARAMS 'NAME'='VALUE'
#   PARAMS 'NAME'=NULL
#
# A quoted 'NULL' is treated as the string "NULL"; unquoted NULL is treated as
# an abstract NULL exposed by the dump.
#
# IFS is matched with a dedicated multi-line literal because its value is
# <space><tab><newline> and the dump does not escape values.
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

BLUE=$'\033[0;34m'
GREEN=$'\033[0;32m'
RED=$'\033[0;31m'
YELLOW=$'\033[0;33m'
GRAY=$'\033[0;90m'
NC=$'\033[0m'
GREY=$'\033[0;90m'

COL1_WIDTH=66
RESULT_WIDTH=154

LOG_ROOT="${SCRIPT_DIR}/logs"
LOG_DIR=""

FIXTURE_DIR="${SCRIPT_DIR}/fixtures/test_init"
PWD_LINK="${FIXTURE_DIR}/pwd_link"
PWD_OTHER_DIR="${FIXTURE_DIR}/pwd_other_dir"
SPECIAL_SCRIPT="${FIXTURE_DIR}/special_script.sh"
PLUS_SPECIAL_SCRIPT="${FIXTURE_DIR}/+special_script.sh"
DASH_SCRIPT="${FIXTURE_DIR}/-s"

TOTAL=0
FAILED=0

CURRENT_ID=""
CURRENT_INVOCATION=""
CURRENT_MSG=""
CURRENT_LOG=""
CURRENT_STDOUT_LOG=""
CURRENT_STDERR_LOG=""
OUTPUT=""
STDOUT_OUTPUT=""
STDERR_OUTPUT=""
RET=0
CASE_FAILED=0
CASE_DETAILS=()

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
	local n=1

	mkdir -p "$LOG_ROOT" || {
		echo -e "${RED}✖ Error: cannot create log root: $LOG_ROOT${NC}"
		exit 1
	}

	while [ -e "${LOG_ROOT}/test_init.${n}" ]; do
		n=$((n + 1))
	done

	LOG_DIR="${LOG_ROOT}/test_init.${n}"
	mkdir -p "$LOG_DIR" || {
		echo -e "${RED}✖ Error: cannot create log dir: $LOG_DIR${NC}"
		exit 1
	}

	rm -rf "$FIXTURE_DIR"
	mkdir -p "$FIXTURE_DIR" "$PWD_OTHER_DIR" || {
		echo -e "${RED}✖ Error: cannot create fixture dirs in: $FIXTURE_DIR${NC}"
		exit 1
	}
	ln -sfn "$PROJECT_ROOT" "$PWD_LINK" || {
		echo -e "${RED}✖ Error: cannot create symlink fixture: $PWD_LINK${NC}"
		exit 1
	}
	if [ "$(cd "$PWD_LINK" 2>/dev/null && pwd -P)" != "$PROJECT_ROOT" ]; then
		echo -e "${RED}✖ Error: PWD symlink fixture does not resolve to project root${NC}"
		echo -e "${RED}  link:   $PWD_LINK${NC}"
		echo -e "${RED}  target: $PROJECT_ROOT${NC}"
		exit 1
	fi

	printf '# special fixture\n' > "$SPECIAL_SCRIPT" || {
		echo -e "${RED}✖ Error: cannot create fixture file: $SPECIAL_SCRIPT${NC}"
		exit 1
	}
	printf '# plus-name special fixture\n' > "$PLUS_SPECIAL_SCRIPT" || {
		echo -e "${RED}✖ Error: cannot create fixture file: $PLUS_SPECIAL_SCRIPT${NC}"
		exit 1
	}
	printf '# dash-name fixture\n' > "$DASH_SCRIPT" || {
		echo -e "${RED}✖ Error: cannot create fixture file: $DASH_SCRIPT${NC}"
		exit 1
	}
}

section()
{
	local title="$1"

	echo ""
	echo -e "${GREY}--- $title ---${NC}\n"
}

fit_col()
{
	local text="$1"
	local width="$2"

	if [ "${#text}" -gt "$width" ]; then
		printf "%s" "${text[1,$((width - 3))]}..."
	else
		printf "%-${width}s" "$text"
	fi
}

print_result()
{
	local result_status="$1"
	local color="$2"
	local symbol="$3"

	local col1="$(fit_col "$CURRENT_INVOCATION" "$COL1_WIDTH")"
	local visible_prefix="Test ${CURRENT_ID}: ${col1} ⇢ ${CURRENT_MSG} "
	local dot_count=$((RESULT_WIDTH - ${#visible_prefix}))
	local dots

	if [ "$dot_count" -lt 3 ]; then
		dot_count=3
	fi
	dots=$(printf "%${dot_count}s" "" | tr ' ' '.')

	printf "Test %s: ${BLUE}%s${NC} ⇢ %s ${GRAY}%s${NC} ${color}%s${NC}\n" \
		"$CURRENT_ID" "$col1" "$CURRENT_MSG" "$dots" "$symbol"

	if [ "$result_status" != "ok" ]; then
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
	CURRENT_MSG="$3"
	shift 3

	CASE_FAILED=0
	CASE_DETAILS=()
	CURRENT_LOG="${LOG_DIR}/test_${CURRENT_ID// /_}.log"
	CURRENT_STDOUT_LOG=""
	CURRENT_STDERR_LOG=""
	STDOUT_OUTPUT=""
	STDERR_OUTPUT=""

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

dump_value_fragment()
{
	local value="$1"

	if [ "$value" = "__DUMP_NULL__" ]; then
		printf "NULL"
	else
		printf "'%s'" "$value"
	fi
}

expect_var()
{
	local name="$1"
	local value="$2"
	local exported="$3"
	local readonly="$4"
	local value_fragment

	value_fragment="$(dump_value_fragment "$value")"

	expect_contains \
		"VAR name='${name}' value=${value_fragment} exported=${exported} readonly=${readonly}" \
		"VARIABLES ${name}=${value_fragment} exported=${exported} readonly=${readonly}"
}

expect_no_var_dump()
{
	local name="$1"

	expect_not_contains "VAR name='${name}' " "VARIABLES must not contain ${name}"
}

expect_param()
{
	local name="$1"
	local value="$2"
	local value_fragment

	value_fragment="$(dump_value_fragment "$value")"

	expect_contains "PARAMS '${name}'=${value_fragment}" "PARAMS ${name}=${value_fragment}"
}

expect_no_param()
{
	local name="$1"

	expect_not_contains "PARAMS '${name}'=" "PARAMS must not contain ${name}"
}

expect_variable_available()
{
	local name="$1"
	local value="$2"
	local exported="$3"
	local readonly="$4"

	expect_var "$name" "$value" "$exported" "$readonly"
	expect_param "$name" "$value"
}

expect_variable_absent()
{
	local name="$1"

	expect_no_var_dump "$name"
	expect_no_param "$name"
}

###############################################################################
# OPTIONS helpers
###############################################################################

ALL_OPTION_NAMES=(a b C e f h i m n u v x c s ignoreeof nolog pipefail vi)
SHORT_PARAM_FLAGS=(a b C e f h i m n u v x)
typeset -A EXPECTED_OPTIONS

begin_case_expect_success()
{
	local expected_ret="$1"
	shift

	begin_case "$@"
	expect_ret "$expected_ret"
}

begin_case_expect_nonzero_with_stderr()
{
	CURRENT_ID="$1"
	CURRENT_INVOCATION="$2"
	CURRENT_MSG="$3"
	shift 3

	CASE_FAILED=0
	CASE_DETAILS=()
	CURRENT_LOG="${LOG_DIR}/test_${CURRENT_ID// /_}.log"
	CURRENT_STDOUT_LOG="${LOG_DIR}/test_${CURRENT_ID// /_}.stdout.log"
	CURRENT_STDERR_LOG="${LOG_DIR}/test_${CURRENT_ID// /_}.stderr.log"

	"$@" < /dev/null > "$CURRENT_STDOUT_LOG" 2> "$CURRENT_STDERR_LOG"
	RET=$?
	STDOUT_OUTPUT="$(< "$CURRENT_STDOUT_LOG")"
	STDERR_OUTPUT="$(< "$CURRENT_STDERR_LOG")"

	{
		printf '### STDOUT ###\n'
		cat "$CURRENT_STDOUT_LOG"
		printf '\n### STDERR ###\n'
		cat "$CURRENT_STDERR_LOG"
	} > "$CURRENT_LOG"

	OUTPUT="${STDOUT_OUTPUT}
${STDERR_OUTPUT}"

	if [ "$RET" -eq 0 ]; then
		fail_current "return code: got 0, expected > 0"
	fi

	if [ -z "$STDERR_OUTPUT" ]; then
		fail_current "stderr: expected diagnostic message, got empty stderr"
	fi
}

expected_options_reset()
{
	local opt

	EXPECTED_OPTIONS=()
	for opt in "${ALL_OPTION_NAMES[@]}"; do
		EXPECTED_OPTIONS[$opt]="false"
	done

	# POSIX allows -h to be enabled by default, so the default state is accepted
	# as either true or false. Tests that explicitly set or unset -h still assert
	# the exact final value.
	EXPECTED_OPTIONS[h]="__ANY__"

	# With no command_file and no -c, sh assumes -s.
	EXPECTED_OPTIONS[s]="true"
}

expected_options_set()
{
	local assignment
	local opt
	local value

	for assignment in "$@"; do
		opt="${assignment%%=*}"
		value="${assignment#*=}"

		if [[ -z "${EXPECTED_OPTIONS[$opt]+set}" ]]; then
			fail_current "internal tester error: unknown option '$opt'"
			continue
		fi

		EXPECTED_OPTIONS[$opt]="$value"
	done
}

expect_option_dump()
{
	local opt="$1"
	local expected="$2"

	expect_contains "OPTION ${opt}=${expected}" "OPTIONS ${opt}=${expected}"
}

expect_option_dump_any_bool()
{
	local opt="$1"

	if [[ "$OUTPUT" != *"OPTION ${opt}=true"* && "$OUTPUT" != *"OPTION ${opt}=false"* ]]; then
		fail_current "missing: OPTIONS ${opt}=<boolean>"
	fi
}

params_hyphen_flags()
{
	if [[ "$OUTPUT" =~ "PARAMS '-'='([^']*)'" ]]; then
		printf '%s' "$match[1]"
		return 0
	fi

	if [[ "$OUTPUT" == *"PARAMS '-'=NULL"* ]]; then
		fail_current "PARAMS '-' is NULL, expected a string"
		printf ''
		return 1
	fi

	fail_current "missing: PARAMS '-'"
	printf ''
	return 1
}

expect_param_flag_present()
{
	local flag="$1"
	local flags="$(params_hyphen_flags)"

	if [[ "$flags" != *"$flag"* ]]; then
		fail_current "PARAMS '-': missing flag '$flag' in '${flags}'"
	fi
}

expect_param_flag_absent()
{
	local flag="$1"
	local flags="$(params_hyphen_flags)"

	if [[ "$flags" == *"$flag"* ]]; then
		fail_current "PARAMS '-': unexpected flag '$flag' in '${flags}'"
	fi
}

expect_options_match_expected()
{
	local opt
	local expected

	for opt in "${ALL_OPTION_NAMES[@]}"; do
		expected="${EXPECTED_OPTIONS[$opt]}"
		if [ "$expected" = "__ANY__" ]; then
			expect_option_dump_any_bool "$opt"
		else
			expect_option_dump "$opt" "$expected"
		fi
	done

	# POSIX leaves inclusion of c and s in $- unspecified, so the getter test
	# deliberately checks only the other single-letter option flags.
	for opt in "${SHORT_PARAM_FLAGS[@]}"; do
		expected="${EXPECTED_OPTIONS[$opt]}"
		if [ "$expected" = "__ANY__" ]; then
			continue
		elif [ "$expected" = "true" ]; then
			expect_param_flag_present "$opt"
		else
			expect_param_flag_absent "$opt"
		fi
	done
}

expect_options_state()
{
	expected_options_reset
	expected_options_set "$@"
	expect_options_match_expected
}

expect_ifs_default()
{
	local exported="${1:-false}"
	local ifs_default=$' \t\n'
	local var_line="VAR name='IFS' value='${ifs_default}' exported=${exported} readonly=false"
	local param_line="PARAMS 'IFS'='${ifs_default}'"

	expect_contains "$var_line" "VARIABLES IFS=<space><tab><newline> exported=${exported} readonly=false"
	expect_contains "$param_line" "PARAMS IFS=<space><tab><newline>"
}

is_special_or_positional_param_name()
{
	local name="$1"

	# Keep this as explicit string comparisons, not a case pattern: in shell
	# patterns '?' and '*' are metacharacters, and this helper must only match
	# the literal special parameter names.
	if [[ "$name" = "-" || "$name" = "0" || "$name" = "$" || "$name" = "!" || "$name" = "?" || "$name" = "#" || "$name" = "@" || "$name" = "*" ]]; then
		return 0
	fi

	if [[ "$name" =~ '^[0-9]+$' ]]; then
		return 0
	fi

	return 1
}

collect_variable_dump_names()
{
	local line
	local name
	local -a names=()

	while IFS= read -r line; do
		if [[ "$line" =~ "VAR name='([^']+)'" ]]; then
			names+=("$match[1]")
		fi
	done <<< "$OUTPUT"

	for name in "${names[@]}"; do
		printf '%s\n' "$name"
	done
}

collect_variable_param_names()
{
	local line
	local name
	local -a names=()

	while IFS= read -r line; do
		if [[ "$line" =~ "PARAMS '([^']+)'" ]]; then
			name="$match[1]"

			if is_special_or_positional_param_name "$name"; then
				continue
			fi

			if [[ "$name" =~ "^[A-Za-z_][A-Za-z0-9_]*$" ]]; then
				names+=("$name")
			fi
		fi
	done <<< "$OUTPUT"

	for name in "${names[@]}"; do
		printf '%s\n' "$name"
	done
}

expect_exact_variable_name_set()
{
	local expected_label="$1"
	shift
	local -a expected=("$@")
	local -a var_names=()
	local -a param_names=()
	local raw

	raw="$(collect_variable_dump_names)"
	if [ -n "$raw" ]; then
		var_names=("${(@f)raw}")
	fi

	raw="$(collect_variable_param_names)"
	if [ -n "$raw" ]; then
		param_names=("${(@f)raw}")
	fi

	expect_name_set "VARIABLES" "$expected_label" "${(@)var_names}" -- "${(@)expected}"
	expect_name_set "PARAMS" "$expected_label" "${(@)param_names}" -- "${(@)expected}"
}

expect_name_set()
{
	local scope="$1"
	local label="$2"
	shift 2

	local -a got=()
	local -a expected=()
	local phase="got"
	local item

	for item in "$@"; do
		if [ "$item" = "--" ]; then
			phase="expected"
			continue
		fi

		if [ "$phase" = "got" ]; then
			got+=("$item")
		else
			expected+=("$item")
		fi
	done

	local -A expected_map=()
	local -A got_map=()

	for item in "${expected[@]}"; do
		expected_map[$item]=1
	done

	for item in "${got[@]}"; do
		got_map[$item]=1
	done

	for item in "${expected[@]}"; do
		if [[ -z "${got_map[$item]-}" ]]; then
			fail_current "${scope}: missing variable name ${item} (${label})"
		fi
	done

	for item in "${got[@]}"; do
		if [[ -z "${expected_map[$item]-}" ]]; then
			fail_current "${scope}: unexpected variable name ${item} (${label})"
		fi
	done
}



###############################################################################
# SPECIALS helpers
###############################################################################

run_in_dir()
{
	local dir="$1"
	shift

	(
		cd "$dir" || exit 125
		"$@"
	)
}

expect_special_raw()
{
	local key="$1"
	local raw="$2"
	local label="$3"

	expect_contains "SPECIAL ${key}=${raw}" "SPECIALS ${label}"
}

expect_special_string()
{
	local key="$1"
	local value="$2"
	local value_fragment

	value_fragment="$(dump_value_fragment "$value")"
	expect_special_raw "$key" "$value_fragment" "${key}=${value_fragment}"
}

expect_special_number()
{
	local key="$1"
	local value="$2"

	expect_special_raw "$key" "$value" "${key}=${value}"
}

extract_special_pid()
{
	local line
	local pid=""

	while IFS= read -r line; do
		if [[ "$line" == 'SPECIAL $='* ]]; then
			pid="${line#SPECIAL \$=}"
			break
		fi
	done <<< "$OUTPUT"

	printf '%s' "$pid"
}

expect_special_pid_consistent()
{
	local pid

	pid="$(extract_special_pid)"
	if [ -z "$pid" ]; then
		fail_current "missing: SPECIALS $=<pid>"
		return
	fi

	if ! [[ "$pid" =~ '^[0-9][0-9]*$' ]]; then
		fail_current "SPECIALS $: expected decimal pid, got '${pid}'"
		return
	fi

	if [ "$pid" -le 0 ]; then
		fail_current "SPECIALS $: expected pid > 0, got '${pid}'"
		return
	fi

	expect_param "$" "$pid"
}

expect_specials_initial_state()
{
	local expected_source="$1"
	local expected_zero="$2"

	expect_special_string "source" "$expected_source"
	expect_special_string "0" "$expected_zero"
	expect_param "0" "$expected_zero"

	expect_special_pid_consistent

	expect_special_number "!" "-1"
	expect_param "!" "__DUMP_NULL__"

	expect_special_number "?" "0"
	expect_param "?" "0"
}


###############################################################################
# POSITIONALS helpers
###############################################################################

collect_positional_dump_indexes()
{
	local line
	local index
	local -a indexes=()

	while IFS= read -r line; do
		if [[ "$line" =~ "^POSITIONALS\\[0\\] ([0-9]+)=" ]]; then
			indexes+=("$match[1]")
		fi
	done <<< "$OUTPUT"

	for index in "${indexes[@]}"; do
		printf '%s\n' "$index"
	done
}

collect_positional_param_indexes()
{
	local line
	local index
	local -a indexes=()

	while IFS= read -r line; do
		if [[ "$line" =~ "^PARAMS '([1-9][0-9]*)'=" ]]; then
			indexes+=("$match[1]")
		fi
	done <<< "$OUTPUT"

	for index in "${indexes[@]}"; do
		printf '%s\n' "$index"
	done
}

expect_exact_positionals_indexes()
{
	local count="$1"
	local -a expected_dump=()
	local -a expected_params=()
	local -a got_dump=()
	local -a got_params=()
	local raw
	local i

	raw="$(collect_positional_dump_indexes)"
	if [ -n "$raw" ]; then
		got_dump=("${(@f)raw}")
	fi

	raw="$(collect_positional_param_indexes)"
	if [ -n "$raw" ]; then
		got_params=("${(@f)raw}")
	fi

	for ((i = 0; i < count; i++)); do
		expected_dump+=("$i")
	done

	for ((i = 1; i <= count; i++)); do
		expected_params+=("$i")
	done

	expect_name_set "POSITIONALS" "positionals indexes" "${(@)got_dump}" -- "${(@)expected_dump}"
	expect_name_set "PARAMS" "positional getter indexes" "${(@)got_params}" -- "${(@)expected_params}"
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
	local param_index=$((index + 1))
	local value_fragment

	value_fragment="$(dump_value_fragment "$value")"

	expect_contains "POSITIONALS[0] ${index}=${value_fragment}" \
		"POSITIONALS[0] ${index}=${value_fragment}"
	expect_param "$param_index" "$value"
}

expect_positionals()
{
	local count="$1"
	shift

	local index=0
	local value

	expect_positionals_count "$count"

	for value in "$@"; do
		expect_positional "$index" "$value"
		index=$((index + 1))
	done

	if [ "$index" -ne "$count" ]; then
		fail_current "internal tester error: expected $count positional values, got $index"
	fi

	expect_exact_positionals_indexes "$count"
}


###############################################################################
# VARIABLES
###############################################################################

test_variables_empty_envp()
{
	local expected_pwd="$(pwd -P)"
	local expected_ppid="$$"

	begin_case "V01" "env -i ./minishell" \
		"empty envp initializes only mandatory variables" \
		env -i "$MINISHELL"

	expect_ifs_default "false"
	expect_variable_available "PPID" "$expected_ppid" "false" "false"
	expect_variable_available "PWD" "$expected_pwd" "false" "false"
	expect_variable_available "PS1" '$ ' "false" "false"
	expect_variable_available "PS2" '> ' "false" "false"
	expect_variable_available "PS4" '+ ' "false" "false"
	expect_exact_variable_name_set "empty envp" "IFS" "PPID" "PWD" "PS1" "PS2" "PS4"
	finish_case
}

test_ifs_envp_default_value()
{
	begin_case "V02" "env -i IFS=<default> ./minishell" \
		"keeps IFS default value but preserves exported attribute" \
		env -i IFS=$' \t\n' "$MINISHELL"

	expect_ifs_default "true"
	finish_case
}

test_ifs_envp_non_default_value()
{
	begin_case "V03" "env -i IFS=abc ./minishell" \
		"resets IFS value but preserves exported attribute" \
		env -i IFS=abc "$MINISHELL"

	expect_ifs_default "true"
	expect_not_contains "VAR name='IFS' value='abc'" "IFS must not keep envp value"
	expect_not_contains "PARAMS 'IFS'='abc'" "PARAMS IFS must not keep envp value"
	finish_case
}

test_ppid_envp_invalid_value()
{
	local expected_ppid="$$"

	begin_case "V04" "env -i PPID=abc ./minishell" \
		"resets PPID to actual parent pid and preserves exported attribute" \
		env -i PPID=abc "$MINISHELL"

	expect_variable_available "PPID" "$expected_ppid" "true" "false"
	expect_not_contains "VAR name='PPID' value='abc'" "PPID must not keep invalid envp value"
	expect_not_contains "PARAMS 'PPID'='abc'" "PARAMS PPID must not keep invalid envp value"
	finish_case
}

test_pwd_envp_valid_symlink()
{
	begin_case "V05" "env -i PWD=<symlink-to-project-root> ./minishell" \
		"keeps valid logical PWD containing a symlink" \
		env -i "PWD=$PWD_LINK" "$MINISHELL"

	expect_variable_available "PWD" "$PWD_LINK" "true" "false"
	expect_not_contains "VAR name='PWD' value='${PROJECT_ROOT}'" "PWD must keep valid logical symlink path, not physical project root"
	expect_not_contains "PARAMS 'PWD'='${PROJECT_ROOT}'" "PARAMS PWD must keep valid logical symlink path, not physical project root"
	finish_case
}

test_pwd_envp_dot_component()
{
	local expected_pwd="$(pwd -P)"
	local invalid_pwd="${expected_pwd}/./"

	begin_case "V06" "env -i PWD=<cwd>/./ ./minishell" \
		"resets PWD containing dot component" \
		env -i "PWD=$invalid_pwd" "$MINISHELL"

	expect_variable_available "PWD" "$expected_pwd" "true" "false"
	expect_not_contains "VAR name='PWD' value='${invalid_pwd}'" "PWD must not keep dot component"
	expect_not_contains "PARAMS 'PWD'='${invalid_pwd}'" "PARAMS PWD must not keep dot component"
	finish_case
}

test_pwd_envp_dot_dot_component()
{
	local expected_pwd="$(pwd -P)"
	local base="${expected_pwd:t}"
	local invalid_pwd="${expected_pwd}/../${base}"

	begin_case "V07" "env -i PWD=<cwd>/../<cwd-name> ./minishell" \
		"resets PWD containing dot-dot component even when it resolves to cwd" \
		env -i "PWD=$invalid_pwd" "$MINISHELL"

	expect_variable_available "PWD" "$expected_pwd" "true" "false"
	expect_not_contains "VAR name='PWD' value='${invalid_pwd}'" "PWD must not keep dot-dot component"
	expect_not_contains "PARAMS 'PWD'='${invalid_pwd}'" "PARAMS PWD must not keep dot-dot component"
	finish_case
}

test_pwd_envp_not_current_directory()
{
	local expected_pwd="$(pwd -P)"
	local wrong_pwd="${PWD_OTHER_DIR:A}"

	begin_case "V08" "env -i PWD=<other-absolute-dir> ./minishell" \
		"resets PWD that does not name the current directory" \
		env -i "PWD=$wrong_pwd" "$MINISHELL"

	expect_variable_available "PWD" "$expected_pwd" "true" "false"
	expect_not_contains "VAR name='PWD' value='${wrong_pwd}'" "PWD must not keep path that is not cwd"
	expect_not_contains "PARAMS 'PWD'='${wrong_pwd}'" "PARAMS PWD must not keep path that is not cwd"
	finish_case
}

test_prompts_envp_present()
{
	begin_case "V09" "env -i PS1=a PS2=b PS4=c ./minishell" \
		"keeps PS1 PS2 PS4 values and preserves exported attributes" \
		env -i PS1=prompt1 PS2=prompt2 PS4=prompt4 "$MINISHELL"

	expect_variable_available "PS1" "prompt1" "true" "false"
	expect_variable_available "PS2" "prompt2" "true" "false"
	expect_variable_available "PS4" "prompt4" "true" "false"
	finish_case
}

test_valid_env_var_with_value()
{
	begin_case "V10" "env -i TEST_VAR=alpha ./minishell" \
		"imports valid variable with value" \
		env -i TEST_VAR=alpha "$MINISHELL"

	expect_variable_available "TEST_VAR" "alpha" "true" "false"
	finish_case
}

test_valid_env_var_empty_value()
{
	begin_case "V11" "env -i EMPTY_VAR= ./minishell" \
		"imports valid variable with empty value" \
		env -i EMPTY_VAR= "$MINISHELL"

	expect_variable_available "EMPTY_VAR" "" "true" "false"
	finish_case
}

test_invalid_env_names_are_ignored()
{
	begin_case "V12" "env -i GOOD=ok 1BAD=no BAD-NAME=no BAD.NAME=no ./minishell" \
		"ignores invalid environment names" \
		env -i GOOD=ok "1BAD=no" "BAD-NAME=no" "BAD.NAME=no" "$MINISHELL"

	expect_variable_available "GOOD" "ok" "true" "false"
	expect_variable_absent "1BAD"
	expect_variable_absent "BAD-NAME"
	expect_variable_absent "BAD.NAME"
	finish_case
}

test_null_string_is_not_null_value()
{
	begin_case "V13" "env -i NULL_WORD=NULL ./minishell" \
		"keeps string NULL distinct from dump NULL" \
		env -i NULL_WORD=NULL "$MINISHELL"

	expect_variable_available "NULL_WORD" "NULL" "true" "false"
	expect_not_contains "VAR name='NULL_WORD' value=NULL " "string NULL must not be dumped as abstract NULL"
	expect_not_contains "PARAMS 'NULL_WORD'=NULL" "string NULL must not be dumped as abstract NULL"
	finish_case
}

test_valid_env_name_edge_cases()
{
	begin_case "V14" "env -i _UNDER=ok A1_B2=ok ./minishell" \
		"imports valid names with leading underscore and digits" \
		env -i _UNDER=ok A1_B2=ok "$MINISHELL"

	expect_variable_available "_UNDER" "ok" "true" "false"
	expect_variable_available "A1_B2" "ok" "true" "false"
	finish_case
}

test_pwd_envp_relative_path()
{
	local expected_pwd="$(pwd -P)"
	local relative_pwd="."

	begin_case "V15" "env -i PWD=. ./minishell" \
		"resets relative PWD" \
		env -i "PWD=$relative_pwd" "$MINISHELL"

	expect_variable_available "PWD" "$expected_pwd" "true" "false"
	expect_not_contains "VAR name='PWD' value='${relative_pwd}'" "PWD must not keep relative path"
	expect_not_contains "PARAMS 'PWD'='${relative_pwd}'" "PARAMS PWD must not keep relative path"
	finish_case
}

expect_minimal_initialized_variables()
{
	local exported="$1"
	local expected_pwd="$(pwd -P)"
	local expected_ppid="$$"

	expect_ifs_default "$exported"
	expect_variable_available "PPID" "$expected_ppid" "$exported" "false"
	expect_variable_available "PWD" "$expected_pwd" "$exported" "false"
	expect_variable_available "PS1" '$ ' "$exported" "false"
	expect_variable_available "PS2" '> ' "$exported" "false"
	expect_variable_available "PS4" '+ ' "$exported" "false"
	expect_exact_variable_name_set "minimal initialized variables" "IFS" "PPID" "PWD" "PS1" "PS2" "PS4"
}

test_allexport_short_exports_initialized_variables()
{
	begin_case "V16" "env -i ./minishell -a" \
		"allexport exports variables initialized by the shell" \
		env -i "$MINISHELL" -a

	expect_minimal_initialized_variables "true"
	finish_case
}



run_variable_tests()
{
	section "VARIABLES"

	test_variables_empty_envp

	test_ifs_envp_default_value
	test_ifs_envp_non_default_value

	test_ppid_envp_invalid_value

	test_pwd_envp_valid_symlink
	test_pwd_envp_dot_component
	test_pwd_envp_dot_dot_component
	test_pwd_envp_not_current_directory

	test_prompts_envp_present

	test_valid_env_var_with_value
	test_valid_env_var_empty_value

	test_invalid_env_names_are_ignored
	test_null_string_is_not_null_value
	test_valid_env_name_edge_cases
	test_pwd_envp_relative_path

	test_allexport_short_exports_initialized_variables
}

###############################################################################
# OPTIONS
###############################################################################

test_options_default_state()
{
	begin_case "O01" "env -i ./minishell" \
		"initializes default option state" \
		env -i "$MINISHELL"

	expect_options_state
	finish_case
}

test_options_short_group_on()
{
	begin_case "O02" "env -i ./minishell -<all-short>" \
		"enables all short flags" \
		env -i "$MINISHELL" -abCefhimnuvx

	expect_options_state \
		a=true b=true C=true e=true f=true h=true i=true m=true n=true u=true v=true x=true
	finish_case
}

test_options_short_group_plus_disables()
{
	begin_case "O03" "env -i ./minishell -<all-short> +<all-short>" \
		"disables all plus-capable short flags" \
		env -i "$MINISHELL" -abCefhimnuvx +abCefhimnuvx

	expect_options_state \
		h=false
	finish_case
}

test_options_short_order_last_write_wins()
{
	begin_case "O04" "env -i ./minishell -efuh +fuh -x" \
		"uses final state after repeated short options" \
		env -i "$MINISHELL" -efuh +fuh -x

	expect_options_state \
		e=true f=false u=false x=true h=false
	finish_case
}

test_options_o_short_equivalents()
{
	begin_case "O05" "env -i ./minishell -o <short-equivalent>" \
		"maps -o names to short flags" \
		env -i "$MINISHELL" \
			-o allexport \
			-o errexit \
			-o noclobber \
			-o noglob \
			-o noexec \
			-o monitor \
			-o notify \
			-o nounset \
			-o verbose \
			-o xtrace

	expect_options_state \
		a=true e=true C=true f=true n=true m=true b=true u=true v=true x=true
	finish_case
}

test_options_plus_o_short_equivalents()
{
	begin_case "O06" "env -i ./minishell -o <short-equiv> +o <short-equiv>" \
		"disables short-equivalent +o names" \
		env -i "$MINISHELL" \
			-o allexport \
			-o errexit \
			-o noclobber \
			-o noglob \
			-o noexec \
			-o monitor \
			-o notify \
			-o nounset \
			-o verbose \
			-o xtrace \
			+o allexport \
			+o errexit \
			+o noclobber \
			+o noglob \
			+o noexec \
			+o monitor \
			+o notify \
			+o nounset \
			+o verbose \
			+o xtrace

	expect_options_state \
		h=false
	finish_case
}

test_options_o_long_only()
{
	begin_case "O07" "env -i ./minishell -o <long-only>" \
		"enables long-only -o options" \
		env -i "$MINISHELL" \
			-o ignoreeof \
			-o nolog \
			-o pipefail \
			-o vi

	expect_options_state \
		ignoreeof=true nolog=true pipefail=true vi=true
	finish_case
}

test_options_plus_o_long_only()
{
	begin_case "O08" "env -i ./minishell -o <long-only> +o <long-only>" \
		"disables long-only +o options" \
		env -i "$MINISHELL" \
			-o ignoreeof \
			-o nolog \
			-o pipefail \
			-o vi \
			+o ignoreeof \
			+o nolog \
			+o pipefail \
			+o vi

	expect_options_state
	finish_case
}

test_options_mixed_short_and_long_final_state()
{
	begin_case "O09" "env -i ./minishell -C +C -o noclobber -u +u" \
		"uses final state across short and -o forms" \
		env -i "$MINISHELL" \
			-C \
			+C \
			-o noclobber \
			-u \
			+u

	expect_options_state \
		C=true
	finish_case
}

test_options_interactive_enables_i_and_monitor()
{
	begin_case "O10" "env -i ./minishell -i" \
		"enables interactive mode and default monitor mode" \
		env -i "$MINISHELL" -i

	expect_options_state \
		i=true m=true
	finish_case
}

test_options_interactive_can_be_disabled()
{
	begin_case "O11" "env -i ./minishell -i +i +m" \
		"disables interactive and monitor modes" \
		env -i "$MINISHELL" -i +i +m

	expect_options_state
	finish_case
}

test_options_interactive_monitor_can_be_disabled()
{
	begin_case "O12" "env -i ./minishell -i +m" \
		"allows explicit monitor disable after -i" \
		env -i "$MINISHELL" -i +m

	expect_options_state \
		i=true
	finish_case
}

test_options_explicit_stdin_mode()
{
	begin_case "O13" "env -i ./minishell -s" \
		"recognizes explicit standard-input mode" \
		env -i "$MINISHELL" -s

	expect_options_state \
		s=true
	finish_case
}

test_options_command_string_mode()
{
	begin_case "O14" "env -i ./minishell -c ':'" \
		"recognizes command-string mode" \
		env -i "$MINISHELL" -c ':'

	expect_options_state \
		c=true s=false
	finish_case
}

test_options_command_string_with_regular_options()
{
	begin_case "O15" "env -i ./minishell -eu -c ':'" \
		"combines regular options with -c" \
		env -i "$MINISHELL" -eu -c ':'

	expect_options_state \
		e=true u=true c=true s=false
	finish_case
}

test_options_invalid_minus_short_single()
{
	begin_case_expect_nonzero_with_stderr "O16" "env -i ./minishell -z" \
		"rejects invalid '-' short option" \
		env -i "$MINISHELL" -z

	finish_case
}

test_options_invalid_plus_short_single()
{
	begin_case_expect_nonzero_with_stderr "O17" "env -i ./minishell +z" \
		"rejects invalid '+' short option" \
		env -i "$MINISHELL" +z

	finish_case
}

test_options_invalid_minus_short_group()
{
	begin_case_expect_nonzero_with_stderr "O18" "env -i ./minishell -az" \
		"rejects invalid '-' option in group" \
		env -i "$MINISHELL" -az

	finish_case
}

test_options_invalid_plus_short_group()
{
	begin_case_expect_nonzero_with_stderr "O19" "env -i ./minishell -a +az" \
		"rejects invalid '+' option in group" \
		env -i "$MINISHELL" -a +az

	finish_case
}

test_options_invalid_mixed_after_valid_short()
{
	begin_case_expect_nonzero_with_stderr "O20" "env -i ./minishell -e -z" \
		"rejects invalid short after valid short" \
		env -i "$MINISHELL" -e -z

	finish_case
}

test_options_invalid_mixed_before_valid_short()
{
	begin_case_expect_nonzero_with_stderr "O21" "env -i ./minishell -z -e" \
		"rejects invalid short before valid short" \
		env -i "$MINISHELL" -z -e

	finish_case
}

test_options_invalid_minus_o_single()
{
	begin_case_expect_nonzero_with_stderr "O22" "env -i ./minishell -o not_an_option" \
		"rejects invalid -o option name" \
		env -i "$MINISHELL" -o not_an_option

	finish_case
}

test_options_invalid_plus_o_single()
{
	begin_case_expect_nonzero_with_stderr "O23" "env -i ./minishell +o not_an_option" \
		"rejects invalid +o option name" \
		env -i "$MINISHELL" +o not_an_option

	finish_case
}

test_options_invalid_minus_o_mixed()
{
	begin_case_expect_nonzero_with_stderr "O24" "env -i ./minishell -o errexit -o not_an_option" \
		"rejects invalid -o after valid -o" \
		env -i "$MINISHELL" -o errexit -o not_an_option

	finish_case
}

test_options_invalid_plus_o_mixed()
{
	begin_case_expect_nonzero_with_stderr "O25" "env -i ./minishell -o errexit +o not_an_option" \
		"rejects invalid +o after valid -o" \
		env -i "$MINISHELL" -o errexit +o not_an_option

	finish_case
}

test_options_invalid_mixed_short_and_o()
{
	begin_case_expect_nonzero_with_stderr "O26" "env -i ./minishell -e -o not_an_option +z" \
		"rejects invalid options in mixed forms" \
		env -i "$MINISHELL" -e -o not_an_option +z

	finish_case
}

test_options_missing_c_command_string()
{
	begin_case_expect_nonzero_with_stderr "O27" "env -i ./minishell -c" \
		"rejects -c without command_string" \
		env -i "$MINISHELL" -c

	finish_case
}

run_option_tests()
{
	section "OPTIONS"

	test_options_default_state
	test_options_short_group_on
	test_options_short_group_plus_disables
	test_options_short_order_last_write_wins

	test_options_o_short_equivalents
	test_options_plus_o_short_equivalents
	test_options_o_long_only
	test_options_plus_o_long_only
	test_options_mixed_short_and_long_final_state

	test_options_interactive_enables_i_and_monitor
	test_options_interactive_can_be_disabled
	test_options_interactive_monitor_can_be_disabled

	test_options_explicit_stdin_mode
	test_options_command_string_mode
	test_options_command_string_with_regular_options

	test_options_invalid_minus_short_single
	test_options_invalid_plus_short_single
	test_options_invalid_minus_short_group
	test_options_invalid_plus_short_group
	test_options_invalid_mixed_after_valid_short
	test_options_invalid_mixed_before_valid_short
	test_options_invalid_minus_o_single
	test_options_invalid_plus_o_single
	test_options_invalid_minus_o_mixed
	test_options_invalid_plus_o_mixed
	test_options_invalid_mixed_short_and_o
	test_options_missing_c_command_string
}


###############################################################################
# SPECIALS
###############################################################################

test_specials_default_stdin()
{
	begin_case "S01" "env -i ./minishell" \
		"stdin source, zero from argv0" \
		env -i "$MINISHELL"

	expect_specials_initial_state "__DUMP_NULL__" "$MINISHELL"
	finish_case
}

test_specials_default_stdin_abs_argv0()
{
	begin_case "S02" "env -i <abs-minishell>" \
		"zero uses exact argv0 when no command_file" \
		env -i "$MINISHELL_ABS"

	expect_specials_initial_state "__DUMP_NULL__" "$MINISHELL_ABS"
	finish_case
}

test_specials_double_hyphen_no_operand()
{
	begin_case "S03" "env -i ./minishell --" \
		"-- with no operand still reads stdin" \
		env -i "$MINISHELL" --

	expect_specials_initial_state "__DUMP_NULL__" "$MINISHELL"
	finish_case
}

test_specials_explicit_stdin()
{
	begin_case "S04" "env -i ./minishell -s" \
		"explicit -s keeps stdin source" \
		env -i "$MINISHELL" -s

	expect_specials_initial_state "__DUMP_NULL__" "$MINISHELL"
	finish_case
}

test_specials_stdin_with_arguments()
{
	begin_case "S05" "env -i ./minishell -s arg1" \
		"-s operands do not become command_file" \
		env -i "$MINISHELL" -s arg1

	expect_specials_initial_state "__DUMP_NULL__" "$MINISHELL"
	finish_case
}

test_specials_single_hyphen_operand()
{
	begin_case "S06" "env -i ./minishell -" \
		"single hyphen operand is ignored" \
		env -i "$MINISHELL" -

	expect_specials_initial_state "__DUMP_NULL__" "$MINISHELL"
	finish_case
}

test_specials_single_hyphen_then_argument()
{
	begin_case "S07" "env -i ./minishell - special_script.sh" \
		"single hyphen is ignored before command_file" \
		env -i "$MINISHELL" - "$SPECIAL_SCRIPT"

	expect_specials_initial_state "$SPECIAL_SCRIPT" "$SPECIAL_SCRIPT"
	finish_case
}

test_specials_command_string_without_name()
{
	begin_case "S08" "env -i ./minishell -c ':'" \
		"-c source, zero from argv0 without command_name" \
		env -i "$MINISHELL" -c ':'

	expect_specials_initial_state ":" "$MINISHELL"
	finish_case
}

test_specials_command_string_without_name_abs_argv0()
{
	begin_case "S09" "env -i <abs-minishell> -c ':'" \
		"-c without command_name keeps exact argv0" \
		env -i "$MINISHELL_ABS" -c ':'

	expect_specials_initial_state ":" "$MINISHELL_ABS"
	finish_case
}

test_specials_command_string_with_spaces()
{
	begin_case "S10" "env -i ./minishell -c <string> cmd_name" \
		"source keeps full command_string operand" \
		env -i "$MINISHELL" -c 'echo hello ; :' cmd_name

	expect_specials_initial_state "echo hello ; :" "cmd_name"
	finish_case
}

test_specials_command_string_empty_name()
{
	begin_case "S11" "env -i ./minishell -c ':' ''" \
		"empty command_name sets zero to empty string" \
		env -i "$MINISHELL" -c ':' ""

	expect_specials_initial_state ":" ""
	finish_case
}

test_specials_empty_command_string()
{
	begin_case "S12" "env -i ./minishell -c '' cmd_name" \
		"empty command_string is a valid source" \
		env -i "$MINISHELL" -c "" cmd_name

	expect_specials_initial_state "" "cmd_name"
	finish_case
}

test_specials_command_string_with_extra_arguments()
{
	begin_case "S13" "env -i ./minishell -c ':' cmd arg" \
		"-c extra operands do not affect specials" \
		env -i "$MINISHELL" -c ':' cmd_name arg1

	expect_specials_initial_state ":" "cmd_name"
	finish_case
}

test_specials_command_file_with_slash()
{
	begin_case "S14" "env -i ./minishell special_script.sh" \
		"source and zero use command_file path" \
		env -i "$MINISHELL" "$SPECIAL_SCRIPT"

	expect_specials_initial_state "$SPECIAL_SCRIPT" "$SPECIAL_SCRIPT"
	finish_case
}

test_specials_command_file_without_slash()
{
	begin_case "S15" "env -i ./minishell special_script.sh" \
		"source and zero use command_file operand" \
		run_in_dir "$FIXTURE_DIR" env -i "$MINISHELL_ABS" "special_script.sh"

	expect_specials_initial_state "special_script.sh" "special_script.sh"
	finish_case
}

test_specials_command_file_with_arguments()
{
	begin_case "S16" "env -i ./minishell script arg" \
		"command_file arguments do not affect specials" \
		env -i "$MINISHELL" "$SPECIAL_SCRIPT" arg1

	expect_specials_initial_state "$SPECIAL_SCRIPT" "$SPECIAL_SCRIPT"
	finish_case
}

test_specials_command_file_after_double_hyphen()
{
	begin_case "S17" "env -i ./minishell -- special_script.sh" \
		"first operand after -- is command_file" \
		env -i "$MINISHELL" -- "$SPECIAL_SCRIPT"

	expect_specials_initial_state "$SPECIAL_SCRIPT" "$SPECIAL_SCRIPT"
	finish_case
}

test_specials_plus_named_command_file_after_double_hyphen()
{
	begin_case "S18" "env -i ./minishell -- +special_script.sh" \
		"-- protects command_file beginning with plus" \
		run_in_dir "$FIXTURE_DIR" env -i "$MINISHELL_ABS" -- "+special_script.sh"

	expect_specials_initial_state "+special_script.sh" "+special_script.sh"
	finish_case
}

run_special_tests()
{
	section "SPECIALS"

	test_specials_default_stdin
	test_specials_default_stdin_abs_argv0
	test_specials_double_hyphen_no_operand

	test_specials_explicit_stdin
	test_specials_stdin_with_arguments
	test_specials_single_hyphen_operand
	test_specials_single_hyphen_then_argument

	test_specials_command_string_without_name
	test_specials_command_string_without_name_abs_argv0
	test_specials_command_string_with_spaces
	test_specials_command_string_empty_name
	test_specials_empty_command_string
	test_specials_command_string_with_extra_arguments

	test_specials_command_file_with_slash
	test_specials_command_file_without_slash
	test_specials_command_file_with_arguments
	test_specials_command_file_after_double_hyphen
	test_specials_plus_named_command_file_after_double_hyphen
}


###############################################################################
# POSITIONALS
###############################################################################

test_positionals_default_stdin()
{
	begin_case "P01" "env -i ./minishell" \
		"no positional parameters by default" \
		env -i "$MINISHELL"

	expect_positionals 0
	finish_case
}

test_positionals_explicit_stdin_no_arguments()
{
	begin_case "P02" "env -i ./minishell -s" \
		"-s without arguments has no positional parameters" \
		env -i "$MINISHELL" -s

	expect_positionals 0
	finish_case
}

test_positionals_explicit_stdin_arguments()
{
	begin_case "P03" "env -i ./minishell -s alpha beta" \
		"-s arguments become positional parameters" \
		env -i "$MINISHELL" -s "alpha" "beta"

	expect_positionals 2 "alpha" "beta"
	finish_case
}

test_positionals_explicit_stdin_delimiter_and_dash_values()
{
	begin_case "P04" "env -i ./minishell -s -- -x +y --" \
		"-- lets -/+ values become positional parameters" \
		env -i "$MINISHELL" -s -- "-x" "+y" "--"

	expect_positionals 3 "-x" "+y" "--"
	finish_case
}

test_positionals_explicit_stdin_empty_null_and_spaces()
{
	begin_case "P05" "env -i ./minishell -s '' NULL 'arg with spaces'" \
		"preserves empty, NULL string, and spaces" \
		env -i "$MINISHELL" -s "" "NULL" "arg with spaces"

	expect_positionals 3 "" "NULL" "arg with spaces"
	finish_case
}

test_positionals_command_string_without_command_name()
{
	begin_case "P06" "env -i ./minishell -c ':'" \
		"-c without command_name has no positional parameters" \
		env -i "$MINISHELL" -c ":"

	expect_positionals 0
	finish_case
}

test_positionals_command_string_command_name_only()
{
	begin_case "P07" "env -i ./minishell -c ':' cmd" \
		"command_name is not a positional parameter" \
		env -i "$MINISHELL" -c ":" "cmd"

	expect_positionals 0
	finish_case
}

test_positionals_command_string_arguments()
{
	begin_case "P08" "env -i ./minishell -c ':' cmd a b" \
		"arguments after command_name become positional" \
		env -i "$MINISHELL" -c ":" "cmd" "a" "b"

	expect_positionals 2 "a" "b"
	finish_case
}

test_positionals_command_string_empty_command_name()
{
	begin_case "P09" "env -i ./minishell -c ':' '' a" \
		"empty command_name is not positional" \
		env -i "$MINISHELL" -c ":" "" "a"

	expect_positionals 1 "a"
	finish_case
}

test_positionals_command_string_dash_like_arguments()
{
	begin_case "P10" "env -i ./minishell -c ':' cmd -x +y --" \
		"post-command_name -/+ values are positional" \
		env -i "$MINISHELL" -c ":" "cmd" "-x" "+y" "--"

	expect_positionals 3 "-x" "+y" "--"
	finish_case
}

test_positionals_command_string_empty_values()
{
	begin_case "P11" "env -i ./minishell -c '' cmd '' NULL 'arg with spaces'" \
		"-c preserves empty, NULL string, and spaces" \
		env -i "$MINISHELL" -c "" "cmd" "" "NULL" "arg with spaces"

	expect_positionals 3 "" "NULL" "arg with spaces"
	finish_case
}

test_positionals_command_file_without_arguments()
{
	begin_case "P12" "env -i ./minishell special_script.sh" \
		"command_file itself is not positional" \
		env -i "$MINISHELL" "$SPECIAL_SCRIPT"

	expect_positionals 0
	finish_case
}

test_positionals_command_file_arguments()
{
	begin_case "P13" "env -i ./minishell special_script.sh a b" \
		"arguments after command_file become positional" \
		env -i "$MINISHELL" "$SPECIAL_SCRIPT" "a" "b"

	expect_positionals 2 "a" "b"
	finish_case
}

test_positionals_command_file_dash_like_arguments()
{
	begin_case "P14" "env -i ./minishell special_script.sh -x +y --" \
		"post-command_file -/+ values are positional" \
		env -i "$MINISHELL" "$SPECIAL_SCRIPT" "-x" "+y" "--"

	expect_positionals 3 "-x" "+y" "--"
	finish_case
}

test_positionals_command_file_without_slash_arguments()
{
	begin_case "P15" "env -i ./minishell special_script.sh a b" \
		"no-slash command_file still uses following args" \
		run_in_dir "$FIXTURE_DIR" env -i "$MINISHELL_ABS" "special_script.sh" "a" "b"

	expect_positionals 2 "a" "b"
	finish_case
}

test_positionals_single_hyphen_before_command_file()
{
	begin_case "P16" "env -i ./minishell - special_script.sh a" \
		"single hyphen is ignored before command_file" \
		env -i "$MINISHELL" - "$SPECIAL_SCRIPT" "a"

	expect_positionals 1 "a"
	finish_case
}

test_positionals_dash_named_command_file_after_double_hyphen()
{
	begin_case "P17" "env -i ./minishell -- -s a" \
		"-- protects command_file beginning with dash" \
		run_in_dir "$FIXTURE_DIR" env -i "$MINISHELL_ABS" -- "-s" "a"

	expect_positionals 1 "a"
	finish_case
}


test_positionals_explicit_stdin_single_hyphen_ignored()
{
	begin_case "P19" "env -i ./minishell -s - alpha" \
		"-s ignores first '-' operand" \
		env -i "$MINISHELL" -s - "alpha"

	expect_positionals 1 "alpha"
	finish_case
}

test_positionals_explicit_stdin_options_after_s()
{
	begin_case "P20" "env -i ./minishell -s -e alpha" \
		"options after -s are not positional" \
		env -i "$MINISHELL" -s -e "alpha"

	expect_positionals 1 "alpha"
	finish_case
}

test_positionals_command_string_options_after_c()
{
	begin_case "P21" "env -i ./minishell -c -e ':' cmd a" \
		"options after -c precede command_string" \
		env -i "$MINISHELL" -c -e ":" "cmd" "a"

	expect_positionals 1 "a"
	finish_case
}

test_positionals_command_string_double_hyphen_after_c()
{
	begin_case "P22" "env -i ./minishell -c -- ':' cmd a" \
		"-- after -c precedes command_string" \
		env -i "$MINISHELL" -c -- ":" "cmd" "a"

	expect_positionals 1 "a"
	finish_case
}

test_positionals_command_file_options_before()
{
	begin_case "P23" "env -i ./minishell -e special_script.sh a" \
		"options before command_file are not positional" \
		env -i "$MINISHELL" -e "$SPECIAL_SCRIPT" "a"

	expect_positionals 1 "a"
	finish_case
}

test_positionals_command_file_empty_null_and_spaces()
{
	begin_case "P24" "env -i ./minishell special_script.sh '' NULL 'arg with spaces'" \
		"command_file preserves empty, NULL string, spaces" \
		env -i "$MINISHELL" "$SPECIAL_SCRIPT" "" "NULL" "arg with spaces"

	expect_positionals 3 "" "NULL" "arg with spaces"
	finish_case
}

test_positionals_plus_named_command_file_after_double_hyphen()
{
	begin_case "P25" "env -i ./minishell -- +special_script.sh a" \
		"-- protects command_file beginning with plus" \
		run_in_dir "$FIXTURE_DIR" env -i "$MINISHELL_ABS" -- "+special_script.sh" "a"

	expect_positionals 1 "a"
	finish_case
}

test_positionals_ten_arguments()
{
	begin_case "P18" "env -i ./minishell -s p1 ... p10" \
		"supports two-digit positional parameter indexes" \
		env -i "$MINISHELL" -s \
			"p1" "p2" "p3" "p4" "p5" \
			"p6" "p7" "p8" "p9" "p10"

	expect_positionals 10 \
		"p1" "p2" "p3" "p4" "p5" \
		"p6" "p7" "p8" "p9" "p10"
	finish_case
}

run_positional_tests()
{
	section "POSITIONALS"

	test_positionals_default_stdin
	test_positionals_explicit_stdin_no_arguments
	test_positionals_explicit_stdin_arguments
	test_positionals_explicit_stdin_delimiter_and_dash_values
	test_positionals_explicit_stdin_empty_null_and_spaces

	test_positionals_command_string_without_command_name
	test_positionals_command_string_command_name_only
	test_positionals_command_string_arguments
	test_positionals_command_string_empty_command_name
	test_positionals_command_string_dash_like_arguments
	test_positionals_command_string_empty_values

	test_positionals_command_file_without_arguments
	test_positionals_command_file_arguments
	test_positionals_command_file_dash_like_arguments
	test_positionals_command_file_without_slash_arguments
	test_positionals_single_hyphen_before_command_file
	test_positionals_dash_named_command_file_after_double_hyphen
	test_positionals_ten_arguments

	test_positionals_explicit_stdin_single_hyphen_ignored
	test_positionals_explicit_stdin_options_after_s
	test_positionals_command_string_options_after_c
	test_positionals_command_string_double_hyphen_after_c
	test_positionals_command_file_options_before
	test_positionals_command_file_empty_null_and_spaces
	test_positionals_plus_named_command_file_after_double_hyphen
}


summary()
{
	echo ""
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
	setup_files

	echo -e "${GREY}minishell init dump tests${NC}"
	echo -e "${GREY}binary: $MINISHELL${NC}"
	echo -e "${GREY}logs:   $LOG_DIR${NC}"
	echo -e "${GREY}fixtures: tests/fixtures/test_init/${NC}"

	run_option_tests
	run_special_tests
	run_positional_tests
	run_variable_tests

	summary
}

main
