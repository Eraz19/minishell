#!/usr/bin/env zsh
###############################################################################
# Suite: BUILTIN commands (POSIX.1-2024 XCU: special built-ins 2.14,
# cd/pwd/echo/env/alias/unalias/wait utilities)
#
# Where POSIX pins an exact behavior, the test pins it too.
# Where POSIX only requires ">0" / "unspecified", the test asserts non-zero
# (so it stays green when raw-enum exit codes get swept to POSIX values).
# Where the project documents a choice (error.h codes, ub.c notices), the
# test asserts the documented choice.
###############################################################################

###############################################################################
t_section "colon (:) — special built-in, POSIX 2.14"
###############################################################################

tt COLON.1 "colon alone: no output, exit 0" \
': ' 0

tt COLON.2 "colon ignores its arguments" \
': arg1 arg2 arg3
echo rc=$?' 0 "rc=0"

tt COLON.3 "colon arguments are still expanded (side effects happen)" \
': ${SIDE_C3:=assigned}
echo $SIDE_C3' 0 "assigned"

tt COLON.4 "colon resets \$? to 0" \
'false
:
echo rc=$?' 0 "rc=0"

###############################################################################
t_section "echo — XBD/XCU echo utility"
###############################################################################

t_begin ECHO.1 "echo with no operand prints a single newline"
t_run 'echo'
expect_status 0
expect_out_exact $'\n'
t_end

tt ECHO.2 "echo joins operands with single spaces" \
'echo a b   c' 0 "a b c"

t_begin ECHO.3 "echo -n suppresses the trailing newline"
t_run 'echo -n abc'
expect_status 0
expect_out_exact "abc"
t_end

t_begin ECHO.4 "clustered/repeated -n flags (-nnn, -n -n)"
t_run 'echo -nnn one'
expect_status 0
expect_out_exact "one"
t_end

t_begin ECHO.5 "-n only counts in the leading flag run"
t_run 'echo hi -n'
expect_status 0
expect_lines "hi -n"
t_end

tt ECHO.6 "unknown dash-word is an operand, not a flag" \
'echo -zz' 0 "-zz"

tt ECHO.7 "echo -e enables backslash escapes" \
"echo -e 'a\\tb'" 0 $'a\tb'

t_begin ECHO.8 "echo -e '\\n' makes a real newline"
t_run "echo -e 'l1\\nl2'"
expect_status 0
expect_lines "l1" "l2"
t_end

tt ECHO.9 "without -e escapes stay literal" \
"echo 'a\\tb'" 0 'a\tb'

t_begin ECHO.10 "echo -e '\\c' stops all output (no newline)"
t_run "echo -e 'ab\\cZZZ'"
expect_status 0
expect_out_exact "ab"
t_end

tt ECHO.11 "echo prints expanded variables" \
'V=world
echo hello $V' 0 "hello world"

###############################################################################
t_section "pwd — POSIX pwd utility (-L default, -P physical)"
###############################################################################

t_begin PWD.1 "pwd prints the current directory"
t_run 'pwd'
expect_status 0
expect_lines "$T_DIR"
t_end

t_begin PWD.2 "pwd -L equals pwd (logical is the default)"
t_run 'pwd -L'
expect_status 0
expect_lines "$T_DIR"
t_end

t_begin PWD.3 "pwd -P resolves symlinks"
t_setup 'mkdir -p real; ln -s real link'
t_run 'cd link
pwd -P'
expect_status 0
expect_lines "$T_DIR/real"
t_end

t_begin PWD.4 "pwd -L keeps the logical (symlinked) path"
t_setup 'mkdir -p real; ln -s real link'
t_run 'cd link
pwd -L'
expect_status 0
expect_lines "$T_DIR/link"
t_end

t_begin PWD.5 "pwd tracks cd"
t_setup 'mkdir -p sub'
t_run 'cd sub
pwd'
expect_status 0
expect_lines "$T_DIR/sub"
t_end

###############################################################################
t_section "cd — POSIX cd utility (HOME, -, CDPATH, -L/-P)"
###############################################################################

t_begin CD.1 "cd <dir> changes the working directory"
t_setup 'mkdir -p sub'
t_run 'cd sub
pwd'
expect_status 0
expect_lines "$T_DIR/sub"
t_end

