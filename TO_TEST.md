# LEXICALY ENGLOBING LOOPS

⚠️ POSIX unspecified
```bash
f() {
  echo "  in f: before break"
  break
  echo "  in f: after break"
}
for i in 1 2; do
  echo "loop i=$i: before f"
  f
  echo "loop i=$i: after f"
done
echo "after loop"

rm -f /tmp/do_break
foo() {
  for j in 1 2; do
    echo "break 2" >/tmp/do_break
    echo "  sourcing /tmp/do_break, j=$j"
    . /tmp/do_break
    echo "  after dot, j=$j"
  done
}

for i in 1 2; do
  echo "running foo, i=$i"
  foo
  echo "after foo, i=$i"
done
rm -f /tmp/do_break
```

# WIP CMD SUB

```bash
$(echo (inside) after)
```
```bash
before$(echo; (inside);
after)end
```

# SIGNALS

```bash
kill -QUIT $$
echo "still here after initial QUIT"
trap 'printf "\n[TRAP QUIT]\n"' QUIT
kill -QUIT $$
echo "still here after trapped QUIT"
trap - QUIT
kill -QUIT $$
echo "still here after trap - QUIT"

kill -INT $$
echo "still here after initial INT"
trap 'printf "\n[TRAP INT]\n"' INT
kill -INT $$
echo "still here after trapped INT"
trap - INT
kill -INT $$
echo "still here after trap - INT"

kill -TERM $$
echo "still here after initial TERM"
trap 'printf "\n[TRAP TERM]\n"' TERM
kill -TERM $$
echo "still here after trapped TERM"
trap - TERM
kill -TERM $$
echo "still here after trap - TERM"
```

# COMMAND SUBSTITUTION

```bash
$(true)
echo "should be 0 => $?"
$(false)$(true)
echo "should be 0 => $?"
$(true)$(false)$(true)
echo "should be 0 => $?"
$(false)
echo "should be 1 => $?"
$(true)$(false)
echo "should be 1 => $?"
$(false)$(true)$(false)
echo "should be 1 => $?"
```

```bash
VAR=$(true)
echo "should be 0 => $?"
VAR=$(false)$(true)
echo "should be 0 => $?"
VAR=$(true)$(false)$(true)
echo "should be 0 => $?"
VAR=$(false)
echo "should be 1 => $?"
VAR=$(true)$(false)
echo "should be 1 => $?"
VAR=$(false)$(true)$(false)
echo "should be 1 => $?"
```

```bash
VAR=value          => status 0
VAR=$(true)        => status 0
VAR=$(false)       => status 1
VAR=${bad syntax}  => ERR_POSIX_EXPANSION
```

```bash
$( echo hello )
echo before$(echo mid)after
echo before $(echo mid) after
$(( echo hello ); foo() { echo hello; }; echo bye )
```

```bash
alias test="echo before; echo $( echo inside ); echo after"
```

```bash
echo before; echo $( cat << EOF ); echo after
# write it manually:
inside
EOF
```

```bash
bash-5.2$ echo $(echo "hello
> boy"
> )
hello boy
# historique bash --posix:
echo $(echo "hello
boy"
)
```

# WIP

```bash
set -- a b c
case b in
	$@) echo VALID_1 ;;
	*) echo ERROR_1 ;;
esac
case b in
	"$@") echo VALID_2 ;;
	*) echo ERROR_2 ;;
esac
case b in
	$*) echo ERROR_3 ;;
	*) echo VALID_3 ;;
esac
case "a b c" in
	$*) echo VALID_4 ;;
	*) echo ERROR_4 ;;
esac
case b in
	"$*") echo ERROR_5 ;;
	*) echo VALID_5 ;;
esac
case $@ in
	a) echo ERROR a ;;
	b) echo ERROR b ;;
	c) echo ERROR c ;;
	abc) echo ERROR abc ;;
	"a b c") echo VALID_6 ;;
	*) echo ERROR no ;;
esac
case b in
	a|b|c) echo VALID_7 ;;
	*) echo ERROR_7 ;;
esac
```

case b in
	a) echo NOP ;;
	c) echo NOP ;;
esac

# TESTS TODO

🧪 Tester expansions qui produisent 0 / 1 / plusieurs fields:
- `redirections`
- `heredoc body`
- `assignments`
- `command name`

🧪 Tester les exit status des command substitutions dans:
- `assignments`
- `redirections`
- `words`
- `case` / `for` / `loop` components...
- `functions`
- ...

---

# LAST EXPANDED COMMAND SUBSTITUTION STATUS

```bash
A=$(true)
echo "should be 0 => $?"
#
A=$(false)
echo "should be 1 => $?"
#
cat << EOF
$(true)
EOF
echo "should be 0 => $?"
#
cat << EOF
$(false)
EOF
echo "should be 0 => $?"
#
<< EOF
$(true)
EOF
echo "should be 0 => $?"
#
<< EOF
$(false)
EOF
echo "should be 1 => $?"
```

---

# `$@` / `$*` UNSPECIFIED CASES IMPLEMENTATIONS

## POSIX 2.5.2 Special Parameters:
- `$@`					=> 1 field **per parameter**, join [first with before] + join [last with after]
- `$*` + unquoted		=> 1 field **per parameter**, join [first with before] + join [last with after]
- `$*` + quoted			=> **only** 1 field, joined with:
	- if `IFS` len > 0				=> `IFS[0]`
	- if `IFS` is *unset*			=> ` `
	- if `IFS` is *set but null*	=> *nothing*
