#!/usr/bin/env zsh
###############################################################################
# Suite: words — tokenization, quoting and word expansions
#        (POSIX.1-2024 XCU 2.2, 2.3, 2.5, 2.6, 2.14)
#
# Every case cites the clause it checks (line refs = ressouces/3_POSIX_chap_2.txt).
# Sections:
#   QUO  2.2   quoting (backslash, '', "", $'')
#   TOK  2.3   token recognition + 2.3.1 alias substitution edges
#   SPP  2.5.2 special parameters ($# $? $- $$ $@ $* positional)
#   PEX  2.6.2 parameter expansion (unset-vs-null table, affix patterns)
#   CSB  2.6.3 command substitution
#   FSP  2.6.5 field splitting algorithm
#   PAT  2.6.6/2.14 pathname expansion and pattern matching
#   TIL  2.6.1 tilde expansion edges
#   QRM  2.6.7 quote removal
###############################################################################

###############################################################################
t_section "quoting (2.2): backslash, single-, double-, dollar-single-quotes"
###############################################################################

# 2.2.1: unquoted backslash preserves the literal value of the next character.
tt QUO.1 "backslash escapes \$, backslash and dquote" \
'V=nope
echo \$V \\ \"' 0 '$V \ "'

# 2.2.1: <backslash><newline> is removed entirely, so it can splice a token
# across lines without acting as a separator (SCMD.10 tests word joining;
# this splices the command NAME itself).
tt QUO.2 "line continuation splices a command name" \
'ec\
ho spliced' 0 "spliced"

# 2.2.2: every character between single-quotes is literal.
tt QUO.3 "single quotes make operators and \$ literal" \
"echo '\$V \`x\` | ; & < > ( ) *'" 0 '$V `x` | ; & < > ( ) *'

# 2.2.3: inside double-quotes whitespace is preserved and no field splitting
# happens; $ keeps its expansion meaning.
tt QUO.4 "double quotes keep inner spacing around an expansion" \
'V=v
echo "a  b   $V"' 0 "a  b   v"

# 2.2.3 (line 66): in double-quotes backslash is special ONLY before
# $ ` \ <newline> (and "). Before other characters it stays literal.
tt QUO.5 "backslash in dquotes: special before \$ and \\, literal before a" \
'echo "\$x \a \\ \""' 0 '$x \a \ "'

# 2.2.3: backslash-newline inside double-quotes is still a line continuation.
tt QUO.6 "line continuation inside double quotes" \
'echo "a\
b"' 0 "ab"

# 2.2.2/2.2.3: an unescaped newline inside quotes is data, not a separator.
tt QUO.7 "literal newline inside double quotes is kept" \
'echo "l1
l2"' 0 "l1" "l2"

# 2.2 (line 30): quoting prevents reserved-word recognition; "if" is then an
# ordinary command name that is not found (127), and the shell continues.
tt QUO.8 "quoted reserved word is not a reserved word" \
'"if" true
echo rc=$?' 0 "rc=127"

# 2.2.3: quoted operator characters are ordinary word characters.
tt QUO.9 "quoted control operators are literal arguments" \
'echo "a|b" ";" "&&" ">x"' 0 'a|b ; && >x'

# 2.3 rule 4: quoting affects characters, not tokens — adjacent quoted parts
# form ONE word (verified through the child argv, not echo).
t_begin QUO.10 "adjacent quoted strings concatenate into one field"
t_run "$TEST_EXEC"' "a"b'"'"'c'"'"' d'
expect_status 0
expect_err_contains "argv[1] => [abc]"
expect_err_contains "argv[2] => [d]"
t_end

# 2.2.4: $'...' escape sequences (\t) are processed before word expansion.
tt QUO.11 "dollar-single-quotes: \\t yields a tab" \
"echo \$'a\tb'" 0 $'a\tb'

# 2.2.4: \' does not terminate the dollar-single-quote sequence.
tt QUO.12 "dollar-single-quotes: escaped quote stays inside" \
"echo \$'A\\'B'" 0 "A'B"

