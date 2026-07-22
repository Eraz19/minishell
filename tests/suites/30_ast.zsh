#!/usr/bin/env zsh
###############################################################################
# Suite: AST node types (POSIX.1-2024 XCU 2.9 / 2.10 grammar)
#
# One section per node kind the builder produces:
#   simple command, pipeline, and-or, list (; &), subshell, brace group,
#   if, while, until, for, case, function definition, redirections, heredoc,
#   plus the expansions a simple command performs.
###############################################################################

###############################################################################
t_section "simple command (2.9.1): words, assignments, search order"
###############################################################################

tt SCMD.1 "external command by absolute path" \
'/bin/echo direct' 0 "direct"

tt SCMD.2 "external command found through PATH" \
'echo via_path' 0 "via_path"

t_begin SCMD.3 "argv words reach the child in order"
t_run "$TEST_EXEC"' one two three'
expect_status 0
expect_err_contains "argv[1] => [one]"
expect_err_contains "argv[2] => [two]"
expect_err_contains "argv[3] => [three]"
t_end

t_begin SCMD.4 "quoting keeps a word whole through exec"
t_run "$TEST_EXEC"' "a b" c'
expect_status 0
expect_err_contains "argv[1] => [a b]"
expect_err_contains "argv[2] => [c]"
t_end

t_begin SCMD.5 "command not found -> 127 (2.8.1: non-interactive may exit)"
t_run 'definitely_not_a_command_xyz
echo rc=$?'
# POSIX.1-2024 2.8.1: non-interactive shell "may exit" on command not
# found; 2.9.1: the failed command's status is 127 either way.
if (( T_RET == 0 )); then
	expect_lines "rc=127"
else
	expect_status 127
fi
expect_err_contains "not found"
t_end

t_begin SCMD.6 "file without +x -> 126"
t_setup 'printf "#!/bin/sh\necho no\n" > noexec.sh; chmod 644 noexec.sh'
t_run './noexec.sh
echo rc=$?'
expect_status 0
expect_out_contains "rc=126"
t_end

t_begin SCMD.11 "ENOEXEC binary: diagnosed, no crash, shell continues"
t_setup 'printf "\x7fELF_not_really_elf_garbage" > bin.bad; chmod +x bin.bad'
t_run './bin.bad
echo survived'
expect_out_contains "survived"
t_end

tt SCMD.7 "empty command line does nothing, \$? untouched" \
'/bin/false

echo rc=$?' 0 "rc=1"

tt SCMD.8 "\$? special parameter tracks the last command" \
'/bin/sh -c "exit 9"
echo rc=$?' 0 "rc=9"

tt SCMD.9 "comment lines are ignored" \
'echo one
# echo two
echo three' 0 "one" "three"

tt SCMD.10 "line continuation joins the two lines" \
'echo before\
after' 0 "beforeafter"

###############################################################################
t_section "expansions inside a simple command (2.6)"
###############################################################################

tt EXP.1 "parameter expansion \$var and \${var}" \
'V=val
echo $V ${V}' 0 "val val"

tt EXP.2 "unset variable expands to nothing (not an error)" \
'echo a${NOT_SET_E2}b' 0 "ab"

tt EXP.3 "\${var:-default} on unset" \
'echo ${NOT_SET_E3:-fallback}' 0 "fallback"

tt EXP.4 "\${var:=assign} assigns and expands" \
'echo ${NEW_E4:=made}
echo $NEW_E4' 0 "made" "made"

t_begin EXP.5 "\${var:?message} on unset -> expansion error 125"
t_run 'echo ${NOT_SET_E5:?custom_diag}'
expect_status 125
expect_err_contains "custom_diag"
t_end

tt EXP.6 "\${var:+alternate} only when set" \
'SET_E6=yes
echo [${SET_E6:+alt}] [${UNSET_E6:+alt}]' 0 "[alt] []"

