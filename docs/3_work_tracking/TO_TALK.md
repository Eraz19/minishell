# TO TALK

- 🚨 en mode `SCAN_MODE_STRING` il ne faut **jamais** lire sur `stdin` même si `-i` est actif:
```bash
# Bash exit après avoir exécuté la string (nous on infinite loop):
bash --posix -ic "echo hello"
# Bash ne demande pas de continuation (nous oui et on reste bloqués dans la continuation, même CTRL+D n'exit pas):
bash --posix -ic "cat << EOF"
# Cette commande ne ressort jamais du builtin eval dans minishell:
eval echo hello
```
- 🤔 `cmd_sub_child_ast()`: Need a `SCAN_MODE_PARENT` for `shell_get_new_runner()` ?
- 🚨 `cmd sub` dans une `fonction`:
	- premier run va free l'`ast` / la `string` de la `cmd_sub` ??

# TO FIX

```bash
cat <<EOF
sub=$(echo yes)
EOF
```

```bash
# input
alias alias_1='FIRST VALUE'
alias alias_1='expanded `alias_1`'
# output
alias_1: command not found
=> lexing => expanded `alias_1`
=> parsing => ast
=> executor => expand(`alias_1`)
===> cmd_sub(alias_1)
===> lexing => expanded `alias_1`
expanded: command not found
$? = 127
```
Du coup :
1. `alias_stack` => list of aliases being currently expanded during `lexing` => reset after each `token`
2. `forbidden_aliases` => list of aliases expanded during `lexing` which are forbidden to `expand` inside `cmd subs` => reset after each `ast execution`

# UNSPECIFIED BEHAVIOUR TO TALK

```
- Caveat worth a deliberate decision: no_such_cmd || echo fallback also
  exits before the || is evaluated. Spec-permitted, but every mainstream
  shell (bash, dash, ksh, zsh) continues, so the common cmd || fallback
  idiom breaks. Per our convention, whichever way you keep it should be
  written down as the documented choice.
```

- should `break` stop the main loop in this kind of cases ?
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
```

# TO TEST

- `reader` / `scanner`:
	- must distingu `\` + `n` from real `\n` ?
```
A loop shall enclose a break or continue command if the loop lexically encloses the command. A loop lexically encloses a break or continue command if the command is:

Executing in the same execution environment (see 2.13 Shell Execution Environment) as the compound-list of the loop's do-group (see 2.10.2 Shell Grammar Rules), and
Contained in a compound-list associated with the loop (either in the compound-list of the loop's do-group or, if the loop is a while or until loop, in the compound-list following the while or until reserved word), and
Not in the body of a function whose function definition command (see 2.9.5 Function Definition Command) is contained in a compound-list associated with the loop.
```