# 2.2.4: \n yields a real newline in the resulting word.
tt QUO.13 "dollar-single-quotes: \\n yields a newline" \
"echo \$'l1\nl2'" 0 "l1" "l2"

# 2.2.4: \xXX (hex) and \ddd (octal) yield the corresponding bytes;
# the sequence ends at the first character not of the expected type.
tt QUO.14 "dollar-single-quotes: hex and octal escapes" \
"echo \$'\x41\102'" 0 "AB"

# 2.2.3 (line 52): inside double-quotes, $ does NOT introduce the $'...'
# quoting form — the text stays literal.
tt QUO.15 "no dollar-single-quote processing inside double quotes" \
"echo \"\$'x'\"" 0 "\$'x'"

###############################################################################
t_section "token recognition (2.3) + alias substitution (2.3.1)"
###############################################################################

# 2.3 rule 6: an unquoted redirection character delimits the current word —
# no blank is needed before the operator.
t_begin TOK.1 "operator delimits a word without blanks (echo a>b)"
t_run 'echo a>b'
expect_status 0
expect_lines
expect_file_lines b "a"
t_end

# 2.7 (line 680): a QUOTED fd number is not part of a redirection — it is an
# ordinary argument word.
t_begin TOK.2 "quoted digit before > is an argument, not an fd prefix"
t_run 'echo a "2">f'
expect_status 0
expect_lines
expect_file_lines f "a 2"
t_end

# 2.7 (spec examples, lines 682/685): echo \2>a redirects and writes '2';
# echo 2\>a performs NO redirection at all.
t_begin TOK.3 "spec examples: escaped fd digit vs escaped operator"
t_run 'echo \2>a
echo 2\>a'
expect_status 0
expect_lines "2>a"
expect_file_lines a "2"
t_end

# 2.3 rule 9/10: '#' starts a comment only where a new word would start.
tt TOK.4 "# inside a word is not a comment" \
'echo a#b #this is a comment' 0 "a#b"

# 2.3 rule 6 + 2.10 grammar: '&&&' cannot be parsed ('&' is not a valid
# and_or continuation) -> syntax error, project code 121.
tte TOK.5 "&&& is a syntax error" \
'echo a &&& echo b' 121 ""

# 2.10 grammar: ';;' only exists inside case -> syntax error elsewhere.
tte TOK.6 ";; outside a case statement is a syntax error" \
'echo a ;; echo b' 121 ""

# 2.10 (linebreak after '|'): a newline after the pipe continues the pipeline.
tt TOK.7 "newline after | continues the pipeline" \
'echo piped |
cat' 0 "piped"

# 2.10 (linebreak after AND_IF): same for &&.
tt TOK.8 "newline after && continues the and-or list" \
'true &&
echo continued' 0 "continued"

# 2.3.1 (line 168): an alias value ending in a blank subjects the NEXT word
# to alias substitution too.
tt TOK.9 "alias value ending in blank triggers alias check on next word" \
"alias e='echo ' hi='HELLO'
e hi" 0 "HELLO"

# 2.3.1 (condition 1, line 153): a token containing quoting characters is
# not subject to alias substitution.
tt TOK.10 "escaped word is not alias-substituted" \
"alias q='echo aliased'
\\q
echo rc=\$?" 0 "rc=127"

###############################################################################
t_section "special and positional parameters (2.5)"
###############################################################################

# 2.5.2 '#' (line 256): counts positional parameters, not \$0.
tt SPP.1 "\$# counts positionals only" \
'set a b c
echo $#
set --
echo $#' 0 "3" "0"

# 2.5.2 '?' (line 259): initialized to 0 when the shell starts.
tt SPP.2 "\$? is 0 at shell startup" \
'echo $?' 0 "0"

# 2.5.2 '?' (line 259): the subshell inherits the parent's \$?.
tt SPP.3 "subshell preserves \$? from the invoking environment" \
'sh -c "exit 3"
(echo in=$?)' 0 "in=3"

# 2.9.1.3 (line 954) + 2.5.2 note (line 261): an assignment-only command
# takes the exit status of its last command substitution.
tt SPP.4 "assignment-only command adopts the cmd-sub status" \
'x=$(sh -c "exit 7")
echo rc=$?' 0 "rc=7"