t_begin CD.2 "cd with no operand goes to \$HOME"
t_run 'HOME='"$T_DIR"'
cd
pwd'
expect_status 0
expect_lines "$T_DIR"
t_end

t_begin CD.3 "cd with unset HOME -> error"
T_ENV=(-u HOME)
t_run_argv -c 'unset HOME; cd'
expect_status_nonzero
expect_err_contains "cd"
t_end

t_begin CD.4 "cd - goes to OLDPWD and prints the new directory"
t_setup 'mkdir -p sub'
t_run 'cd sub
cd '"$T_DIR"'
cd -'
expect_status 0
expect_lines "$T_DIR/sub"
t_end

t_begin CD.5 "cd updates PWD and OLDPWD (exported)"
t_setup 'mkdir -p sub'
t_run 'cd sub
echo "PWD=$PWD"
echo "OLDPWD=$OLDPWD"'
expect_status 0
expect_lines "PWD=$T_DIR/sub" "OLDPWD=$T_DIR"
t_end

t_begin CD.6 "cd to a nonexistent directory -> error, message, non-zero"
t_run 'cd ./no_such_dir_xyz
echo rc=$?'
expect_status 0
expect_out_contains "rc="
expect_out_lacks "rc=0"
expect_err_contains "no_such_dir_xyz"
t_end

t_begin CD.7 "cd failure does not abort the shell (cd is not special)"
t_run 'cd ./no_such_dir_xyz
echo survived'
expect_status 0
expect_out_contains "survived"
t_end

t_begin CD.8 "cd with too many operands -> error"
t_run 'cd a b
echo rc=$?'
expect_status 0
expect_out_lacks "rc=0"
expect_err_contains "too many arguments"
t_end

t_begin CD.9 "cd to a plain file -> error (ENOTDIR)"
t_setup 'touch not_a_dir'
t_run 'cd not_a_dir
echo rc=$?'
expect_status 0
expect_out_lacks "rc=0"
t_end

t_begin CD.10 "cd .. resolves logically against PWD"
t_setup 'mkdir -p a/b'
t_run 'cd a/b
cd ..
pwd'
expect_status 0
expect_lines "$T_DIR/a"
t_end

t_begin CD.11 "CDPATH: matching entry is used and the path is printed"
t_setup 'mkdir -p elsewhere/target sub'
t_run 'CDPATH='"$T_DIR"'/elsewhere
cd sub
cd target
pwd'
expect_status 0
expect_out_contains "$T_DIR/elsewhere/target"
t_end

t_begin CD.12 "cd -P enters the physical directory"
t_setup 'mkdir -p real; ln -s real link'
t_run 'cd -P link
pwd'
expect_status 0
expect_lines "$T_DIR/real"
t_end

###############################################################################
t_section "env — POSIX env utility (regular built-in here)"
###############################################################################

tth ENV.1 "env prints NAME=value lines of the environment" \
'env' 0 "PATH="

t_begin ENV.2 "env reflects exported variables"
t_run 'export EVAR_2=visible
env'
expect_status 0
expect_out_contains "EVAR_2=visible"
t_end

t_begin ENV.3 "env does NOT show unexported shell variables"
t_run 'PRIVATE_3=hidden
env'
expect_status 0
expect_out_lacks "PRIVATE_3=hidden"
t_end

t_begin ENV.4 "env NAME=value adds to the printed environment"
t_run 'env INLINE_4=added'
expect_status 0
expect_out_contains "INLINE_4=added"
t_end

t_begin ENV.5 "env -i starts from an empty environment"
t_run 'env -i ONLY_5=alone'
expect_status 0
expect_lines "ONLY_5=alone"
t_end

t_begin ENV.6 "POSIX: env with a utility operand runs the utility"
t_run 'env /bin/echo via_env'
expect_status 0
expect_lines "via_env"
t_end

###############################################################################
t_section "exit — special built-in, POSIX 2.14 exit"
###############################################################################

tta EXIT.1 "exit with no operand uses \$? of the last command" 1 "" \
	-- -c 'false; exit'