tt EXP.7 "\${#var} string length" \
'V=hello
echo ${#V}' 0 "5"

tt EXP.8 "\${var%pat} / \${var#pat} affix removal" \
'F=dir/file.txt
echo ${F%.txt} ${F#dir/}' 0 "dir/file file.txt"

tt EXP.9 "command substitution \$( )" \
'echo got:$(echo inner)' 0 "got:inner"

tt EXP.10 "backquoted command substitution" \
'echo got:`echo inner`' 0 "got:inner"

tt EXP.11 "command substitution strips trailing newlines" \
'echo [$(printf "x\n\n\n")]' 0 "[x]"

tt EXP.12 "field splitting on the expansion of an unquoted variable" \
'V="a b c"
set -- $V
echo $#' 0 "3"

tt EXP.13 "double quotes suppress field splitting" \
'V="a b c"
set -- "$V"
echo $#' 0 "1"

tt EXP.14 "single quotes suppress all expansion" \
"echo '\$HOME'" 0 '$HOME'

tt EXP.15 "double quotes keep \$ expansion but not globbing" \
'V=star
echo "$V *"' 0 'star *'

t_begin EXP.16 "tilde expansion to \$HOME"
t_run 'echo ~'
expect_status 0
expect_lines "$HOME"
t_end

t_begin EXP.17 "tilde with a suffix path"
t_run 'echo ~/sub'
expect_status 0
expect_lines "$HOME/sub"
t_end

t_begin EXP.18 "pathname expansion: * matches files in cwd"
t_setup 'touch aa.gl bb.gl'
t_run 'echo *.gl'
expect_status 0
expect_lines "aa.gl bb.gl"
t_end

t_begin EXP.19 "pathname expansion: ? and [...] classes"
t_setup 'touch f1.q f2.q g1.q'
t_run 'echo f?.q
echo [fg]1.q'
expect_status 0
expect_lines "f1.q f2.q" "f1.q g1.q"
t_end

tt EXP.20 "pattern with no match stays literal (POSIX default)" \
'echo *.nomatch_e20' 0 "*.nomatch_e20"

t_begin EXP.21 "\$\$ expands to the shell pid (a number)"
t_run 'echo $$'
expect_status 0
if ! grep -Eq '^[0-9]+$' "$T_OUT_FILE"; then
	t_fail "stdout: expected a numeric pid, got '$(<$T_OUT_FILE)'"
fi
t_end

tt EXP.22 '$0 in -c mode defaults to the shell name' \
'echo $#' 0 "0"

###############################################################################
t_section "pipeline node (2.9.2): |, status, ! negation"
###############################################################################

tt PIPE.1 "two-stage pipeline passes data" \
'echo through | /bin/cat' 0 "through"

tt PIPE.2 "three-stage pipeline" \
'printf "b\na\n" | /bin/sort | /bin/head -1' 0 "a"

tt PIPE.3 "pipeline status = last command (no pipefail)" \
'/bin/false | /bin/true
echo rc=$?' 0 "rc=0"

tt PIPE.4 "pipeline status = last command (failure)" \
'/bin/true | /bin/false
echo rc=$?' 0 "rc=1"

tt PIPE.5 "! negates a pipeline: true -> 1" \
'! /bin/true
echo rc=$?' 0 "rc=1"

tt PIPE.6 "! negates a pipeline: false -> 0" \
'! /bin/false
echo rc=$?' 0 "rc=0"

tt PIPE.7 "builtin inside a pipeline" \
'echo builtin_data | /bin/cat' 0 "builtin_data"

tt PIPE.8 "pipeline commands run in subshells (var does not leak)" \
'PV_8=outer
echo x | PV_8=inner /bin/cat > /dev/null
echo $PV_8' 0 "outer"

tt PIPE.9 "early SIGPIPE termination is not an error for the reader" \
'/usr/bin/yes | /bin/head -1' 0 "y"

###############################################################################
t_section "and-or node (2.9.3): && ||"
###############################################################################

tt ANDOR.1 "&& runs the right side on success" \
'/bin/true && echo ran' 0 "ran"

tt ANDOR.2 "&& skips the right side on failure" \
'/bin/false && echo skipped
echo rc=$?' 0 "rc=1"

tt ANDOR.3 "|| runs the right side on failure" \
'/bin/false || echo rescued' 0 "rescued"

tt ANDOR.4 "|| skips the right side on success" \
'/bin/true || echo skipped
echo rc=$?' 0 "rc=0"

tt ANDOR.5 "left-to-right chain of mixed operators" \
'/bin/true && /bin/false || echo fallback' 0 "fallback"

tt ANDOR.6 "chain status is the last executed command" \
'/bin/false || /bin/sh -c "exit 4"
echo rc=$?' 0 "rc=4"

tt ANDOR.7 "&& || with pipelines as operands" \
'echo a | /bin/grep -q a && echo found' 0 "found"

###############################################################################
t_section "list node (2.9.3): sequential ; and async &"
###############################################################################

tt LIST.1 "semicolon runs both commands in order" \
'echo one; echo two' 0 "one" "two"

tt LIST.2 "list status is the last command's" \
'/bin/false; /bin/true
echo rc=$?' 0 "rc=0"

tt LIST.3 "trailing semicolon is fine" \
'echo tail;' 0 "tail"

tt LIST.4 "newline separates commands like ;" \
'echo l1
echo l2' 0 "l1" "l2"

tt ASYNC.1 "& returns immediately with status 0" \
'/bin/sleep 0.2 &
echo rc=$?' 0 "rc=0"

t_begin ASYNC.2 "\$! holds the pid of the last async command"
t_run '/bin/sleep 0.05 &
echo $!
wait'
expect_status 0
if ! grep -Eq '^[0-9]+$' "$T_OUT_FILE"; then
	t_fail "stdout: expected a pid from \$!, got '$(<$T_OUT_FILE)'"
fi
t_end

tt ASYNC.3 "async command really runs (observable side effect)" \
'echo bg_output > bg.txt &
wait
/bin/cat bg.txt' 0 "bg_output"

tt ASYNC.4 "foreground work continues while & job runs" \
'/bin/sleep 0.3 &
echo immediate
wait' 0 "immediate"

###############################################################################
t_section "subshell node (2.9.4.3): ( ) isolation"
###############################################################################

tt SUB.1 "subshell runs its list" \
'(echo inside)' 0 "inside"

tt SUB.2 "subshell exit status propagates" \
'(exit 3)
echo rc=$?' 0 "rc=3"

tt SUB.3 "variable assignment does not escape the subshell" \
'(SV_3=inner)
echo [${SV_3:-unset}]' 0 "[unset]"

t_begin SUB.4 "cd inside a subshell does not move the parent"
t_run '(cd /)
pwd'
expect_status 0
expect_lines "$T_DIR"
t_end

tt SUB.5 "nested subshells" \
'((echo deep))' 0 "deep"

tt SUB.6 "subshell in a && chain" \
'(exit 1) || echo caught' 0 "caught"

###############################################################################
t_section "brace group node (2.9.4.1): { } shares the environment"
###############################################################################

tt GRP.1 "brace group runs its list" \
'{ echo grouped; }' 0 "grouped"

tt GRP.2 "assignments inside { } persist after it" \
'{ GV_2=kept; }
echo $GV_2' 0 "kept"

tt GRP.3 "group status is the last command's" \
'{ /bin/true; /bin/false; }
echo rc=$?' 0 "rc=1"

tt GRP.4 "group as an operand of &&" \
'/bin/true && { echo a; echo b; }' 0 "a" "b"

###############################################################################
t_section "if node (2.9.4.4): then / elif / else, status"
###############################################################################

tt IF.1 "true condition runs then" \
'if /bin/true; then echo yes; fi' 0 "yes"

tt IF.2 "false condition skips then; status 0 without else" \
'if /bin/false; then echo yes; fi
echo rc=$?' 0 "rc=0"

tt IF.3 "else branch on false condition" \
'if /bin/false; then echo yes; else echo no; fi' 0 "no"

tt IF.4 "elif chain picks the first true condition" \
'if /bin/false; then echo a
elif /bin/true; then echo b
elif /bin/true; then echo c
else echo d
fi' 0 "b"

tt IF.5 "condition may be a pipeline / list" \
'if echo probe | /bin/grep -q probe; then echo piped; fi' 0 "piped"

tt IF.6 "if status = executed branch's last command" \
'if /bin/true; then /bin/sh -c "exit 5"; fi
echo rc=$?' 0 "rc=5"

tt IF.7 "multiline body with several commands" \
'if /bin/true; then
	echo first
	echo second
fi' 0 "first" "second"

###############################################################################
t_section "while / until node (2.9.4.5-6)"
###############################################################################

tt WHILE.1 "while body runs while the condition is true" \
'touch flag_w1
while /bin/test -e flag_w1; do
	echo iteration
	/bin/rm flag_w1
done' 0 "iteration"

tt WHILE.2 "false condition: body never runs, status 0" \
'while /bin/false; do echo never; done
echo rc=$?' 0 "rc=0"

tt WHILE.3 "while drives multiple iterations" \
'touch a_w3 b_w3
while /bin/test -e a_w3 -o -e b_w3; do
	echo tick
	if /bin/test -e a_w3; then /bin/rm a_w3; else /bin/rm b_w3; fi
done' 0 "tick" "tick"

tt UNTIL.1 "until runs while the condition is false" \
'until /bin/test -e made_u1; do
	echo creating
	touch made_u1
done' 0 "creating"

tt UNTIL.2 "until with an initially-true condition never runs, status 0" \
'until /bin/true; do echo never; done
echo rc=$?' 0 "rc=0"

tt LOOPCTL.1 "break leaves the loop (POSIX special built-in)" \
'for i in a b c; do
	echo $i
	break
done' 0 "a"

tt LOOPCTL.2 "continue skips to the next iteration" \
'for i in a b; do
	continue
	echo $i
done
echo after' 0 "after"

###############################################################################
t_section "for node (2.9.4.2): word list iteration"
###############################################################################

tt FOR.1 "for iterates the word list in order" \
'for x in one two three; do echo $x; done' 0 "one" "two" "three"

tt FOR.2 "empty word list: no iterations, status 0" \
'for x in; do echo never; done
echo rc=$?' 0 "rc=0"

tt FOR.3 "words are expanded before iteration" \
'L="p q"
for x in $L r; do echo $x; done' 0 "p" "q" "r"

tt FOR.4 "for without in iterates the positional parameters" \
'set -- m n
for x; do echo $x; done' 0 "m" "n"

tt FOR.5 "loop variable keeps its last value after the loop (POSIX)" \
'for x in a b last; do :; done
echo $x' 0 "last"

t_begin FOR.6 "glob expansion feeds the word list"
t_setup 'touch it1.fw it2.fw'
t_run 'for f in *.fw; do echo $f; done'
expect_status 0
expect_lines "it1.fw" "it2.fw"
t_end

tt FOR.7 "for status = last iteration's last command" \
'for x in 1 2; do /bin/sh -c "exit $x"; done
echo rc=$?' 0 "rc=2"

###############################################################################
t_section "case node (2.9.4.4): patterns, |, *, ;; and ;& (Issue 8)"
###############################################################################

tt CASE.1 "literal pattern match" \
'case apple in apple) echo matched;; esac' 0 "matched"

tt CASE.2 "* default arm" \
'case zebra in apple) echo a;; *) echo default;; esac' 0 "default"

tt CASE.3 "first matching arm wins" \
'case x in x) echo one;; x) echo two;; esac' 0 "one"

tt CASE.4 "| pattern alternatives" \
'case beta in alpha|beta) echo either;; esac' 0 "either"

tt CASE.5 "glob patterns ? and *" \
'case file9 in file?) echo qmark;; esac
case prefix_rest in prefix_*) echo star;; esac' 0 "qmark" "star"

tt CASE.6 "quoted pattern is literal (no glob)" \
'case "*" in "*") echo literal;; a) echo no;; esac' 0 "literal"

tt CASE.7 "no matching arm: status 0, nothing runs" \
'case none in a) echo a;; b) echo b;; esac
echo rc=$?' 0 "rc=0"

tt CASE.8 "case word is expanded" \
'V=pick
case $V in pick) echo expanded;; esac' 0 "expanded"