# 2.5.2 '-' (line 263): current option flags appear in \$-.
tt SPP.5 "\$- reflects set -f" \
'set -f
case $- in *f*) echo has_f ;; *) echo no_f ;; esac' 0 "has_f"

# 2.5.2 '$' (line 265): \$\$ expands to the same value in a subshell.
tt SPP.6 "\$\$ is unchanged inside a subshell" \
'p=$$
( q=$$ ; [ "$q" = "$p" ] && echo same || echo diff )' 0 "same"

# 2.5.2 '@' (line 252): "$@" embedded in a word — first field joins the
# prefix, last field joins the suffix.
t_begin SPP.7 "embedded \"\$@\": x\"\$@\"y joins prefix and suffix"
t_run 'set -- "a b" c
'"$TEST_EXEC"' x"$@"y'
expect_status 0
expect_err_contains "argv[1] => [xa b]"
expect_err_contains "argv[2] => [cy]"
t_end

# 2.5.2 '@' (line 252): with no positional parameters, "$@" generates ZERO
# fields (not one empty field).
t_begin SPP.8 "\"\$@\" with no positionals produces zero fields"
t_run 'set --
'"$TEST_EXEC"' "$@"'
expect_status 0
expect_err_lacks "argv[1]"
t_end

# 2.5.2 '*' (line 255): "$*" joins with the FIRST character of IFS.
tt SPP.9 "\"\$*\" joins with the first IFS character" \
'IFS=:-
set a b c
echo "$*"' 0 "a:b:c"

# 2.5.2 '*' (line 255): IFS null -> joined with no separation.
tt SPP.10 "\"\$*\" with empty IFS concatenates" \
'IFS=
set a b c
echo "$*"' 0 "abc"

# 2.5.2 '*' (line 255): IFS unset -> joined with a space.
tt SPP.11 "\"\$*\" with unset IFS uses a space" \
'unset IFS
set a b c
echo "$*"' 0 "a b c"

# 2.6.2 spec example (line 505): braces select the parameter name; $10 is
# $1 followed by '0'; unset ${10} expands empty.
tt SPP.12 "spec example: \${a}b-\$ab-\${1}0-\${10}-\$10" \
'a=1
set 2
echo ${a}b-$ab-${1}0-${10}-$10' 0 "1b--20--20"

###############################################################################
t_section "parameter expansion (2.6.2): unset-vs-null table, patterns"
###############################################################################

# 2.6.2 table: without colon, a null (set but empty) parameter substitutes
# NULL, not word.
tt PEX.1 "\${x-word} vs \${x:-word} on a null parameter" \
'x=
echo "[${x-w}]" "[${x:-w}]"' 0 "[] [w]"

# 2.6.2 table: '+' substitutes word when set-but-null; ':+' does not.
tt PEX.2 "\${x+word} vs \${x:+word} on a null parameter" \
'x=
echo "[${x+w}]" "[${x:+w}]"' 0 "[w] []"

# 2.6.2 table: '=' on a null parameter substitutes null and does NOT assign.
tt PEX.3 "\${x=word} on null: no assignment happens" \
'x=
echo "[${x=w}][$x]"' 0 "[][]"

# 2.6.2 table: '=' on an UNSET parameter assigns word.
tt PEX.4 "\${x=word} on unset assigns and substitutes" \
'echo "[${u_pex4=w}][$u_pex4]"' 0 "[w][w]"

# 2.6.2 table: '?' without colon on a null parameter substitutes null —
# no error, the shell continues.
tt PEX.5 "\${x?msg} on a null parameter is not an error" \
'x=
echo "[${x?msg}]"
echo rc=$?' 0 "[]" "rc=0"

# 2.6.2: ':?' with word omitted still errors; diagnostic names the parameter
# (spec example line 529-530); non-interactive shell exits (2.8.1).
t_begin PEX.6 "\${x:?} bare form errors and names the parameter"
t_run 'echo ${u_pex6:?}
echo after'
expect_status 125
expect_err_contains "u_pex6"
expect_out_lacks "after"
t_end

