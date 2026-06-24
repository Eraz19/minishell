# WIP

1. walk_ast() call walk_list()
2. walk_list() call walk_and_or()
3. walk_and_or() call walk_pipeline()
4. walk_pipeline() call walk_command()
5. walk_command() call redirect_push() (sauf simple_command et function_def)
6. walk_command() peut call soit :
	- walk_if() call walk_list() (back to step 2)
	- walk_for() call walk_list() (back to step 2)
	- walk_loop() call walk_list() (back to step 2)
	- walk_case() call walk_list() (back to step 2)
	- walk_list() (back to step 2)
	- walk_func() save juste la fonction
	- execute() qui execute la simple command
7. walk_command() call redirect_pop()

---

- `shell_exit_on_veof()` => `bool shell_should_exit()`
- `option_is_active()` peut fail (ERR_SHELL_NOT_FOUND):
	- Changer signature 😫
- Vérifier partout que les `error_sys()` sont bien créées avant de free quoi que ce soit (ou tout autre call `libc`)

# EXAM

print tous les board pour lesquels 2 dames peuvent pas se manger (selon règle des échecs)

---

# ALEXANDER

## BUGS
- `heredoc`:
	- `scanner_report_io_here()`
		- N'envoie pas de path au premier appel
		- Envoie plusieurs fois le même path
		- Devrait renvoyer un `t_buff` au lieu d'un `char *`
	- `scanner_heredoc_read()`
		- Ne lit pas les here documents

## AJOUTS DONT J'AI BESOIN
- `token->assign_operand_offset` (-1 si inexistant):
	> If the TOKEN contains an unquoted (as determined while applying rule 4 from 2.3 Token Recognition) <equals-sign> character that is not part of an embedded parameter expansion, command substitution, or arithmetic expansion construct (as determined while applying rule 5 from 2.3 Token Recognition)
- `scanner_reset()`:
	- Pour refresh après une syntax error (ou autre error...?)
	- `free()` les items mais pas les arrays pour éviter de re `malloc()` après

## DOUTES
- `error_print()`:
	- Vérifier que tous les call sont bien doublement `NULL` terminés

---

# TODO (HIGH PRIORIY)

- `void shell_utility_error(t_shell_error shell_err, t_error err)`:
	- `shell_err` = type d'erreur haut niveau (`SHELL_ERR_BUILTIN`, ...)
	- `err` = type d'erreur bas niveau (`ERR_LIBC`, ...)
	- `exit()` si les conditions sont remplies
- ⚠️ Vérifier que les `buff_*()`, `vector_*()` etc de `libft` ne free pas en cas d'échec (sinon `errno` undefined):
	- 🚨 `buff_dup_n()` le fait !!
	- 🚨 `buff/format/append()` le fait !!
	- 🚨 `vector_dup()` le fait !!
	- 🚨 `vector_init()`, `vector_grow()` et `vector_dup()`, `vector_pop()`, `vector_insert()`, `vector_remove()` et `vector_merge()` retournent false dans d'autres cas qu'une erreur système !
- `undefined_behaviour()`:
	- N'exit plus le shell => Vérifier que tous les callers prennent ça en compte
	- print la tête à Xavier

---

# TODO (LOW PRIORIY)

## VARIABLES

- `params`: Switch `t_vector`s to **hash table** ?

## SHELL PROGRAM

- Return correct `exit status` (see [sh](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/sh.html) `EXIT STATUS` section).
- Shall use [exit](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#exit) builtin to exit itself ??
- Implement correct [2.8.1 Consequences of Shell Errors](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_08_01).

## ENV PROCESSING

- See `ENVIRONMENT VARIABLES` -> `ENV` section in [sh](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/sh.html).
- `If the expanded value of ENV is not an absolute pathname, the results are unspecified` ([sh](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/sh.html) -> `ENVIRONMENT VARIABLES` -> `ENV`)

## LIBFT

- Remove **wildcards** from `libft`'s `Makefile`
- ⚠️ `libft/vector` => Arithmétique sur `void *` n'est pas **standard C**, c'est une **extension GCC** => Ok norme et compilation 42 ?!
- ⚠️ `libft/vector` => Returns `false` on `libc` (`malloc`) failure **OR** `new_cap > SIZE_MAX / 2` !! (but `minishell` assumes `ERR_LIBC`!) => add `t_error` return type with `ERR_SIZE_MAX_REACHED` / `ERR_LIBC` value

## MATHS AND ARITHMETIC EXPANSIONS

- [2.6.4 Arithmetic Expansion](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_06_04)
- [1.1.2.1 Arithmetic Precision and Operations](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap01.html#tag_18_01_02_01)
- [1.1.2.2 Mathematical Functions](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap01.html#tag_18_01_02_02)

## BUILTINS CRITICAL ERROR vs CLASSIC ERROR

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

---

# UNSPECIFIED BEHAVIUOURS NOT IMPLEMENTED YET

## MAILPATH

- `The default message is unspecified` ([sh](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/sh.html) -> `ENVIRONMENT VARIABLES` -> `MAILPATH`)
- `The default messages for the various MAIL -related messages are unspecified` ([sh](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/sh.html) -> `RATIONALE`)

## vi Line Editing Insert Mode

- `If end-of-file is entered other than at the beginning of the line, the results are unspecified` ([sh](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/sh.html) -> `EXTENDED DESCRIPTION` -> `vi Line Editing Insert Mode`)

---

# TODO (BEFORE SUBMIT)

- add `const` everywhere it's missing
- Make doc
- delete `logs` lib
- delete `printf()` calls
- delete `*_dump.c` files and `*_dump()` functions
- delete `debug.h` and `debug.c`
- delete all `DEBUG` sections
- check all `TODO` comments

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