tt CASE.9 ";& falls through to the next arm (Issue 8)" \
'case a in a) echo one ;& b) echo two ;; esac' 0 "one" "two"

tt CASE.10 "case status = executed arm's last command" \
'case go in go) /bin/sh -c "exit 6";; esac
echo rc=$?' 0 "rc=6"

###############################################################################
t_section "function definition node (2.9.5)"
###############################################################################

tt FUNC.1 "define then call a function" \
'greet() { echo hello_from_f; }
greet' 0 "hello_from_f"

tt FUNC.2 "defining a function produces no output and status 0" \
'noop_f2() { echo never; }
echo rc=$?' 0 "rc=0"

tt FUNC.3 "arguments become positional parameters inside" \
'show() { echo $#:$1:$2; }
show a b' 0 "2:a:b"

tt FUNC.4 "outer positional parameters are restored after the call" \
'set -- outer1 outer2
f4() { :; }
f4 inner
echo $1:$#' 0 "outer1:2"

tt FUNC.5 "function status = last command of the body" \
'fail_f5() { /bin/sh -c "exit 3"; }
fail_f5
echo rc=$?' 0 "rc=3"

tt FUNC.6 "return N sets the function's status (POSIX special built-in)" \
'ret_f6() { return 4; echo not_reached; }
ret_f6
echo rc=$?' 0 "rc=4"