# 2.6.2 spec example (lines 509-518): finding the matching close brace.
tt PEX.7 "spec example: \${foo-bar}xyz} brace matching" \
'foo=asdf
echo ${foo-bar}xyz}
foo=
echo ${foo-bar}xyz}
unset foo
echo ${foo-bar}xyz}' 0 "asdfxyz}" "xyz}" "barxyz}"

# 2.6.2: word is only evaluated when it is used — no side effects otherwise.
t_begin PEX.8 "unused default word is not evaluated"
t_run 'x=set
echo ${x:-$(echo leaked > sidef)}'
expect_status 0
expect_lines "set"
expect_file_absent sidef
t_end

# 2.6.2: word undergoes full expansion when used.
tt PEX.9 "default word is itself expanded" \
'd=def
echo ${u_pex9:-$d} ${u_pex9b:-$(echo sub)}' 0 "def sub"

# 2.6.2 + 2.6.5: a quoted expansion with a default containing spaces is one
# field; unquoted it is split.
tt PEX.10 "field count of quoted vs unquoted default word" \
'set -- "${u_p10:-a b}"
echo $#
set -- ${u_p10:-a b}
echo $#' 0 "1" "2"

# 2.6.2 ${#parameter} (line 486): length 0 for null, decimal length otherwise.
tt PEX.11 "\${#x} of null and of a value" \
'x=
y=hello
echo ${#x} ${#y}' 0 "0 5"

# 2.6.2 (lines 490-497): smallest vs largest suffix removal.
tt PEX.12 "\${x%.*} smallest vs \${x%%.*} largest suffix" \
'x=a.b.c
echo ${x%.*} ${x%%.*}' 0 "a.b a"

# 2.6.2 spec examples (lines 547-554): smallest vs largest prefix removal.
tt PEX.13 "\${x#*/} smallest vs \${x##*/} largest prefix" \
'x=/one/two/three
echo [${x#*/}] [${x##*/}]' 0 "[one/two/three] [three]"

# 2.6.2 (line 491): the pattern word is expanded before matching.
tt PEX.14 "affix pattern comes from a variable expansion" \
'x=file.c
s=.c
echo ${x%$s}.o' 0 "file.o"

# 2.6.2 (lines 555-560): quoting inside the braces makes pattern characters
# literal; unquoted '*' after 'a' matches the SMALLEST prefix (just "a").
tt PEX.15 "quoted vs unquoted * in an affix pattern" \
'x="a*b"
echo "[${x#"a*"}][${x#a*}]"' 0 "[b][*b]"

# 2.6.2 (line 488): enclosing the whole expansion in dquotes does not quote
# the pattern characters — they stay active.
tt PEX.16 "pattern characters stay special inside outer dquotes" \
'x="a b.c"
echo "${x%.c}"' 0 "a b"

###############################################################################
t_section "command substitution (2.6.3)"
###############################################################################

# 2.6.3 (line 569): trailing newlines are stripped, embedded ones are kept.
tt CSB.1 "only trailing newlines are stripped" \
'x=$(printf "a\nb\n\n\n")
echo "[$x]"' 0 "[a" "b]"

# 2.6.3 (line 580): the result is NOT rescanned for expansions.
tt CSB.2 "cmd-sub output is not expanded again" \
'HOME=/tmp
x=$(echo '"'"'$HOME ~ `echo no`'"'"')
echo "$x"' 0 '$HOME ~ `echo no`'

# 2.6.3 + 2.6.5: unquoted results ARE field split; quoted results are not.
tt CSB.3 "cmd-sub result splits unquoted, not quoted" \
'set -- $(echo a b c)
echo $#
set -- "$(echo a b c)"
echo $#' 0 "3" "1"

# 2.6.3 (line 582): backquote nesting via backslash-escaped inner backquotes.
tt CSB.4 "nested backquotes with backslash escapes" \
'echo `echo \`echo deep\``' 0 "deep"

# 2.13: command substitution runs in a subshell — assignments do not leak.
tt CSB.5 "assignments inside cmd-sub stay in the subshell" \
'x=out
y=$(x=in; echo $x)
echo $x $y' 0 "out in"

# 2.6.3 (lines 585-587): "$( (cmds) )" — the spec's own workaround for the
# $(( ambiguity: space-separated subshell inside cmd-sub.
tt CSB.6 "spec form: \$( (commands) ) subshell inside cmd-sub" \
'echo $( (echo sub) )' 0 "sub"

# 2.9.1.1 step 4 (line 929): assignment values undergo cmd-sub but NO field
# splitting.
tt CSB.7 "no field splitting in an assignment value" \
'x=$(printf "a  b")
echo "[$x]"' 0 "[a  b]"

# 2.6.3 (line 575): any syntactically correct program can be the commands
# string, including loops spanning lines.
tt CSB.8 "multi-line program inside \$( )" \
'x=$(for i in 1 2 3
do
echo $i
done)
echo "$x"' 0 "1" "2" "3"

# 2.3 rule 5 (line 134): finding the terminating ) requires recursive
# tokenization — a quoted ) must not end the substitution.
tt CSB.9 "quoted close-paren inside \$( ) does not terminate it" \
'echo $(echo ")")' 0 ")"

# 2.2.3 (line 53): characters inside "$( )" within dquotes are not affected
# by the outer quotes — inner dquotes are their own context.
tt CSB.10 "double quotes nest independently inside \"\$( )\"" \
'echo "$(echo "a  b")"' 0 "a  b"

# 2.6.3: deep $() nesting (regression guard for the nested-recursion crash).
tt CSB.11 "four-level nested \$( )" \
'echo $(echo $(echo $(echo $(echo deep4))))' 0 "deep4"

###############################################################################
t_section "field splitting (2.6.5): the delimiter algorithm"
###############################################################################

# 2.6.5 (lines 657-660): a non-whitespace IFS delimiter between two others
# delimits an EMPTY field.
tt FSP.1 "a::b with IFS=: gives three fields, middle empty" \
'x=a::b
IFS=:
set -- $x
echo "$#" "[$1][$2][$3]"' 0 "3 [a][][b]"

# 2.6.5 (line 654): sequences of IFS whitespace collapse; leading/trailing
# whitespace delimits nothing.
tt FSP.2 "default IFS: runs of blanks collapse, edges stripped" \
'x="  a   b  "
set -- $x
echo $#' 0 "2"

# 2.6.5: whitespace around a non-ws delimiter is absorbed into it, but a
# second non-ws delimiter still yields an empty field.
tt FSP.3 "mixed IFS=' :' — ws-padded colons and an empty field" \
'x=" a : b : : c "
IFS=" :"
set -- $x
echo "$#" "[$1][$2][$3][$4]"' 0 "4 [a][b][][c]"

# 2.6.5 (line 623): IFS= (null) -> no splitting at all.
tt FSP.4 "IFS= disables field splitting" \
'IFS=
x="a b"
set -- $x
echo $#' 0 "1"

# 2.6.5 (line 623): with IFS null, a wholly empty expansion field is still
# removed.
tt FSP.5 "IFS= still removes a fully empty expansion field" \
'IFS=
e=
set -- $e
echo $#' 0 "0"

# 2.6.5 (line 633): unset IFS behaves as space-tab-newline.
tt FSP.6 "unset IFS falls back to default splitting" \
'unset IFS
x="a b"
set -- $x
echo $#' 0 "2"

# 2.6.5 (line 627): fields with no expansion results are never split.
tt FSP.7 "literal words are not subject to IFS" \
'IFS=x
set -- axb
echo $#' 0 "1"

# 2.6.5 (lines 635, 663): delimiters TERMINATE fields — a trailing non-ws
# delimiter does not create an empty last field.
tt FSP.8 "trailing delimiter creates no empty field" \
'x=a:b:
IFS=:
set -- $x
echo $#' 0 "2"

# 2.6.5 (line 660): a leading non-ws delimiter DOES delimit a leading empty
# field.
tt FSP.9 "leading delimiter creates a leading empty field" \
'x=:a
IFS=:
set -- $x
echo "$#" "[$1]"' 0 '2 []'

# 2.6.5 (line 648): literal bytes glue to expansion bytes; the split only
# happens inside expansion results.
tt FSP.10 "literal prefix joins the first expansion field" \
'x=" b"
set -- a$x
echo "$#" "[$1]"' 0 '2 [a]'

# 2.6.5 (line 639): an expansion of only IFS whitespace yields zero fields.
tt FSP.11 "whitespace-only expansion vanishes" \
'x="   "
set -- $x
echo $#' 0 "0"

###############################################################################
t_section "pathname expansion & pattern matching (2.6.6, 2.14)"
###############################################################################

# 2.14.1: [!...] matches any character not in the set.
tt PAT.1 "case bracket negation [!a-c]" \
'case d in [!a-c]) echo yes ;; *) echo no ;; esac' 0 "yes"

# 2.14.1: character classes inside brackets.
tt PAT.2 "case character class [[:digit:]]" \
'case 5 in [[:digit:]]) echo yes ;; *) echo no ;; esac
case x in [[:digit:]]) echo yes ;; *) echo no ;; esac' 0 "yes" "no"

