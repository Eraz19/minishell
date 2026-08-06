#!/usr/bin/env zsh
###############################################################################
# Suite: semantics — redirections, error consequences, simple-command
#        semantics, grammar edges, special built-ins
#        (POSIX.1-2024 XCU 2.7, 2.8, 2.9.1, 2.10, 2.15)
#
# Every case cites the clause it checks (line refs = ressouces/3_POSIX_chap_2.txt).
# Sections:
#   RED2   2.7    redirection edge cases (word expansion, fd ops, ordering)
#   HD2    2.7.4  here-document edge cases
#   ERRC   2.8.1  consequences-of-errors table
#   STA    2.8.2  exit statuses
#   ASG    2.9.1  simple-command assignment/redirection semantics
#   GRM    2.10   grammar edges (newlines, reserved words, groups)
#   LOOPN  2.15   break/continue with n
#   SHIFT  2.15   shift
#   EVAL   2.15   eval
#   DOT    2.15   dot
#   RET    2.15   return
###############################################################################

###############################################################################
t_section "redirection edges (2.7): word expansion, fd ops, ordering"
###############################################################################

# 2.7 (line 695): the redirection word undergoes tilde/param/cmd-sub/quote
# removal but NO field splitting — a value with a space names ONE file.
t_begin RED2.1 "redirection target is not field split"
t_run 'f="a b"
echo hi > $f'
expect_status 0
expect_lines
expect_file_lines "a b" "hi"
t_end

# 2.7 (line 699): redirections apply left to right. 2>&1 BEFORE >file dups
# stderr onto the old stdout, then only stdout moves to the file.
# NOTE: needle assertion, not exact lines — on debug builds the shell's own
# banners follow the 2>&1 dup onto the captured stdout (harness only filters
# the stderr stream).
t_begin RED2.2 "2>&1 >file: stderr keeps the old stdout"
t_run '{ echo out; echo err >&2; } 2>&1 >ordered.txt'
expect_status 0
expect_out_contains "err"
expect_file_lines ordered.txt "out"
t_end

# 2.7.5: <&- closes standard input; the command fails but the shell goes on.
t_begin RED2.3 "<&- closes stdin, command fails, shell continues"
t_run 'cat <&-
echo rc=$?'
expect_status 0
expect_out_contains "rc="
expect_out_lacks "rc=0"
t_end

# 2.7.6: >&- closes standard output; the write fails, nothing is printed.
t_begin RED2.4 ">&- closes stdout: echo fails, shell continues"
t_run 'echo hi >&-
echo rc=$?'
expect_status 0
expect_out_lacks "hi"
expect_out_lacks "rc=0"
expect_out_contains "rc="
t_end

# 2.7.6: duplicating from a descriptor that was never opened is a
# redirection error; with an external utility the shell shall not exit
# (2.8.1 table line 846) and the command is not run.
t_begin RED2.5 "dup from unopened fd 7 fails, shell continues"
t_run 'echo hi >&7
echo rc=$?'
expect_status 0
expect_out_lacks "hi"
expect_out_lacks "rc=0"
expect_out_contains "rc="
t_end

# 2.7.7: <> opens read-write WITHOUT truncating an existing file.
t_begin RED2.6 "<> does not truncate an existing file"
t_setup 'printf "keep\n" > keep.txt'
t_run ': <> keep.txt
cat keep.txt'
expect_status 0
expect_lines "keep"
t_end

# 2.9.1.3 (line 952): a command of only redirections runs them (in a
# subshell environment) and completes with status 0.
t_begin RED2.7 "redirection-only command creates the file, status 0"
t_run '> made.txt
echo rc=$?'
expect_status 0
expect_lines "rc=0"
expect_file_lines made.txt
t_end

# 2.9.1.3 (line 952) + 2.8.1 (table line 846): a failing redirection-only
# command fails with >0 but does not abort the shell.
t_begin RED2.8 "failing redirection-only command: >0, shell continues"
t_run '> /nonexistent_red8/f
echo rc=$?'
expect_status 0
expect_out_lacks "rc=0"
expect_out_contains "rc="
t_end

# 2.7.4 + 2.7: a heredoc and an output redirection can share one command.
t_begin RED2.9 "heredoc input combined with > output"
t_run 'cat <<EOF >hd.out
body line
EOF
cat hd.out'
expect_status 0
expect_lines "body line"
t_end

