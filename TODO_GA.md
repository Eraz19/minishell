# WIP

- ⚠️ `trap` si `ctrl + D` après avoir déjà saisi une input
- `parser_can_next_token_be_a_cmd_name_or_word()`

---

# ALEXANDER

## BUGS
- `history`:
	- use `serialize()` and `deserialize()` and `deserialize_all()`
	- `history_load()`: Pas d'historique avec flèche du haut quand on vient de lancer le shell
	- L'historique apparaît quoted
	- Le `newline` apparait dans l'input (il ne devrait pas être stocké dans l'historique)
- `scanner_get_next_token()`:
	- Renvoie `TOKEN_NONE` au lieu de `TOKEN_EOF` ? (nécessaire pour reduce le programme + distinguer d'une error)
	- Ne renvoie pas d'erreur lorsque la cmd_string / le fichier d'input est déjà consommée !
	- Modifier la doc pour enlever l'obligation d'init le token côté caller
- `heredoc`:
	- Ne lit pas le here document après le `newline` malgré le trigger de `scanner_report_io_here()`
	- (actuellement je reçois le contenu et le delimiter dans les `token`)
	- Le flow correct doit être :
	1. Le `parser` trigger le `scanner` lorsqu'il reduce un `io_here` (via `scanner_report_io_here()`)
	2. Le `scanner` trigger le module `heredoc` qui créé un fichier temporaire et renvoie son path au `scanner` qui le renvoie au `parser`
	3. Lorsque le `scanner` renvoie le prochain `NEWLINE`: il set `should_parse_heredoc = true`.
	4. Au `scanner_get_next_token()` suivant: `should_parse_heredoc == true` donc `scanner` trigger `heredoc_read()`.
	5. le `heredoc` parse + stocke **les** heredoc bodys dans les fichiers temporaires correspondants.
	6. Le `scanner` remet `should_parse_heredoc = false`.
	7. Le `scanner` skip les tokens consommés par `heredoc`.
	8. Le `scanner` renvoie le prochain `token` au `parser` (`EOF` si c'est la fin de l'input).

## AJOUTS DONT J'AI BESOIN
- `token_contains_unquoted_equal()`:
	> If the TOKEN contains an unquoted (as determined while applying rule 4 from 2.3 Token Recognition) <equals-sign> character that is not part of an embedded parameter expansion, command substitution, or arithmetic expansion construct (as determined while applying rule 5 from 2.3 Token Recognition)
	- `token->assign_operand_offset` (-1 si inexistant)
- `scanner_reset()`:
	- Pour refresh après une syntax error (ou autre error...?)
	- `free()` les items mais pas les arrays pour éviter de re `malloc()` après
- `IO_NUMBER` et `IO_LOCATION`:
	- Décrits dans `Grammar Lexical Conventions` + `The rules for token recognition in 2.3 Token Recognition shall apply`
	- Donc clairement responsabilité du `lexer` selon moi
	- `IO_NUMBER` : Solely digits and the delimiter character is '<' or '>'
	- `IO_LOCATION` : At least three characters, begins with '{' and ends '}', and the delimiter character is '<' or '>'
	- Nécessaire pour distinguer `echo 2>out` de `echo 2 >out`

## UPDATE QUE J'AI FAIT DANS TON CODE
- `t_heredoc_mode`:
	- J'ai préfixé avec `HEREDOC_MODE_` (pls prefix all sinon je galère à trouver le nom des enums de tes modules)
- `t_token_type`:
	- J'ai préfixé avec `TOKEN_` et retirer les trailing `_`

## UPDATE QUE J'AI FAIT DANS MON CODE
- `t_error	builder_can_next_word_be_a_cmd_name(bool *dst)`:
	- La signature a changé pour return un `t_error`
	- Il faut donc désormais gérer la possible erreur `ERR_SHELL_NOT_FOUND` dans `is_token_alias_expandable()`
	- Ou j'exit le shell dans ce cas là ?
	- ⚠️ **TODO**: remove `shell_exit()` because it could let somme allocations inside pending functions => just return error
- `make debug`:
	- compile avec les flags de sanitizing + debug au lieu des flags d'opti

## DOUTES
- `error_print()`:
	- Vérifier que tous les call sont bien doublement `NULL` terminés

## VALIDÉ
- `parser` own les `token` (et leur `value`) reçus via `scanner_get_next_token()`
- `\n` à la fin de chaque input du `reader`
- `scanner_report_io_here()`:
	- J'envoie le delimiter brut (donc pas unquoted) pour que tu saches si le body doit être expandu on est d'accord ?
	- Tu le copies donc je free de mon côté ? (pas très opti donc on pourrait juste documenter l'ownership plutôt ?)

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
- `undefined_behaviour()`:
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
