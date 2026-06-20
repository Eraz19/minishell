# ALEXANDER

- J'ai commenté mes modifs de fix avec `// TO_CHECK` pour que tu puisses vérifier :
	- J'ai fix le problème dans `history_load_size_env()` : il faut clear state->err quand tu handle une error
- `Makefile` : pense à le modifier quand tu changes les path des fichiers stp (idem pour `libft`)
- `.vscode/settings.json` : idem
- Attention au naming des fonctions :
	- `path_name_expansion()` => `expand_path_name()`
	- `substitutions()` => `substitute()`
	- ...
- Attention aux fonctions prototypées mais pas implémentées :
	- `shell_get_alias()`, `shell_get_heredoc()`, `substitutions()`, `path_name_expansion()`...
	- Pour des trucs aussi simples => les implémenter direct
	- J'ai peur que tu oublies plein de trucs si tu fais pas dans l'ordre
- `token_type` :
	- devraient être préfixés (`NONE` par exemple tout le monde voudrait s'en servir...)
	- pourquoi certains suffixés avec `_` (`EOF_`, `NEWLINE_`)
- `error_print()` calls sont bien double NULLés ?
- ⚠️ `echo 2>out` => `2` est un `IO_NUMBER` alors que `echo 2 >out` => `2` est un argument `WORD` :
	- => `scanner` doit conserver l'info d'adjacence ! Donc soit il classe `2` directement comme `IO_NUMBER` soit `token` contient un `bool followed_by_redirection_operator`
- ⚠️ `parser` va copier les token pour les conserver dans l'`ast` :
	- Quid deepcopy / ownership / lifetime des deep content
	- Quid ownership du token content => transféré au `parser` donc c'est lui qui call `token_free()` ?
	- Comme je stocke les token dans le parser, je rappelle `token_init()` sur un token qui a déjà été populated par `scanner_next_token()` mais pas free derrière car `vector_push()` ne deep copy pas, c'est ok de ton côté ?

# PARSER



# TODO

- ⚠️ Vérifier que les `buff_*()`, `vector_*()` etc de `libft` ne free pas en cas d'échec (sinon `errno` undefined):
	- 🚨 `buff_dup_n()` le fait !!
	- 🚨 `buff/format/append()` le fait !!
	- 🚨 `vector_dup()` le fait !!
	- 🚨 `vector_init()`, `vector_grow()` et `vector_dup()`, `vector_pop()`, `vector_insert()`, `vector_remove()` et `vector_merge()` retournent false dans d'autres cas qu'une erreur système !
- ⚠️ `undefined_behaviour()` should not `shell_exit()` ! (for example a `builtin` UB should only generate a builtin error, then the shell should behave as POSIX says for builtin errors!) => it should return `ERR_UNDEFINED_BEHAVIOUR`:
	- Fixed but **NEED TO CHECK ALL EXISTING USAGES of `undefined_behaviour()`**

## BUILTINS

| ERROR                               | DESCRIPTION                                                   | SOURCE                                                       | TEST CMD                                                        | CONFIRMED |
|-------------------------------------|---------------------------------------------------------------|--------------------------------------------------------------|-----------------------------------------------------------------|-----------|
| `ERR_UTILITY_OPT_INVALID`           | invalid / unrecognized `option`                               | 1.4 Utility Description Defaults / OPTIONS                  | `bash --posix -c 'export -z; echo NOT_REACHED'`                 | YES       |
| `ERR_UTILITY_OPT_MISSING_ARG`       | missing required `option_argument`                            | 1.4 Utility Description Defaults / OPTIONS                  | `bash --posix -c 'fc -e; echo REACHED'`                         | YES*      |
| `ERR_UTILITY_USAGE_INVALID`         | invalid usage of options, arguments, or environment variables | 1.4 Utility Description Defaults / CONSEQUENCES OF ERRORS   | `bash --posix -c 'shift x; echo AFTER'`                         | YES       |
| `ERR_UTILITY_EXTENDED_SYNTAX`       | invalid usage of complex syntax from EXTENDED DESCRIPTION     | 1.4 Utility Description Defaults / CONSEQUENCES OF ERRORS   | `bash --posix -c "eval 'if'; echo NOT_REACHED"`                 | YES       |
| `ERR_UTILITY_RESOURCE_EXHAUSTED`    | resource exhaustion                                           | 1.4 Utility Description Defaults / CONSEQUENCES OF ERRORS   | hard to make deterministic / environment-dependent              | YES       |
| `ERR_UTILITY_FILE_IO`               | difficulty accessing, creating, reading, or writing files     | 1.4 Utility Description Defaults / CONSEQUENCES OF ERRORS   | `bash --posix -c '. /no/such/file; echo NOT_REACHED'`           | YES       |
| `ERR_UTILITY_PRIVILEGE`             | difficulty associated with process privileges                 | 1.4 Utility Description Defaults / CONSEQUENCES OF ERRORS   | environment-dependent, e.g. privileged-only operation           | YES       |
| `ERR_UTILITY_OPERAND_ACTION_FAILED` | requested action cannot be performed on an operand            | 1.4 Utility Description Defaults / CONSEQUENCES OF ERRORS   | `bash --posix -c '. /no/such/file; echo NOT_REACHED'`           | YES       |
| `ERR_UTILITY_OPT_ACTION_FAILED`     | requested action characterized by option/option-argument failed | 1.4 Utility Description Defaults / CONSEQUENCES OF ERRORS | utility-specific; needs the target utility page                 | YES       |
| `ERR_UTILITY_UNRECOVERABLE`         | unrecoverable error condition                                 | 1.4 Utility Description Defaults / CONSEQUENCES OF ERRORS   | hard to make deterministic / implementation-dependent           | YES       |

- `shell` shall expose `void shell_set_utility_error(t_utility_error error)`
- errors:
	- ✅ `ERR_UTILITY_OPT_INVALID`: option non reconnue (`bash --posix -c 'export -z; echo NOT_REACHED'`);
	- ❔ `ERR_UTILITY_OPT_MISSING_ARG`: option qui requiert un argument mais ne le reçoit pas ;

- Remove `t_shell *shell` from args: same signature as classic `main()`
- Check all doc
	- [XBD 12. Utility Conventions](https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/V1_chap12.html)
	- [1.4 Utility Description Defaults](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap01.html#tag_18_04)
	- [1.6 Built-In Utilities](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap01.html#tag_18_06)
	- [1.7 Intrinsic Utilities](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap01.html#tag_18_07)
	- [2.15 Special Built-In Utilities](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_15)
- ⚠️ `builtins`: ensure to follow [Utility Conventions](https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/V1_chap12.html#tag_12_02):
	- ⚠️ "Guideline 5: One or more options without option-arguments, **followed by at most one option that takes an option-argument**, should be accepted when grouped behind one '-' delimiter." => actually `-aio <option_argument>` is not parsed correctly ??
- ⚠️ `special builtins`: ensure to follow [2.15 Special Built-In Utilities](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_15)
	- Make the full list of special builtins
- ⚠️ `export`, `readonly` and `unset`: `--` is the end of options (`-` also ?)
- implement `set` builtin (to edit `positionals`)
- implement `shift` builtin (to edit `positionals`)

## SHELL PROGRAM

- Return correct `exit status` (see [sh](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/sh.html) `EXIT STATUS` section).
- Shall use [exit](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#exit) builtin to exit itself ??
- Implement correct [2.8.1 Consequences of Shell Errors](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_08_01).

## ENV PROCESSING

- See `ENVIRONMENT VARIABLES` -> `ENV` section in [sh](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/sh.html).
- `If the expanded value of ENV is not an absolute pathname, the results are unspecified` ([sh](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/sh.html) -> `ENVIRONMENT VARIABLES` -> `ENV`)

## LR_MACHINE MODULE

- Implement `parser hooks`
- add `const` everywhere it's missing
- Make doc less verbose

## LIBFT

- Remove **wildcards** from `libft`'s `Makefile`
- ⚠️ `libft/vector` => Arithmétique sur `void *` n'est pas **standard C**, c'est une **extension GCC** => Ok norme et compilation 42 ?!
- ⚠️ `libft/vector` => Returns `false` on `libc` (`malloc`) failure **OR** `new_cap > SIZE_MAX / 2` !! (but `minishell` assumes `ERR_LIBC`!) => add `t_error` return type with `ERR_SIZE_MAX_REACHED` / `ERR_LIBC` value

---

# LATER

## MATHS AND ARITHMETIC EXPANSIONS

- [2.6.4 Arithmetic Expansion](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_06_04)
- [1.1.2.1 Arithmetic Precision and Operations](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap01.html#tag_18_01_02_01)
- [1.1.2.2 Mathematical Functions](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap01.html#tag_18_01_02_02)

## MAILPATH

- `The default message is unspecified` ([sh](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/sh.html) -> `ENVIRONMENT VARIABLES` -> `MAILPATH`)
- `The default messages for the various MAIL -related messages are unspecified` ([sh](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/sh.html) -> `RATIONALE`)

## vi Line Editing Insert Mode

- `If end-of-file is entered other than at the beginning of the line, the results are unspecified` ([sh](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/sh.html) -> `EXTENDED DESCRIPTION` -> `vi Line Editing Insert Mode`)

---

# TESTS

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

## lr_machine.md

- Préciser que `ACTION` est complétée étape par étape avec un process et un payload différents pour :
	- `ERROR`: default
	- `SHIFT`: `action.payload` = `transition.to_lr_state_id`
	- `REDUCE`: `action.payload` = `lr_state[i].rule_state.rule_id` (only for `rules` with `pos` >= `rhs_len`)
	- `ACCEPT`: same as `REDUCE` but only if `rule.lhs` = `SYM_start` and for `SYM_EOF`

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

# TO REMOVE BEFORE SUBMIT

- delete `logs` lib and all calls to it
- delete `*_dump.c` files and `*_dump()` functions
- delete `debug.h` and `debug.c`