# 2.9.2: each pipeline stage applies its own redirections — a > inside the
# first stage starves the pipe, not the file.
t_begin RED2.10 "redirection inside a pipeline stage wins over the pipe"
t_run 'echo a > redirf | cat
cat redirf'
expect_status 0
expect_lines "a"
t_end

# 2.7.3: >> creates the file when it does not exist.
t_begin RED2.11 ">> creates a missing file"
t_run 'echo first >> new.txt
cat new.txt'
expect_status 0
expect_lines "first"
t_end

###############################################################################
t_section "here-document edges (2.7.4)"
###############################################################################

# 2.7.4: ANY quoting in the delimiter (even partial) makes the body literal.
tt HD2.1 "partially quoted delimiter suppresses expansion" \
'cat <<E"O"F
$HOME literal
EOF' 0 '$HOME literal'

# 2.7.4: in an unquoted-delimiter body, backslash escapes $ (heredoc quoting).
tt HD2.2 "backslash protects \$ in an unquoted heredoc body" \
'x=v
cat <<EOF
\$x and $x
EOF' 0 '$x and v'

# 2.7.4: <<- strips leading TABS only; spaces are preserved.
t_begin HD2.3 "<<- strips tabs but not spaces"
t_run "$(printf 'cat <<-EOF\n\ttabbed\n  spaced\n\tEOF\n')"
expect_status 0
expect_lines "tabbed" "  spaced"
t_end

# 2.7.4: the line must contain EXACTLY the delimiter — a leading space makes
# it body text.
tt HD2.4 "delimiter with leading space is body, not terminator" \
'cat <<EOF
a
 EOF
EOF' 0 "a" " EOF"

