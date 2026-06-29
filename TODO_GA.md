# WIP

- ⚠️ Complete les `TODO (GA)`

- 🚧 **ALL REPO**:
	- 🚧 `const` partout
	- 🚧 `inline` partout
	- 🚧 `assert` partout
	- 🚧 **include** prototype header

- **TODO**: convert `posix_helpers` (coûterait trop cher avec ChatGPT)
- `5_exec_env` => Utilise `params_get()` donc à update après avoir update le module `params`
- `ft_pidtostring()` et `ft_ltostring()` pour éviter double alloc
- `specials->zero` convert to `t_string` to avoid multiple `str_len()` when accessing it ?

- 🚧 `runner`:
	- 🚧 unlink heredoc path after use
- 🚧 `posix_read()`:
	- 🚧 implement it using `string_read_*()` API ? (⚠️ remove auto retry ?!)
- 🚧 `assignment_split()`:
	- 🚧 refactor
- 🚧 `libft`:
	- 🚧 update `buff_get_index()` calls to handle new `ssize_t` return type + new form `buff_get_index_c()`
	- 🚧 update `buff_append()`, `buff_prepend()`, `buff_insert()` et `buff_dup()` callers
- 🚧 `params`:
	- 🚧 `options`:
		- 🚧 `options_get()`: `char *` => `t_buff`
	- 🚧 `specials`:
		- 🚧 `source`: `char *` => `t_buff`
		- 🚧 `zero`: `char *` => `t_buff`
	- 🚧 `positionals`:
		- 🚧 `params`: `char **` => `t_vector(t_buff)`
	- 🚧 `variables`:
		- 🚧 `var.name`: `char *` => `t_buff`
		- 🚧 `var.value`: `char *` => `t_buff`
		- 🚧 `var.has_value`: add it to make difference before set without value and set with empty value
	- 🚧 `params`:
		- 🚧 update all API from `char *` to `t_buff` (and from `char **` to `t_vector(t_buff)`)
- 🚧 `parser`:
	- 🚧 use `token->assignment_offset` (-1 if missing) in `ASSIGNMENT_WORD` qualifier
	- 🚧 call `scanner_reset()` (+ `parser_reset()` ?) on syntax errors
	- 🚧 add `t_token *closing_par` argument:
		- 🚧 if `closing_par == NULL` => normal mode
		- 🚧 else:
			- 🚧 input contains `(`
			- 🚧 on `subshell` reduction => shallow copy last token in `closing_par` + `return`
- 🚧 `subshell`:
	- 🚧 create module (must be compatible with `command_substitution` search)
- 🚧 `redirector`:
	- 🚧 finish module (need `t_token` in `AST`)
- 🚧 Split `builder/parser/qualifiers/build_table.c` into multiple files
- 🚧 Include prototypes `.h` in all `.c`
- 🚧 Check all `error_sys()`:
	- 🚧 must be called before any `free()` / `libc` call
- 🚧 **ALL**: add doc

## RESOURCES

- [2.9.1.1 Order of Processing](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_09_01_01)
	- [2.15 Special Built-In Utilities](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_15)
	- [2.7 Redirection](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_07)
- [2.9.1.2 Variable Assignments](2.9.1.2 Variable Assignments)
- [2.9.1.4 Command Search and Execution](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_09_01_04)
- [2.9.5 Function Definition Command](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_09_05)
- [1.7 Intrinsic Utilities](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap01.html#tag_18_07)
- [8. Environment Variables](https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/V1_chap08.html#tag_08)
- [2.9.1.6 Non-built-in Utility Execution](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_09_01_06)
- [2.9.1.6 Non-built-in Utility Execution](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_09_01_06)
- [2.9.2 Pipelines](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_09_02)

1. Expand `words` (see 2.9.1.1:2)
2. Redirect (see 2.7)
3. Expand `assignments`
> ⚠️ Steps `2` and `3` **may** be reversed if :
>	- no command name results from step 1
>	- the command name matches the name of a special built-in utility (see 2.15)

## IMPLEMENTATION ORDER

1. Module `redirection` :
	- Créer une redirection
	- Push une redirection sur la stack
	- Restaurer une redirection
	- Pop une redirection de la stack
2. Module `function_registry` :
	- `t_function` = `char *name` + `t_ast_command body` + `t_ast_redir_list redirs`
	- Save une fonction
	- Retrieve une fonction
	- Delete une fonction
3. Module `command_search`
	- Check if command name contains `\`
	- Check if the command name matches the name of a `special built-in utility`
	- Check if the command name matches the name of an `utility` for which results are `unspecified`
	- Ask `function_registry` to know if the command name matches a `function` name (+ path search)
	- Check if the command name matches the name of an `intrinsic utility`
	- Search for command using `PATH` variable content :
		> ⚠️ `builtins` must be associated with a `directory` to know when to recognize them during `PATH` exploration
	- Remember `PATH` value to **NOT** search again while `PATH` is not `re-assigned` and the remembered command location is still valid
2. Module `executor`
	- Chercher une commande (function, builtin, path resolution) => Quelle section POSIX ?
3. Vérifier que ce système minimal fonctionne
3. Implémenter le module qui créé un subshell et y exécute une commande
4. Implémenter le module qui gère les pipeline:
	- `pipefail option` behaviour to check
5. TODO...

---

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

# ALEXANDER

## QUESTION
- ⚠️ signature de `positionals_get()` modifiée pour renvoyer un pointeur read-only
- ⚠️ `params_get()` use `t_string`, `params_get_from_const()` use `const char *`
- ⚠️ J'ai vu plein de `error_sys()` après des `free*()` dans ton code
- use `string_append_format()` / `buff_append_format()` pour pas avoir à `ft_itoa()` + `free()`
- use `t_string` everywhere instead of `t_buff` (NUL-terminé donc évite plein d'allocs / manips manuelles, je peux refacto si besoin)
- `scanner_reset()`:
	- ⚠️ free un pointeur qui n'a pas été malloc (reproduce with syntax error)
	- J'ai remove son argument car c'est le `runner` qui l'appelle donc il n'est pas sensé connaître sa struct
- `ft_getpwnam`:
	- Besoin forcément d'un `static buff` ou on peut convertir pour utiliser `t_string` et `posix_read()` ?
- `scanner_report_io_here()`:
	- ✅ j'ai refacto pour utiliser `t_string *path` et `t_token *delim`
	- ✅ du coup j'ai aussi refacto `heredoc_add_to_queue()`, `heredoc_create_file()` et `heredoc_build_path()` (opti + fix)
- `scanner_heredoc_read()`:
	- print bien une erreur dans le cas du delim manquant en non interactif ? (impossible pour le `parser` de savoir quel heredoc était en train d'être lu à ce moment là)

## TODO
- use `posix_write()` instead of `write()`
- use `posiw_open()` instead of `open()`
- `heredoc`:
	- `tmp/minishell/*` au lieu de `tmp/*` pour pouvoir supprimer facilement tous nos fichiers temporaires sans avoir à connaître leurs noms ? => miss `mkdir()` function
- `errors`:
	- Vérifier qu'aucun call à `free()` / `libc` n'est fait avant un `error_sys()`
	- Vérifier que tous les call à `error_print()` sont bien doublement `NULL` terminés

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
- delete `assert()` calls
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
- `heredoc`:
	- as `mkdir()` and `mktmp()` is forbidden, we can't properly create a tmp file, so we just iterate over an 0-INT_MAX file_name suffix to find an available filename to create directly in `tmp/`
	- as `lseek()` is forbidden, we can't keep the `fd` open, so we `open()`/`close()` the tmp file several times to re-roll it

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