tta EXIT.2 "exit 0" 0 "" -- -c 'exit 0'
tta EXIT.3 "exit 5" 5 "" -- -c 'exit 5'
tta EXIT.4 "exit 255 (top of the POSIX range)" 255 "" -- -c 'exit 255'
tta EXIT.5 "exit -- 42 (leading -- is skipped)" 42 "" -- -c 'exit -- 42'

t_begin EXIT.6 "exit stops the script immediately"
t_run 'echo before
exit 7
echo after'
expect_status 7
expect_lines "before"
t_end

t_begin EXIT.7 "exit non-numeric -> project contract 122 + UB notice"
t_run 'exit notanumber'
expect_status 122
expect_err_contains "unspecified behaviour"
t_end

t_begin EXIT.8 "exit 256 -> unspecified; project contract 122"
t_run 'exit 256'
expect_status 122
t_end

t_begin EXIT.9 "exit 300 -> unspecified; project contract n % 256"
t_run 'exit 300'
expect_status 44
t_end

t_begin EXIT.10 "exit with too many operands -> error (still exits, 91)"
t_run 'exit 1 2
echo not_reached'
expect_status 91
expect_out_lacks "not_reached"
expect_err_contains "too many arguments"
t_end

###############################################################################
t_section "export — special built-in, POSIX 2.14 export"
###############################################################################

tth EXPORT.1 "export NAME=value is visible to children" \
'export XP_1=val1
env' 0 "XP_1=val1"

tth EXPORT.2 "export an already-set variable by name" \
'XP_2=val2
export XP_2
env' 0 "XP_2=val2"

tth EXPORT.3 "export multiple assignments at once" \
'export XP_A=1 XP_B=2
env' 0 "XP_A=1" "XP_B=2"

t_begin EXPORT.4 "exported value reaches an external command's envp"
t_run 'export XP_4=deep
'"$TEST_EXEC"''
expect_status 0
expect_err_contains "envp"
expect_err_contains "[XP_4=deep]"
t_end

tth EXPORT.5 "export -p output format: export NAME='value'" \
'export XP_5=v5
export -p' 0 "export XP_5='v5'"

tth EXPORT.6 "export -p single-quotes embedded quotes" \
"export XP_6=\"a b'c\"
export -p" 0 "export XP_6='a b'\\''c'"

t_begin EXPORT.7 "export name with no value flags without assigning"
t_run 'export XP_7
export -p'
expect_status 0
expect_out_contains "XP_7"
t_end

t_begin EXPORT.8 "export invalid identifier -> assignment error 124, shell aborts"
t_run 'export 1BAD=x
echo not_reached'
expect_status 124
expect_out_lacks "not_reached"
expect_err_contains "invalid name"
t_end

t_begin EXPORT.9 "export with no arguments: project UB choice, exit 0"
t_run 'export
echo rc=$?'
expect_status 0
expect_out_contains "rc=0"
t_end

###############################################################################
t_section "readonly — special built-in, POSIX 2.14 readonly"
###############################################################################

t_begin RDONLY.1 "assignment to a readonly variable fails"
t_run 'readonly RO_1=locked
RO_1=changed'
expect_status_nonzero
expect_err_contains "readonly"
t_end

t_begin RDONLY.2 "readonly variable keeps its value"
t_run 'readonly RO_2=keep
RO_2=changed
echo $RO_2'
expect_out_lacks "changed"
t_end

t_begin RDONLY.3 "unset of a readonly variable fails and aborts (special)"
t_run 'readonly RO_3=v
unset RO_3
echo not_reached'
expect_status_nonzero
expect_out_lacks "not_reached"
expect_err_contains "readonly"
t_end

tth RDONLY.4 "readonly -p output format: readonly NAME='value'" \
'readonly RO_4=v4
readonly -p' 0 "readonly RO_4='v4'"

t_begin RDONLY.5 "readonly on an existing variable locks it"
t_run 'RO_5=first
readonly RO_5
RO_5=second'
expect_status_nonzero
t_end

t_begin RDONLY.6 "readonly assignment failure aborts a non-interactive shell"
t_run 'readonly RO_6=v
RO_6=other
echo not_reached'
expect_out_lacks "not_reached"
t_end

###############################################################################
t_section "set — special built-in (positional parameters; options in suite 10)"
###############################################################################

