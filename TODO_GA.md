# TODO

## LR_MACHINE MODULE

- Implement `parser hooks`
- add `const` everywhere it's missing
- Make doc less verbose

## SHELL MODULE

- Do all the `// TODO ⚠️` points

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
- ⚠️ `libft/vector` => Returns `false` on `libc` (`malloc`) failure **OR** `new_cap > SIZE_MAX / 2` !! (but `minishell` assumes `ERR_LIBC`!)

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
- `ft_getppid()` + `ft_getpid()` on **Linux**, **Mac_x86**, and **freeBSD**

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

## POSIX limitations due to 42 functions whitelist

- Workarounds and/or asm stubs have been done to emulate the following functions which are not allowed by the official 42 subject:
	- `getpid()` -> `ft_getpid()`: get current process id for `$$` initialization:
		- `macOS` / ARM: asm stub
		- `macOS` / x86: asm stub
		- `linux`/ all: workaround via `/proc/self/status`
		- `freeBSD` / all (all archs): workaround via `/proc/curproc/status` / `/proc/self/status`
	- `getppid()` -> `ft_getppid()`: get parent process id for `$PPID` initialization
		- `macOS` / ARM: asm stub
		- `macOS` / x86: asm stub
		- `linux`/ all: workaround via `/proc/self/status`
		- `freeBSD` / all (all archs): workaround via `/proc/curproc/status` / `/proc/self/status`
	- `fcntl()` -> `ioctl()`: set `stdin` to blocking mode for `stdin` management
		- all OS and archs: via `ioctl()` (non-POSIX function) instead of `fcntl()`
- ⚠️ as `OpenBSD` sends `SIGABRT` when `syscalls` are sent from unauthorized memory addresses, this `shell` is not fully POSIX compliant on this Operating System. A next version of this program may use all the real `libc` functions to enable full POSIX compliance.

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
