# TODO

- add `const` everywhere it's needed
- `var_get()` should be private (returns a pointer to the real var)
- `var_get_value()` should be public (returns a malloc'd copy of var->value)
- Préciser dans `lr_machine.md` que `ACTION` est complétée étape par étape avec un process et un payload différents pour :
	- `ERROR`: default
	- `SHIFT`: `action.payload` = `transition.to_lr_state_id`
	- `REDUCE`: `action.payload` = `lr_state[i].rule_state.rule_id` (only for `rules` with `pos` >= `rhs_len`)
	- `ACCEPT`: same as `REDUCE` but only if `rule.lhs` = `SYM_start` and for `SYM_EOF`
- Implement `parser hooks`
- Remove **wildcards** from `libft`'s `Makefile`
- ⚠️ `libft/vector` => Arithmétique sur `void *` n'est pas **standard C**, c'est une **extension GCC** => Ok norme et compilation 42 ?!
...

---

# TO CHECK

- `ft_getppid()` on **Linux**, **Mac_x86**, and **FreeBSD**

---

# TO OPTI

## LR_MACHINE

- Switch from `LR(1)` to `LRAR(1)` or `mini LR(1)` ?
- Switch `action` and `goto` tables from **2D** to **1D** arrays / **hash tables** ?
- Merge `to_lr_state_id` and `rule_id` in `t_action` into a unique `payload` field (one is used by `SHIFT` actions, the other one by `REDUCE` action so they are never useful at the same time)

## VARIABLES

- Switch from `t_vector` to **hash table** ?

---

# TO DOCUMENT

## What I learned

- Read, understand and implement an **industrial standard** (`POSIX`)
- Think, find and implement a suitable **architecture** for a large purpose program:
	- **deep modules** strategy: `scanner` (aka `lexer`) + `builder` (aka `parser`) + `runner` (aka `executor`)
	- **memory safety** flow: init, run, free
- Work as a **team** with `git` and `discord` (2 members):
	- **git branches**
	- **git issues**
	- **github actions** (`CI/CD`)
	- **discord hooks**

---

# ⚠️ Unreachable POSIX requirements

POSIX requirements which current implementation can't reproduce because of 42 allowed functions limitations.

- `variables`:
	- `PPID` variable: "Set by the shell to the decimal value of its parent process ID during initialization of the shell"
		- **forbiden** functions: `getppid()`
		- **Linux** workaround: read `PPid` from `/proc/self/stat` or `/proc/self/status`
		- **MacOS** workaround: NONE