tth SET.1 "set with no args lists shell variables as NAME='value'" \
"LISTED_1=seen
set" 0 "LISTED_1='seen'"

tt SET.2 "set a b c replaces the positional parameters" \
'set a b c
echo $1:$2:$3:$#' 0 "a:b:c:3"

tt SET.3 "set -- clears the positional parameters" \
'set a b
set --
echo count=$#' 0 "count=0"

tt SET.4 "set -- protects operands that look like options" \
'set -- -f -x
echo $1 $2' 0 "-f -x"

tt SET.5 "positional parameters feed \$@ expansion" \
'set p q
for a in "$@"; do echo [$a]; done' 0 "[p]" "[q]"

tt SET.6 "\$* joins with the first IFS character" \
'IFS=-
set a b c
echo "$*"' 0 "a-b-c"

###############################################################################
t_section "unset — special built-in, POSIX 2.14 unset"
###############################################################################

tt UNSET.1 "unset removes a variable" \
'U_1=val
unset U_1
echo [${U_1:-gone}]' 0 "[gone]"

tt UNSET.2 "unset -v is the explicit variable form" \
'U_2=val
unset -v U_2
echo [${U_2:-gone}]' 0 "[gone]"

tt UNSET.3 "unset removes several names at once" \
'A_3=1 B_3=2
unset A_3 B_3
echo [${A_3:-x}][${B_3:-y}]' 0 "[x][y]"

tt UNSET.4 "unset of a variable that does not exist is NOT an error" \
'unset NEVER_SET_4
echo rc=$?' 0 "rc=0"

t_begin UNSET.5 "unset -f removes a function definition"
t_run 'f_u5() { echo defined; }
unset -f f_u5
f_u5
echo rc=$?'
expect_out_contains "rc=127"
t_end

t_begin UNSET.6 "unset with an invalid name -> error"
t_run 'unset 1bad'
expect_status_nonzero
expect_err_contains "invalid name"
t_end

t_begin UNSET.7 "unset with no operand -> usage error"
t_run 'unset'
expect_status_nonzero
t_end

t_begin UNSET.8 "unset variable no longer reaches children"
t_run 'export GONE_8=v
unset GONE_8
env'
expect_status 0
expect_out_lacks "GONE_8=v"
t_end

###############################################################################
t_section "alias / unalias — POSIX alias substitution"
###############################################################################

tt ALIAS.1 "define and use an alias" \
"alias hi_1='echo aliased'
hi_1" 0 "aliased"

tt ALIAS.2 "alias with arguments appended after substitution" \
"alias say_2='echo prefix'
say_2 suffix" 0 "prefix suffix"

tth ALIAS.3 "alias (no operand) lists definitions as name='value'" \
"alias ls_3='echo fake'
alias" 0 "ls_3='echo fake'"

tth ALIAS.4 "alias NAME prints that single definition" \
"alias one_4='echo 1'
alias two_4='echo 2'
alias one_4" 0 "one_4='echo 1'"

t_begin ALIAS.5 "alias of an unknown name -> non-zero + diagnostic"
t_run 'alias no_such_alias_5'
expect_status_nonzero
expect_err_contains "no_such_alias_5"
t_end

tt ALIAS.6 "alias redefinition: last definition wins" \
"alias re_6='echo first'
alias re_6='echo second'
re_6" 0 "second"

tt ALIAS.7 "recursive alias does not loop forever" \
"alias echo='echo wrapped'
echo done" 0 "wrapped done"

tt ALIAS.8 "alias is only substituted in command position" \
"alias notcmd_8='SHOULD_NOT_EXPAND'
echo notcmd_8" 0 "notcmd_8"

tt UNALIAS.1 "unalias removes the definition" \
"alias tmp_u1='echo x'
unalias tmp_u1
tmp_u1
echo rc=\$?" 0 "rc=127"

tt UNALIAS.2 "unalias -a removes everything" \
"alias a_u2='echo a'
alias b_u2='echo b'
unalias -a
a_u2
echo rc=\$?" 0 "rc=127"

t_begin UNALIAS.3 "unalias of an unknown name -> non-zero + diagnostic"
t_run 'unalias no_such_alias_u3'
expect_status_nonzero
expect_err_contains "no_such_alias_u3"
t_end