# 2.14.3: a leading period must be matched explicitly — * skips dotfiles.
t_begin PAT.3 "* does not match a leading dot"
t_setup 'touch .hidden visible'
t_run 'echo *'
expect_status 0
expect_lines "visible"
t_end

# 2.14.3: <slash> must be matched explicitly — * does not cross directories.
t_begin PAT.4 "* does not match across /"
t_setup 'mkdir sub; touch sub/inner.txt'
t_run 'echo *inner*'
expect_status 0
expect_lines "*inner*"
t_end

# 2.6.6 + 2.14: a quoted pattern character is literal — only the file whose
# name really contains '*' matches.
t_begin PAT.5 "quoted * is literal, unquoted * globs"
t_setup 'touch "a*" ax'
t_run 'echo a"*"
echo a*'
expect_status 0
expect_lines 'a*' 'a* ax'
t_end

# 2.14.1: range expression in a filename pattern.
t_begin PAT.6 "bracket range [a-c] in pathname expansion"
t_setup 'touch fa fb fd'
t_run 'echo f[a-c]'
expect_status 0
expect_lines "fa fb"
t_end

# 2.2.1 + 2.6.6: a backslash-escaped * never globs, even with matches present.
t_begin PAT.7 "escaped \\* stays literal despite matching files"
t_setup 'touch x1 x2'
t_run 'echo \*'
expect_status 0
expect_lines "*"
t_end