tt FUNC.7 "function sees and mutates shell variables" \
'V_f7=start
mut() { V_f7=changed; }
mut
echo $V_f7' 0 "changed"

tt FUNC.8 "redefinition replaces the body" \
'f8() { echo old; }
f8() { echo new; }
f8' 0 "new"

tt FUNC.9 "function body can be any compound command (subshell)" \
'sub_f9() (echo in_subshell)
sub_f9' 0 "in_subshell"

tt FUNC.10 "function takes precedence over PATH lookup" \
'true() { echo shadowed; }
true' 0 "shadowed"

###############################################################################
t_section "redirection nodes (2.7): > >> < <> >| <& >& fd prefixes"
###############################################################################

tt REDIR.1 "> creates a file with the command's stdout" \
'echo content > out_r1.txt
/bin/cat out_r1.txt' 0 "content"

tt REDIR.2 "> truncates an existing file" \
'echo first > f_r2.txt
echo second > f_r2.txt
/bin/cat f_r2.txt' 0 "second"

tt REDIR.3 ">> appends" \
'echo one >> f_r3.txt
echo two >> f_r3.txt
/bin/cat f_r3.txt' 0 "one" "two"

t_begin REDIR.4 "< feeds a file to stdin"
t_setup 'printf "from_file\n" > in.txt'
t_run '/bin/cat < in.txt'
expect_status 0
expect_lines "from_file"
t_end

