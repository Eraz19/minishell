#!/usr/bin/env zsh
###############################################################################
# Suite: shell OPTIONS (POSIX.1-2024 sh(1) + set(1), XCU 2.x)
#
# Covers invocation modes (-c, -s, script operand) and every option from
# tests/test_rules.txt: -a -C -e -f -h -i -n -u -v -x, -o pipefail,
# -o ignoreeof, plus `set`-level option management.
#
# TD options (-e, -u, -v) are written but guarded by td_guard (--td to run).
#
# Project contracts asserted on purpose (documented choices, error.h):
#   121 syntax error | 126 not executable | 127 not found
#   122 special-builtin error | 124 assignment error | 125 expansion error
###############################################################################

###############################################################################
t_section "invocation: -c command string (POSIX sh: -c)"
###############################################################################

tta INVOC-C.1 "-c runs the command string" 0 "hello" \
	-- -c 'echo hello'
tta INVOC-C.2 "-c empty string does nothing, exit 0" 0 "" \
	-- -c ''
tta INVOC-C.3 "-c exit status is last command's" 1 "" \
	-- -c '/bin/false'
tta INVOC-C.4 "-c command-not-found -> 127" 127 "" \
	-- -c 'no_such_command_xyz_42'

t_begin INVOC-C.5 "-c: next operand becomes \$0"
t_run_argv -c 'echo $0' myname
expect_status 0
expect_lines "myname"
t_end

t_begin INVOC-C.6 "-c: operands after \$0 become \$1 \$2"
t_run_argv -c 'echo $1:$2:$#' zero one two
expect_status 0
expect_lines "one:two:2"
t_end

t_begin INVOC-C.7 "-c with no command string -> usage error"
t_run_argv -c
expect_status_nonzero
expect_err_contains "-c"
t_end

###############################################################################
t_section "invocation: -s / stdin / script operand"
###############################################################################

t_begin INVOC-S.1 "no operands: reads commands from stdin"
T_STDIN=$'echo from_stdin\n'
t_run_argv
expect_status 0
expect_lines "from_stdin"
t_end

t_begin INVOC-S.2 "-s explicitly reads from stdin"
T_STDIN=$'echo dash_s\n'
t_run_argv -s
expect_status 0
expect_lines "dash_s"
t_end

t_begin INVOC-S.3 "-s: operands become positional parameters"
T_STDIN=$'echo $1-$2\n'
t_run_argv -s p1 p2
expect_status 0
expect_lines "p1-p2"
t_end

t_begin INVOC-F.1 "script file operand is executed"
t_setup 'printf "echo from_script\n" > s.sh'
t_run_argv ./s.sh
expect_status 0
expect_lines "from_script"
t_end

t_begin INVOC-F.2 "script operand: \$0 = script path, \$1.. = args"
t_setup 'printf "echo \$0 \$1\n" > s.sh'
t_run_argv ./s.sh arg1
expect_status 0
expect_lines "./s.sh arg1"
t_end

t_begin INVOC-F.3 "script not found -> 127 (POSIX sh exit status)"
t_run_argv ./no_such_script.sh
expect_status 127
t_end

t_begin INVOC-F.4 "script not readable -> 126"
t_setup 'printf "echo secret\n" > locked.sh; chmod 000 locked.sh'
t_run_argv ./locked.sh
expect_status 126
t_end

t_begin INVOC-F.5 "empty script -> exit 0"
t_setup ': > empty.sh'
t_run_argv ./empty.sh
expect_status 0
expect_lines
t_end

t_begin INVOC-O.1 "invalid command-line option -> error"
t_run_argv -Z -c 'echo no'
expect_status_nonzero
expect_out_lacks "no"
expect_err_contains "invalid option"
t_end

t_begin INVOC-O.2 "-- ends option parsing (script named like an option dir)"
t_setup 'printf "echo dashdash_ok\n" > s.sh'
t_run_argv -- ./s.sh
expect_status 0
expect_lines "dashdash_ok"
t_end

###############################################################################
t_section "option -a / allexport (POSIX set -a)"
###############################################################################

tth OPT-A.1 "set -a: new variable is exported to children" \
'set -a
NEWVAR_A1=exported_a1
env' 0 "NEWVAR_A1=exported_a1"

t_begin OPT-A.2 "without -a: plain assignment is NOT exported"
t_run 'NOEXP_A2=hidden
env'
expect_status 0
expect_out_lacks "NOEXP_A2=hidden"
t_end

t_begin OPT-A.3 "set -a also exports assignment to a pre-existing variable"
t_run 'OLDVAR_A3=before
set -a
OLDVAR_A3=after
env'
expect_status 0
expect_out_contains "OLDVAR_A3=after"
t_end