- if no *field spillting*	=> UNSPECIFIED => **MINISHELL** => same behaviour as if field splitting was active

## MINISHELL
- `$@`:
	- `redirection`: always redirect to one file per field
	- `case`: 0 field => skip (match = false)
	- `case`: n fields => match sur chaque field

## YASH (normal / -o posixlycorrect)
- `$@`:
	- `redirection`: always merge fields in `filename`
	- `case`: always merge patterns

## BASH --posix
- `$@`:
	- `redirection`: always merge fields in `filename`
	- `case`: unquoted => merge fields
	- `case`: quoted => only keep first field

## BASH
- `$@`:
	- `redirection`: error "redirection ambigue"
	- `case`: unquoted => merge fields
	- `case`: quoted => only keep first field

## ZSH
- `$@`:
	- `redirection`: always redirect to one file per field
	- `case`: always merge patterns

## REDIRECTION UNSPECIFIED TESTS

```bash
# prints to "a" + "b" + "c"
set -- 'a' 'b' 'c'
echo hello > $@
# prints to "a" + "b" + "c"
set -- 'a' 'b' 'c'
echo hello > "$@"
# prints to "a" + "b" + "c"
set -- 'a' 'b' 'c'
echo hello > $*
# prints to "azbzc"
IFS="zab"
set -- 'a' 'b' 'c'
echo hello > "$*"
# prints to "a b c"
unset IFS
set -- 'a' 'b' 'c'
echo hello > "$*"
# prints to "abc"
IFS=
set -- 'a' 'b' 'c'
echo hello > "$*"
```

## CASE UNSPECIFIED TESTS

```bash
# TEST 1 => bash merges all fields
clear
set -- 'a' 'b' 'c'
for subject in 'abc' 'a b c' 'a' 'b' 'c'
do
  case $subject in
    $@) printf 'MATCH <%s>\n' "$subject" ;;
    *) printf 'NO  <%s>\n' "$subject" ;;
  esac
done
# TEST 2 => bash keeps only first field
clear
set -- 'a' 'b' 'c'
for subject in 'abc' 'a b c' 'b' 'a' 'c'
do
  case $subject in
    "$@") printf 'MATCH <%s>\n' "$subject" ;;
    *) printf 'NO  <%s>\n' "$subject" ;;
  esac
done
# TEST 2 => no match
clear
set --
for subject in 'abc' 'a b c' 'b' 'a' 'c'
do
  case $subject in
    "$@") printf 'MATCH <%s>\n' "$subject" ;;
    *) printf 'NO  <%s>\n' "$subject" ;;
  esac
done
```

---

# MATCH PATTERN TESTS

```bash
cat *	# should match all files in current dir
cat "*"	# should only match "*" file
```

## IF

```bash
# OK
echo "--------------------"
false
echo "before => $?"
if false || echo "in condition => $?"; then
	echo "inside => $?"
fi
echo "after => $?"
echo "--------------------"
```

```bash
# OK
echo "--------------------"
false
echo "before => $?"
if false; then
	echo NOP
fi
echo "after => $?"
echo "--------------------"
```

## FOR

```bash
# OK
echo "--------------------"
i=old
for i in a b c; do
  :
done
echo "should be 'c' => '$i'"
echo "--------------------"
```

```bash
# OK
echo "--------------------"
a=one
for x in $a $a; do
  a=two
  echo "shoud be 'one' => '$x'"
done
echo "--------------------"
```

```bash
# [RUNNER] error should have been requalified : 124 (variable assignment error)
echo "--------------------"
echo "should throw assignment error"
readonly i
for i in a b c; do
  echo "$i"
done
echo "--------------------"
```

---

# SUBSHELL

```bash
# ./minishell: builtin_break: not implemented
echo "--------------------"
while true; do
	(
		while true; do
			break 2
		done
		echo after
	)
	echo parent
done
echo "--------------------"
```

---

# CASE

```bash
# OK
echo "--------------------"
case x in
 x) ;;
esac
echo "\$? should be '0' => '$?'"
echo "--------------------"
```

# CASE : PATTERN MATCHING

```bash
echo "--------------------"
# OK (expected = abc*def)
v='abc*def'
echo "${v#'*'}"

# OK
p='*'
case abc in
  "$p") echo "ERROR: * should be litteral when p='*' and pattern is \"$p\"" ;;
	$p) echo "valid 1";;
esac

# OK
case '*' in
  \*) echo "valid 2" ;;
esac

# OK
case '?' in
  \?) echo "valid 3" ;;
esac

# OK
case '[' in
  \[) echo "valid 4" ;;
esac

# OK
case '[' in
  [) echo "valid 5" ;;
esac

# OK
case "" in
  "") echo "valid 6" ;;
esac
echo "--------------------"
```

---

# EXPANSIONS

```bash
# should assign ONLY if pattern is unset or NULL:
VAR=${pattern:=foo}
# Should NEVER assign during expansion:
VAR=${pattern}
VAR=${pattern:-foo}
VAR=${pattern+foo}
VAR=${pattern#foo}
VAR=${pattern%foo}
```