# 2.7.4: quoted delimiter also disables command substitution in the body.
tt HD2.5 "quoted delimiter keeps cmd-sub literal" \
"cat <<'EOF'
\$(echo x) \`echo y\`
EOF" 0 '$(echo x) `echo y`'

# 2.7.4: unquoted delimiter: backquote command substitution runs in the body.
tt HD2.6 "backquote cmd-sub runs in an unquoted body" \
'cat <<EOF
`echo sub`
EOF' 0 "sub"

# 2.9.5 + 2.7.4: a heredoc can feed a function call.
tt HD2.7 "heredoc feeds a function invocation" \
'f() { cat; }
f <<EOF
fed
EOF' 0 "fed"

# 2.7.4: quote removal is NOT performed on the body — quotes are data.
tt HD2.8 "quotes in the body are literal data" \
'cat <<EOF
"dq" and '"'"'sq'"'"'
EOF' 0 '"dq" and '"'"'sq'"'"''

###############################################################################
t_section "consequences of shell errors (2.8.1 table)"
###############################################################################

# 2.8.1 (table line 819): redirection error WITH a special built-in ->
# non-interactive shell shall exit.
t_begin ERRC.1 "redirection error on special built-in aborts"
t_run ': > /nonexistent_errc1/f
echo after'
expect_status_nonzero
expect_out_lacks "after"
t_end

# 2.8.1 (table line 846): redirection error with an ordinary utility ->
# shall not exit; the command fails with >0.
t_begin ERRC.2 "redirection error on external continues"
t_run 'echo x > /nonexistent_errc2/f
echo rc=$?'
expect_status 0
expect_out_lacks "x"
expect_out_lacks "rc=0"
expect_out_contains "rc="
t_end

# 2.8.1 (table line 863) + 2.6.2: expansion error (unset + '?') -> diagnostic
# naming the parameter, non-interactive shell exits (project code 125).
t_begin ERRC.3 "expansion error \${x?} aborts with the parameter named"
t_run 'echo ${u_errc3?custom_msg}
echo after'
expect_status 125
expect_err_contains "u_errc3"
expect_out_lacks "after"
t_end

# 2.9.1.2 (line 949) + 2.8.1 (table line 855): assigning to a readonly via a
# command prefix is a variable assignment error -> command not run, shell exits.
t_begin ERRC.4 "readonly assignment prefix aborts, command not run"
t_run 'readonly r_errc4=1
r_errc4=2 echo hi
echo after'
expect_status_nonzero
expect_out_lacks "hi"
expect_out_lacks "after"
t_end

# 2.8.1 (line 895): errors in a subshell environment (pipeline stage) do not
# abort the parent; pipeline status stays the LAST command's.
tte ERRC.5 "not-found in a pipeline stage: parent unaffected" \
'nosuchcmd_errc5 | cat
echo rc=$?' 0 "not found" "rc=0"

###############################################################################
t_section "exit statuses (2.8.2)"
###############################################################################

# 2.8.2: a command terminated by a signal reports status > 128 (128+SIGTERM).
tt STA.1 "signal death reports 128+n" \
'sh -c '"'"'kill -TERM $$'"'"'
echo rc=$?' 0 "rc=143"

###############################################################################
t_section "simple-command semantics (2.9.1)"
###############################################################################

# 2.9.1.1 (line 924): assignments are performed from beginning to end —
# a duplicate assignment lets the LAST value win.
tt ASG.1 "duplicate assignment prefixes: last one wins" \
'X_asg1=1 X_asg1=2 sh -c '"'"'echo $X_asg1'"'"'' 0 "2"

# 2.9.1.2 (line 938): every assignment prefix is exported to the command.
tt ASG.2 "all assignment prefixes reach the child environment" \
'A_asg2=1 B_asg2=2 sh -c '"'"'echo $A_asg2$B_asg2'"'"'' 0 "12"

# 2.9.1 (line 921): redirections may appear BEFORE the command word.
t_begin ASG.3 "redirection before the command name"
t_run '>pre.txt echo hi
cat pre.txt'
expect_status 0
expect_lines "hi"
t_end

# 2.10.2 (rule 7): an assignment-shaped word AFTER the command name is an
# ordinary argument.
tt ASG.4 "NAME=value after the command word is an argument" \
'echo A=1' 0 "A=1"

# 2.9.1.2 + 2.9.1.4: a PATH assignment prefix affects the search for that
# very command.
tt ASG.5 "PATH prefix changes the lookup of the command itself" \
'PATH=/nonexistent_asg5 ls
echo rc=$?' 0 "rc=127"

###############################################################################
t_section "grammar edges (2.10): newlines, reserved words, groups"
###############################################################################

# 2.10.2: each reserved word of if/then/fi may sit on its own line.
tt GRM.1 "if / then / fi on separate lines" \
'if true
then
echo branch
fi' 0 "branch"

# 2.10.2 (for_clause): a newline is allowed between the name and 'in'.
tt GRM.2 "for with newline before in" \
'for i
in a b
do
echo $i
done' 0 "a" "b"

# 2.10.2 (case_item): the pattern may be introduced by an optional '('.
tt GRM.3 "case pattern with leading parenthesis" \
'case x in (x) echo m ;; esac' 0 "m"

# 2.10.2: '}' only terminates a brace group as a COMMAND word — 'echo hi }'
# absorbs it as an argument and the group is never closed -> syntax error.
tt GRM.4 "unterminated brace group is a syntax error" \
'{ echo hi }' 121

# 2.4/2.10: outside command position '{' and '}' are ordinary words.
tt GRM.5 "{ and } as arguments are literal" \
'echo } {' 0 "} {"

# 2.10.2: a compound_list cannot be empty — 'then;' is a syntax error.
tt GRM.6 "empty command between then and ; is a syntax error" \
'if true; then; echo x; fi' 121

# 2.9.5: blanks are allowed between the function name and '()'.
tt GRM.7 "function definition with spaced parentheses" \
'f () { echo spaced; }
f' 0 "spaced"

# 2.4: reserved words are only recognized in command (first-word) position.
tt GRM.8 "reserved words as arguments stay literal" \
'echo if then else fi do done case esac while' 0 \
"if then else fi do done case esac while"

###############################################################################
t_section "break / continue with n (2.15, pages @1791/@2006)"
###############################################################################

# break page: 'break n' exits the nth enclosing loop.
tt LOOPN.1 "break 2 exits both loops" \
'for i in 1 2; do for j in 1 2; do echo $i$j; break 2; done; done
echo after' 0 "11" "after"

# break page: n greater than the number of enclosing loops -> the OUTERMOST
# loop is exited; this is not an error.
tt LOOPN.2 "break with n larger than the nesting depth" \
'for i in 1 2; do break 9; echo body; done
echo rc=$?' 0 "rc=0"

# continue page: 'continue n' returns to the top of the nth enclosing loop —
# the rest of BOTH bodies is skipped.
tt LOOPN.3 "continue 2 resumes the outer loop" \
'for i in 1 2; do for j in a b; do continue 2; echo inner; done; echo outer; done
echo end' 0 "end"

# continue page: n larger than the nesting depth -> outermost loop is used.
tt LOOPN.4 "continue with n larger than the nesting depth" \
'for i in 1 2; do continue 9; echo body; done
echo end' 0 "end"

###############################################################################
t_section "shift (2.15, page @3118)"
###############################################################################

# shift page: without n, shift by 1.
tt SHIFT.1 "shift defaults to n=1" \
'set a b c
shift
echo $1 $#' 0 "b 2"

# shift page (spec example): parameters move down, # is updated.
tt SHIFT.2 "shift 2 renumbers the positionals" \
'set a b c d e
shift 2
echo $# $1 $2' 0 "3 c d"

# shift page: n=0 changes nothing and returns 0.
tt SHIFT.3 "shift 0 is a successful no-op" \
'set a b
shift 0
echo rc=$? n=$# f=$1' 0 "rc=0 n=2 f=a"

# shift page: n equal to $# empties the positional parameters.
tt SHIFT.4 "shift \$# leaves zero parameters" \
'set a b c
shift $#
echo n=$#' 0 "n=0"

# shift page EXIT STATUS: n > $# is an error — the shell may exit; if it
# does not, shift returns non-zero. Either way the && branch must not run.
t_begin SHIFT.5 "shift beyond \$# fails either lane"
t_run 'set a b
shift 3 && echo BAD'
expect_status_nonzero
expect_out_lacks "BAD"
t_end

###############################################################################
t_section "eval (2.15, page @2182)"
###############################################################################

# eval page: arguments are joined with spaces and executed; eval's status is
# the constructed command's status.
tt EVAL.1 "eval joins its arguments into one command" \
'eval echo a b
echo rc=$?' 0 "a b" "rc=0"

# eval page: no arguments (or empty) -> status 0.
tt EVAL.2 "eval with no arguments returns 0" \
'eval
echo rc=$?' 0 "rc=0"

# eval page: exit status of the evaluated command is passed through.
tt EVAL.3 "eval propagates the command's status" \
'eval '"'"'sh -c "exit 5"'"'"'
echo rc=$?' 0 "rc=5"

# eval page: the command may be built from expansions.
tt EVAL.4 "eval executes a command built from variables" \
'c=echo
eval "$c built"' 0 "built"

###############################################################################
t_section "dot (2.15, page @2091)"
###############################################################################

# dot page: commands execute in the CURRENT environment — assignments persist.
t_begin DOT.1 "dot script runs in the current environment"
t_setup 'printf "v_dot1=42\n" > lib.sh'
t_run '. ./lib.sh
echo $v_dot1'
expect_status 0
expect_lines "42"
t_end

# dot + return pages: return N stops the dot script; N becomes dot's status.
t_begin DOT.2 "return stops the dot script with its status"
t_setup 'printf "echo one\nreturn 9\necho two\n" > r.sh'
t_run '. ./r.sh
echo rc=$?'
expect_status 0
expect_lines "one" "rc=9"
t_end

# dot page + 2.8.1: a missing file is a special built-in error -> the
# non-interactive shell exits.
t_begin DOT.3 "dot with a missing file aborts"
t_run '. ./nope_dot3.sh
echo after'
expect_status_nonzero
expect_out_lacks "after"
t_end

# dot page: an operand without a slash is searched via PATH.
t_begin DOT.4 "dot searches PATH for slash-free operands"
t_setup 'printf "echo found\n" > dotlib'
t_run 'PATH="$PWD:$PATH"
. dotlib'
expect_status 0
expect_lines "found"
t_end

###############################################################################
t_section "return (2.15, page @2744)"
###############################################################################

# return page EXIT STATUS: without n, return uses the current value of \$?.
tt RET.1 "return without operand keeps the last status" \
'f() { sh -c "exit 4"; return; }
f
echo rc=$?' 0 "rc=4"