t_begin UNALIAS.4 "unalias with no operand -> usage error"
t_run 'unalias'
expect_status_nonzero
t_end

###############################################################################
t_section "wait — POSIX wait utility (async pids, \$!)"
###############################################################################

tt WAIT.1 "wait with no children returns 0" \
'wait
echo rc=$?' 0 "rc=0"

tt WAIT.2 "wait for a background job" \
'/bin/sleep 0.1 &
wait
echo rc=$?' 0 "rc=0"

tt WAIT.3 "wait \$! returns that child's exit status (success)" \
'true &
wait $!
echo rc=$?' 0 "rc=0"

tt WAIT.4 "wait \$! returns that child's exit status (failure)" \
'false &
wait $!
echo rc=$?' 0 "rc=1"

t_begin WAIT.5 "wait \$! propagates a custom exit status"
t_run "$TEST_EXEC"' 7 &
wait $!
echo rc=$?'
expect_status 0
expect_out_contains "rc=7"
t_end

tt WAIT.6 "wait on an unknown pid -> 127 (POSIX)" \
'wait 99999999
echo rc=$?' 0 "rc=127"

t_begin WAIT.7 "wait with a non-numeric operand -> error"
t_run 'wait not_a_pid'
expect_status_nonzero
t_end

tt WAIT.8 "wait for several pids" \
'true &
P1=$!
/bin/sleep 0.05 &
P2=$!
wait $P1 $P2
echo rc=$?' 0 "rc=0"

###############################################################################
t_section "trap — special built-in, POSIX 2.14 trap"
###############################################################################

tt TRAP.1 "trap with no operands and no traps set prints nothing" \
'trap' 0

tth TRAP.2 "trap lists as: trap -- 'action' COND" \
"trap 'echo caught' INT
trap" 0 "trap -- 'echo caught' INT"

tth TRAP.3 "trap -p prints requested conditions" \
"trap 'echo t3' TERM
trap -p TERM" 0 "'echo t3' TERM"

tt TRAP.4 "trap - COND resets to default (listing empties)" \
"trap 'echo x' INT
trap - INT
trap" 0

tth TRAP.5 "trap '' COND sets ignore (empty action listed)" \
"trap '' INT
trap" 0 "'' INT"

tth TRAP.6 "numeric condition: 2 means INT" \
"trap 'echo n6' 2
trap" 0 "INT"

t_begin TRAP.7 "invalid condition name -> error, shell continues"
t_run 'trap - NOT_A_SIG
echo survived'
expect_out_contains "survived"
expect_err_contains "NOT_A_SIG"
t_end

t_begin TRAP.8 "EXIT trap action runs when the shell exits (POSIX)"
t_run 'trap "echo exiting" EXIT
echo main'
expect_status 0
expect_lines "main" "exiting"
t_end

tth TRAP.9 "trap EXIT can be set via condition 0" \
"trap 'echo z' 0
trap" 0 "'echo z'"

###############################################################################
t_section "built-in classification (POSIX 2.8.1 / 2.9.1)"
###############################################################################

t_begin CLASS.1 "special built-in error aborts a non-interactive shell"
t_run 'readonly CL_1=v
unset CL_1
echo not_reached'
expect_out_lacks "not_reached"
t_end

t_begin CLASS.2 "intrinsic built-in error does NOT abort (cd)"
t_run 'cd /no/such/dir
echo survived'
expect_status 0
expect_lines "survived"
t_end

tt CLASS.3 "assignment prefix on a special built-in persists (POSIX)" \
'CL_3=persists :
echo [$CL_3]' 0 "[persists]"

tt CLASS.4 "assignment prefix on an external command does NOT persist" \
'CL_4=temp true
echo [${CL_4:-empty}]' 0 "[empty]"

t_begin CLASS.5 "assignment prefix reaches the child environment only"
t_run 'CL_5=childonly '"$TEST_EXEC"'
env'
expect_status 0
expect_err_contains "[CL_5=childonly]"
expect_out_lacks "CL_5=childonly"
t_end

t_begin CLASS.6 "standalone assignment sets a shell variable, exit 0"
t_run 'CL_6=plain
echo $CL_6 rc=$?'
expect_status 0
expect_lines "plain rc=0"
t_end