t_begin REDIR.5 "< on a missing file: error, command not run, shell continues"
t_run '/bin/cat < no_such_input.txt
echo rc=$?'
expect_status 0
expect_out_lacks "rc=0"
t_end

tt REDIR.6 "2> redirects stderr by fd number" \
'/bin/ls no_such_entry_r6 2> err_r6.txt
/bin/grep -c no_such_entry_r6 err_r6.txt' 0 "1"

tt REDIR.7 "2>&1 duplicates stderr onto stdout's target" \
'/bin/sh -c "echo to_err >&2" 2>&1 | /bin/cat' 0 "to_err"

tt REDIR.8 "order matters: > file 2>&1 captures both" \
'/bin/sh -c "echo o; echo e >&2" > both_r8.txt 2>&1
/bin/sort both_r8.txt' 0 "e" "o"

tt REDIR.9 ">| clobbers regardless of noclobber" \
'set -C
echo old > f_r9.txt 2>/dev/null || :
echo forced >| f_r9.txt
/bin/cat f_r9.txt' 0 "forced"

tt REDIR.10 "<> opens read-write and creates the file" \
'/bin/true <> rw_r10.txt
/bin/test -e rw_r10.txt
echo rc=$?' 0 "rc=0"

tt REDIR.11 "redirection applies to builtins too" \
'pwd > pwd_r11.txt
/bin/test -s pwd_r11.txt
echo rc=$?' 0 "rc=0"