t_begin OPT-A.4 "set +a turns allexport back off"
t_run 'set -a
set +a
LATEVAR_A4=nope
env'
expect_status 0
expect_out_lacks "LATEVAR_A4=nope"
t_end

tth OPT-A.5 "set -o allexport is the same option" \
'set -o allexport
NAMEDVAR_A5=v
env' 0 "NAMEDVAR_A5=v"

tta OPT-A.6 "command line -a" 0 "CMDLINE_A6=v" \
	-- -a -c 'CMDLINE_A6=v; env'

tth OPT-A.7 "set -o reports allexport on" \
'set -a
set -o' 0 "allexport	on"

###############################################################################
t_section "option -C / noclobber (POSIX set -C, >| bypass)"
###############################################################################

t_begin OPT-C.1 "set -C: > refuses to overwrite an existing regular file"
t_setup 'printf "keep\n" > exists.txt'
t_run 'set -C
echo new > exists.txt'
expect_status_nonzero
expect_file_lines exists.txt "keep"
t_end

t_begin OPT-C.2 "set -C: > still creates a new file"
t_run 'set -C
echo fresh > new.txt'
expect_status 0
expect_file_lines new.txt "fresh"
t_end

t_begin OPT-C.3 "set -C: >| forces the overwrite (clobber operator)"
t_setup 'printf "old\n" > f.txt'
t_run 'set -C
echo forced >| f.txt'
expect_status 0
expect_file_lines f.txt "forced"
t_end

t_begin OPT-C.4 "set -C: >> append to existing file is allowed"
t_setup 'printf "one\n" > f.txt'
t_run 'set -C
echo two >> f.txt'
expect_status 0
expect_file_lines f.txt "one" "two"
t_end

t_begin OPT-C.5 "set -C: > to a non-regular file (/dev/null) is allowed"
t_run 'set -C
echo sink > /dev/null'
expect_status 0
t_end

t_begin OPT-C.6 "set +C restores clobbering"
t_setup 'printf "old\n" > f.txt'
t_run 'set -C
set +C
echo clobbered > f.txt'
expect_status 0
expect_file_lines f.txt "clobbered"
t_end

t_begin OPT-C.7 "shell survives a noclobber refusal (non-special command)"
t_setup 'printf "keep\n" > exists.txt'
t_run 'set -C
echo new > exists.txt
echo survived'
expect_out_contains "survived"
expect_file_lines exists.txt "keep"
t_end

###############################################################################
t_section "option -e / errexit — TD, not implemented (--td to run)"
###############################################################################

td_guard OPT-E.1 "set -e: shell exits on a failing command" && {
	t_begin OPT-E.1 "set -e: shell exits on a failing command"
	t_run 'set -e
/bin/false
echo unreachable'
	expect_status 1
	expect_out_lacks "unreachable"
	t_end
}

td_guard OPT-E.2 "set -e: failure in && / || does not exit" && {
	t_begin OPT-E.2 "set -e: failure in && / || does not exit"
	t_run 'set -e
/bin/false || echo caught
echo alive'
	expect_status 0
	expect_lines "caught" "alive"
	t_end
}

td_guard OPT-E.3 "set -e: failing if-condition does not exit" && {
	t_begin OPT-E.3 "set -e: failing if-condition does not exit"
	t_run 'set -e
if /bin/false; then echo yes; fi
echo alive'
	expect_status 0
	expect_lines "alive"
	t_end
}

td_guard OPT-E.4 "set -e: ! negated failure does not exit" && {
	t_begin OPT-E.4 "set -e: ! negated failure does not exit"
	t_run 'set -e
! /bin/false
echo alive'
	expect_status 0
	expect_lines "alive"
	t_end
}

td_guard OPT-E.5 "command line -e" && {
	tta OPT-E.5 "command line -e" 1 "" \
		-- -e -c '/bin/false; echo unreachable'
}

###############################################################################
t_section "option -f / noglob (POSIX set -f)"
###############################################################################

t_begin OPT-F.1 "set -f: pathname expansion is disabled"
t_setup 'touch a.glob b.glob'
t_run 'set -f
echo *.glob'
expect_status 0
expect_lines "*.glob"
t_end

t_begin OPT-F.2 "without -f: the same pattern expands"
t_setup 'touch a.glob b.glob'
t_run 'echo *.glob'
expect_status 0
expect_lines "a.glob b.glob"
t_end

t_begin OPT-F.3 "set +f re-enables globbing"
t_setup 'touch a.glob'
t_run 'set -f
set +f
echo *.glob'
expect_status 0
expect_lines "a.glob"
t_end

tta OPT-F.4 "command line -f" 0 "*.nomatch" \
	-- -f -c 'echo *.nomatch'

