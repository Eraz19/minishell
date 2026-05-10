# TODO

## OPTIONS MODULE

- revert to `bool option_is_active(option)` bc we never need to check other shell options
- add logs

## PARAMS MODULE

- add `param_get()` API to allow to get `$0` (etc) as `$VAR`

## UNDEFINED BEHAVIOR TROLLING

- `-o` ou `+o` sans argument => `undefined_behaviour()`
- `options_load()` si (`-` && `--`) || (opérandes devant `-`) `undefined_behaviour()`

## BUILTINS

- ⚠️ `builtins`: ensure to follow [Utility Conventions](https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/V1_chap12.html#tag_12_02):
	- ⚠️ "Guideline 5: One or more options without option-arguments, **followed by at most one option that takes an option-argument**, should be accepted when grouped behind one '-' delimiter." => actually `-aio <option_argument>` is not parsed correctly ??
- ⚠️ `special builtins`: ensure to follow [2.15 Special Built-In Utilities](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_15)
	- Make the full list of special builtins
- ⚠️ `export`, `readonly` and `unset`: `--` is the end of options (`-` also ?)
- implement `set` builtin

## LIBFT

- Remove **wildcards** from `libft`'s `Makefile`
- ⚠️ `libft/vector` => Arithmétique sur `void *` n'est pas **standard C**, c'est une **extension GCC** => Ok norme et compilation 42 ?!

## OTHERS

- implement `expander` module
- comment all functions with list of possible `t_error` types they can return
- add `const` everywhere it's needed
- Implement `parser hooks`

## Documentation

- Préciser dans `lr_machine.md` que `ACTION` est complétée étape par étape avec un process et un payload différents pour :
	- `ERROR`: default
	- `SHIFT`: `action.payload` = `transition.to_lr_state_id`
	- `REDUCE`: `action.payload` = `lr_state[i].rule_state.rule_id` (only for `rules` with `pos` >= `rhs_len`)
	- `ACCEPT`: same as `REDUCE` but only if `rule.lhs` = `SYM_start` and for `SYM_EOF`

---

## TESTS

- `sh` parsing (`variables` + `options` + `operands` + `arguments`)
- `builtins` parsing
- `ft_getppid()` + `ft_getpid()` on **Linux**, **Mac_x86**, and **FreeBSD**

---

# OPTIMIZATIONS

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