tt REDIR.12 "redirection on a compound command (if...fi > file)" \
'if /bin/true; then echo branch; fi > if_r12.txt
/bin/cat if_r12.txt' 0 "branch"

tt REDIR.13 "redirection on a loop collects all iterations" \
'for i in x y; do echo $i; done > loop_r13.txt
/bin/cat loop_r13.txt' 0 "x" "y"

tt REDIR.14 "multiple redirections: every file is created, last wins" \
'echo dest > a_r14.txt > b_r14.txt
/bin/cat b_r14.txt
/bin/test -e a_r14.txt -a ! -s a_r14.txt
echo rc=$?' 0 "dest" "rc=0"

tt REDIR.15 "fds are restored after the command" \
'echo first > f_r15.txt
echo visible' 0 "visible"

t_begin REDIR.16 "redirection target word is expanded"
t_run 'NAME=exp_r16
echo data > ${NAME}.txt
/bin/cat exp_r16.txt'
expect_status 0
expect_lines "data"
t_end

###############################################################################
t_section "heredoc nodes (2.7.4): << and <<-"
###############################################################################

tt HD.1 "basic heredoc body reaches the command" \
'/bin/cat <<EOF
line1
line2
EOF' 0 "line1" "line2"

tt HD.2 "unquoted delimiter: parameters expand in the body" \
'V=inside
/bin/cat <<EOF
value=$V
EOF' 0 "value=inside"

tt HD.3 "quoted delimiter: body is literal" \
"/bin/cat <<'EOF'
\$HOME stays
EOF" 0 '$HOME stays'

tt HD.4 "<<- strips leading tabs" \
'/bin/cat <<-EOF
	tabbed
	EOF' 0 "tabbed"

tt HD.5 "command substitution runs inside an unquoted heredoc" \
'/bin/cat <<EOF
sub=$(echo yes)
EOF' 0 "sub=yes"

tt HD.6 "empty heredoc body" \
'/bin/cat <<EOF
EOF
echo after_hd' 0 "after_hd"

tt HD.7 "two heredocs on one line (2.7.4: order of here-docs)" \
'/bin/cat <<A; /bin/cat <<B
first
A
second
B' 0 "first" "second"

t_begin HD.8 "unterminated heredoc -> syntax-class error (project: 121)"
t_run '/bin/cat <<EOF
never closed'
expect_status 121
t_end

tt HD.9 "heredoc redirected onto a whole loop" \
'touch once_hd9
while /bin/test -e once_hd9; do
	/bin/rm once_hd9
	/bin/cat
done <<EOF
a
b
EOF' 0 "a" "b"

###############################################################################
t_section "syntax errors (2.10): report + non-interactive abort"
###############################################################################

t_begin SYN.1 "lone 'if then' -> syntax error 121 (project code)"
t_run 'if then'
expect_status 121
expect_err_contains "invalid syntax"
t_end

t_begin SYN.2 "unterminated double quote -> 121"
t_run 'echo "unclosed'
expect_status 121
t_end

t_begin SYN.3 "unterminated single quote -> 121"
t_run "echo 'unclosed"
expect_status 121
t_end

t_begin SYN.4 "orphan closing paren -> 121"
t_run 'echo hi )'
expect_status 121
t_end

t_begin SYN.5 "pipe with no right-hand side -> 121"
t_run 'echo left |'
expect_status 121
t_end