tth OPT-F.5 "set -o noglob is the same option" \
'set -o noglob
echo *.zzz' 0 "*.zzz"

###############################################################################
t_section "option -h / command hashing (POSIX set -h)"
###############################################################################

t_begin OPT-H.1 "set -h: commands still resolve and run"
t_run 'set -h
/bin/echo hashed_ok'
expect_status 0
expect_lines "hashed_ok"
t_end

t_begin OPT-H.2 "set -h: repeated PATH lookups keep working"
t_setup 'mkdir -p bin; printf "#!/bin/sh\necho tool_ran\n" > bin/mytool_h2; chmod +x bin/mytool_h2'
t_run 'PATH=$PWD/bin:$PATH
set -h
mytool_h2
mytool_h2'
expect_status 0
expect_lines "tool_ran" "tool_ran"
t_end

t_begin OPT-H.3 "set +h: disabling hashing keeps commands runnable"
t_run 'set +h
/bin/echo still_ok'
expect_status 0
expect_lines "still_ok"
t_end

###############################################################################
t_section "option -i / interactive (forced with -s -i on a pipe)"
###############################################################################

t_begin OPT-I.1 "interactive: EOF exits cleanly with last status"
T_STDIN=""
t_run_argv -s -i
expect_status 0
t_end

t_begin OPT-I.2 "interactive: shell survives command-not-found"
T_STDIN=$'no_such_cmd_xyz\necho survived\n'
t_run_argv -s -i
expect_status 0
expect_out_contains "survived"
t_end

t_begin OPT-I.3 "interactive: shell survives a syntax error"
T_STDIN=$'if then\necho survived\n'
t_run_argv -s -i
expect_status 0
expect_out_contains "survived"
t_end

t_begin OPT-I.4 "non-interactive: syntax error aborts with 121 (project code)"
t_run 'if then
echo not_reached'
expect_status 121
expect_out_lacks "not_reached"
expect_err_contains "invalid syntax"
t_end

t_begin OPT-I.5 "non-interactive: command-not-found — 2.8.1 says 'may exit'"
t_run 'no_such_cmd_xyz
echo survived'
# POSIX.1-2024 2.8.1: command not found, non-interactive shell "may exit"
# (diagnostic required either way; 2.9.1: the failed command's status is 127).
# Both branches are conformant — assert whichever one the shell took:
#   continue -> next command runs, final status 0
#   exit     -> status 127, next command never runs
if (( T_RET == 0 )); then
	expect_lines "survived"
else
	expect_status 127
	expect_out_lacks "survived"
fi
expect_err_contains "not found"
t_end

###############################################################################
t_section "option -n / noexec (POSIX set -n)"
###############################################################################

tta OPT-N.1 "-n: commands are parsed but not executed" 0 "" \
	-- -n -c 'echo should_not_print'

t_begin OPT-N.2 "-n: syntax errors are still reported"
t_run_argv -n -c 'if then'
expect_status 121
expect_err_contains "invalid syntax"
t_end

t_begin OPT-N.3 "set -n mid-script stops executing the rest"
t_run 'echo before
set -n
echo after'
expect_status 0
expect_lines "before"
t_end

t_begin OPT-N.4 "-n: no side effects happen (no file created)"
t_run_argv -n -c 'echo x > side_effect.txt'
expect_file_absent side_effect.txt
t_end

###############################################################################
t_section "option -u / nounset — TD, not implemented (--td to run)"
###############################################################################

td_guard OPT-U.1 "set -u: expanding an unset variable is an error" && {
	t_begin OPT-U.1 "set -u: expanding an unset variable is an error"
	t_run 'set -u
echo $UNSET_VAR_U1
echo not_reached'
	expect_status_nonzero
	expect_out_lacks "not_reached"
	t_end
}

td_guard OPT-U.2 "set -u: \${var:-default} is still fine" && {
	t_begin OPT-U.2 "set -u: \${var:-default} is still fine"
	t_run 'set -u
echo ${UNSET_VAR_U2:-fallback}'
	expect_status 0
	expect_lines "fallback"
	t_end
}

td_guard OPT-U.3 "set -u: set variables expand normally" && {
	t_begin OPT-U.3 "set -u: set variables expand normally"
	t_run 'set -u
V=ok
echo $V'
	expect_status 0
	expect_lines "ok"
	t_end
}

###############################################################################
t_section "option -v / verbose — TD, not implemented (--td to run)"
###############################################################################

td_guard OPT-V.1 "set -v: input lines are echoed to stderr" && {
	t_begin OPT-V.1 "set -v: input lines are echoed to stderr"
	t_run 'set -v
echo visible'
	expect_status 0
	expect_lines "visible"
	expect_err_contains "echo visible"
	t_end
}

