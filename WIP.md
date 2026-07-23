🚨 Ne pas demander de continuation si `OPT_INTERACTIVE` (`-i`) n'est pas activée !

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

# TO FIX

- `builtin_set`:
	- shall throw `ERR_INVALID_USAGE` when `-o` / `+o` is used without `option` but `first_operand_index` < `argc`
- `builtin_env`:
	- implement `utility` execution:
		- *resolve* cmd_name => *external* vs *builtin*
		- *execute* => `fork` + `execve`

# REQUIRED

- ⚠️ `builtins`:
	- ⚠️ `dot`
	- ⚠️ `kill`

# OTHERS

- when shell options are invalid => requalify error in `ERR_INVALID_USAGE`
- rename `params` to `env`
- `shell`:
	- process `ENV` at startup:
		- See `ENVIRONMENT VARIABLES` -> `ENV` section in [sh](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/sh.html).
		- `If the expanded value of ENV is not an absolute pathname, the results are unspecified` ([sh](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/sh.html) -> `ENVIRONMENT VARIABLES` -> `ENV`)
- `options`:
	- handle all options properly
- `ast`:
	- use `t_ast_command` ast `root` instead of `t_ast_list` (`command` can contain a `list` anyway...)
- `runner-executor`:
	- `exec` specific flow
	- `command` specific flow