###############################################################################
t_section "tilde expansion edges (2.6.1)"
###############################################################################

# 2.6.1: any quoting of the tilde (or of any part of the word up to the
# first /) suppresses tilde expansion.
tt TIL.1 "quoted tilde forms do not expand" \
'HOME=/tmp
echo "~" "~/x" ~"/x"' 0 '~ ~/x ~/x'

# 2.6.1: the tilde-prefix must start the word.
tt TIL.2 "tilde not at word start is literal" \
'HOME=/tmp
echo a~ x/~y' 0 "a~ x/~y"

# 2.9.1.1 step 4 (line 927/929): tilde expansion happens in assignment values.
tt TIL.3 "tilde expands in an assignment value" \
'HOME=/tmp
d=~/sub
echo $d' 0 "/tmp/sub"

###############################################################################
t_section "quote removal (2.6.7)"
###############################################################################

# 2.6.7 (line 670): quote characters are removed only when not themselves
# quoted.
tt QRM.1 "quoted quote characters survive quote removal" \
'echo "'"'"'a'"'"'" '"'"'"b"'"'"' \"c\"' 0 ''"'"'a'"'"' "b" "c"'

# 2.6.7: empty quotes inside a word disappear but keep the word joined.
tt QRM.2 "empty quotes vanish inside a word" \
'echo a""b'"''"'c' 0 "abc"

# 2.6.5/2.6.7: quoted null strings produce (and keep) empty fields — quote
# removal happens after splitting.
tt QRM.3 "quoted empty strings survive as empty fields" \
'set -- "" '"''"' ""'"''"'
echo $#' 0 "3"
