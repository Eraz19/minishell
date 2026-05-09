# TODO

- `-o` ou `+o` sans argument => UB => **LA TETE A XAV** !!
- `options_load()` si (`-` && `--`) || (opérandes devant `-`) => UB => **LA TETE A XAV**
- ⚠️ `export`, `readonly` and `unset`: `--` is the end of options (`-` also ?)
- ⚠️ `export`, `readonly` and `unset`: Check additional [2.15 **Special Built-In Utilities**] rules to follow
- implement `set` builtin
- `load` module shall handle variables `expansion` ?!
- comment all functions with list of possible `t_error` types they can return
- add `const` everywhere it's needed
- Préciser dans `lr_machine.md` que `ACTION` est complétée étape par étape avec un process et un payload différents pour :
	- `ERROR`: default
	- `SHIFT`: `action.payload` = `transition.to_lr_state_id`
	- `REDUCE`: `action.payload` = `lr_state[i].rule_state.rule_id` (only for `rules` with `pos` >= `rhs_len`)
	- `ACCEPT`: same as `REDUCE` but only if `rule.lhs` = `SYM_start` and for `SYM_EOF`
- Implement `parser hooks`
- Remove **wildcards** from `libft`'s `Makefile`
- ⚠️ `libft/vector` => Arithmétique sur `void *` n'est pas **standard C**, c'est une **extension GCC** => Ok norme et compilation 42 ?!
...

## READER

- Catch `ctrl + D` on empty line and `exit` if `option_is_active(OPT_IGNOREEOF)` == `false`

---

# TO CHECK

- `ft_getppid()` on **Linux**, **Mac_x86**, and **FreeBSD**
- Options:
```bash
bash --posix +i -c 'printf "%s\n" "$-"'
bash --posix -i -c 'printf "%s\n" "$-"'
bash --posix -i +i -c 'printf "%s\n" "$-"'
bash --posix +i -i -c 'printf "%s\n" "$-"'
# Expected output
hBc
himBHc
hBc
himBHc
```
- Special parameters :
```bash
bash --posix -c 'printf "<%s>\n" "$0"'
bash --posix -c 'printf "<%s>\n" "$0"' my0
printf '%s\n' 'printf "<%s>\n" "$0"' | bash --posix
./test.sh   # avec à l’intérieur: printf '<%s>\n' "$0"
```

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
		- **MacOS** workaround: asm stub
		- **FreeBSD** workaround: read [...]
		- **OpenBSD** workaround: ***NONE***