td_guard OPT-V.2 "command line -v echoes the -c string" && {
	t_begin OPT-V.2 "command line -v echoes the -c string"
	t_run_argv -v -c 'echo hi'
	expect_status 0
	expect_lines "hi"
	expect_err_contains "echo hi"
	t_end
}

###############################################################################
t_section "option -x / xtrace (POSIX set -x, PS4 prefix)"
###############################################################################

t_begin OPT-X.1 "set -x: traces the expanded command on stderr"
t_run 'set -x
echo traced'
expect_status 0
expect_lines "traced"
expect_err_contains "+ echo traced"
t_end

t_begin OPT-X.2 "xtrace shows EXPANDED words, not the source text"
t_run 'X=expanded_val
set -x
echo $X'
expect_status 0
expect_lines "expanded_val"
expect_err_contains "+ echo expanded_val"
t_end

t_begin OPT-X.3 "PS4 value replaces the default '+ ' prefix"
t_run 'PS4=">>> "
set -x
echo custom'
expect_status 0
expect_err_contains ">>> echo custom"
t_end

t_begin OPT-X.4 "set +x stops tracing"
t_run 'set -x
set +x
echo quiet'
expect_status 0
expect_lines "quiet"
expect_err_lacks "+ echo quiet"
t_end

t_begin OPT-X.5 "xtrace goes to stderr, never stdout"
t_run 'set -x
echo only_this'
expect_status 0
expect_lines "only_this"
t_end

tth OPT-X.6 "set -o xtrace is the same option" \
'set -o xtrace
set -o' 0 "xtrace	on"

###############################################################################
t_section "option -o pipefail (POSIX.1-2024 set -o pipefail)"
###############################################################################

tt PIPEFAIL.1 "default: pipeline status = last command" \
'/bin/false | /bin/true
echo rc=$?' 0 "rc=0"

tt PIPEFAIL.2 "pipefail: any failing element fails the pipeline" \
'set -o pipefail
/bin/false | /bin/true
echo rc=$?' 0 "rc=1"

tt PIPEFAIL.3 "pipefail: status of the failing element is kept" \
'set -o pipefail
/bin/sh -c "exit 3" | /bin/true | /bin/true
echo rc=$?' 0 "rc=3"

tt PIPEFAIL.4 "pipefail: all-success pipeline still returns 0" \
'set -o pipefail
echo data | /bin/cat > /dev/null
echo rc=$?' 0 "rc=0"

tt PIPEFAIL.5 "pipefail + ! negation" \
'set -o pipefail
! /bin/false | /bin/true
echo rc=$?' 0 "rc=0"

tt PIPEFAIL.6 "set +o pipefail restores last-command semantics" \
'set -o pipefail
set +o pipefail
/bin/false | /bin/true
echo rc=$?' 0 "rc=0"

tth PIPEFAIL.7 "set -o reports pipefail on" \
'set -o pipefail
set -o' 0 "pipefail	on"

###############################################################################
t_section "option -o ignoreeof (POSIX set -o ignoreeof)"
###############################################################################

t_begin IGNEOF.1 "non-interactive: ignoreeof does not block end-of-input"
t_run 'set -o ignoreeof
echo done'
expect_status 0
expect_lines "done"
t_end

tth IGNEOF.2 "set -o reports ignoreeof on" \
'set -o ignoreeof
set -o' 0 "ignoreeof	on"

t_manual IGNEOF.3 "interactive Ctrl-D is ignored, shell re-prompts" \
	"needs a real tty (a closed-stdin -s -i run would loop forever)"

###############################################################################
t_section "set: option management (set -o / +o listings)"
###############################################################################

t_begin SETOPT.1 "set -o lists every option with its state"
t_run 'set -o'
expect_status 0
for opt in allexport errexit ignoreeof monitor noclobber noexec noglob \
		nolog notify nounset pipefail verbose vi xtrace; do
	expect_out_contains "$opt"
done
t_end

tth SETOPT.2 "set +o prints re-inputtable option commands" \
'set -f
set +o' 0 "set -o noglob" "set +o pipefail"

t_begin SETOPT.3 "set -o with an unknown option name -> error"
t_run 'set -o no_such_option_xyz'
expect_status_nonzero
t_end

t_begin SETOPT.4 "toggling by flag is visible in set -o listing"
t_run 'set -C
set -o'
expect_status 0
expect_out_contains "noclobber	on"
t_end

t_begin SETOPT.5 "set with an invalid flag -> error, shell reports it"
t_run 'set -Z'
expect_status_nonzero
expect_err_contains "invalid option"
t_end
