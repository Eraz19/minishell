# TODO

- `execve()`
	- `ENOENT` / `ENOTDIR` => `ERR_CMD_NOT_FOUND`
	- `EACCES` / `ELOOP` / `ENAMETOOLONG` => `ERR_CMD_NOT_EXECUTABLE`
	- `ENOEXEC` => ⚠️ lancer un shell avec ce pathname comme script (sauf si heuristic de rejet)
	- Autres => `ERR_LIBC`
- ⚠️ `string_plit_on_*()`: add `bool skip_empty_entries` => update callers
- ⚠️ `function_set()` + `function_unset()`
- Move `t_tokens` from `runner` to `token` module ?
- Use `t_tokens` instead of `t_vector` of `t_token *`
- `hashmap`: signatures updated => update callers
- update expander calls to new `TILDE` flags
- handle `options`:
	- `-n` flag (`OPT_NOEXEC`)
	- ...

# REDIRECTOR

1. `cmd_expander` avec une API du style `t_error cmd_expand(t_vector *words, bool *out_has_cmd_name, char ***out_argv)`
2. `cmd_resolver` avec une API du style `t_error cmd_resolve(const char *cmd_name, t_cmd_type *out_cmd_type)` avec t_cmd_type qui est une enum CMD_NONE / CMD_SPECIAL_BUILTIN / CMD_FUNCTION / CMD_OTHER
3. `cmd_assignator` avec une API du style `t_error cmd_assign(t_vector *assignments)` ici j'ai du mal à saisir ce que signifie "environnement temporaire/exporté" : temporaire je comprends "revert assignment after command execution" mais "exporté" je vois pas du tout à quoi ça correspond ? Ça veut dire qu'on ajoute les assignments à envp / environ mais on n'effectue pas les assignments dans les params du shell ??
4. `redirector` : déjà implémenté, l'orchestrator aura juste à le call le moment venu (on pourra si besoin le renommer `cmd_redirector` pour uniformiser le naming)
5. `cmd_invoker` à faire en dernier mais ça j'ai pas trop de question dessus pour l'instant à priori
6. `cmd_orchestrator` qui appelle tous les sous-modules des points précédents dans le bon ordre

# ALEXANDER

- `EXP_DSQUOTE`:
	- process first, then apply all other expansions from the beginning of `word`
- `utils`:
	- `scan_set_mode()` à déplacer dans un module `input_mode`
	- Utiliser `free_char_ptr_void()` au lieu de `free` comme callback pour les `vector_fre()` contenant des `char *`
- replace `string_read_all()` by `posix_read()` and make `posix_read()` use `string_read_all()` (don't retry auto !)
- Pour debug sous `Linux` => `launch.json` => `"MIMode": "gdb"`

# WIP

- 🚧 `runner`:
	- 🚧 unlink heredoc path after use
- 🚧 `parser`:
	- 🚧 implement `runner_find_cmd_sub_closing()` (see `TODO.c`)
		- 🚧 add `t_token *closing_par` argument:
			- 🚧 if `closing_par == NULL` => normal mode
			- 🚧 else:
				- 🚧 input contains `(`
				- 🚧 on `subshell` reduction => shallow copy last token in `closing_par` + `return`
- 🚧 `subshell`:
	- 🚧 create module (must be compatible with `command_substitution` search)
- 🚧 `builder`:
	- 🚧 Split `builder/parser/qualifiers/build_table.c` into multiple files
- 🚧 `posix_read()`:
	- 🚧 implement it using `string_read_*()` API ? (⚠️ remove auto retry on EINTR in libft !)
- 🚧 `libft`:
	- 🚧 update `buff_get_index()` calls to handle new `ssize_t` return type + new form `buff_get_index_c()`
	- 🚧 update `buff_append()`, `buff_prepend()`, `buff_insert()` et `buff_dup()` callers
- `ft_pidtostring()` et `ft_ltostring()` pour éviter double alloc
- 🚧 **ALL REPO**:
	- 🚧 `const` partout
	- 🚧 `inline` partout
	- 🚧 `assert` partout
	- 🚧 `out_` prefix de tous les args qui sont **générés** par une fonction (cf `C#` syntax)
	- 🚧 `ref_` prefix de tous les args qui sont **potentiellement modifiés** par une fonction (cf `C#` syntax)
	- 🚧 `error_sys()` must be called before any `free()` / `libc` call
	- ⚠️ search for `open()` / `read()` / `write()` / ... remaining usages
	- 🚧 `error_print()` return value must **NOT** be ignored (for `err.printed` update)
	- 🚧 add doc
	- 🚧 **include** prototype header
	- ⚠️ don't call `undefined_behaviour()` when it's `unspecified`
	- rename `ERR_LIBC` -> `ERR_SYS`

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

## TODO
- use `posix_write()` instead of `write()`
- use `posiw_open()` instead of `open()`
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
- `redirections`:
	- as `fcntl()` is forbidden, we check whether the rhs fd of `>&` / `<&` is open, but we do not check whether it is open respectively for writing or reading. This is still POSIX-compliant because POSIX says that a redirection error "may" result in that case.
	- as `fcntl()` is forbidden, we cannot allocate redirection backup fds atomically with `F_DUPFD`. We use `fstat()` + `dup2()` instead. This is considered safe enough for `minishell` because it is single-threaded and its signal handlers do not open file descriptors.
	- as `sysconf()` / `getrlimit()` are forbidden, we cannot query the actual file descriptor limit of the host process. POSIX only requires shell redirections to support user file descriptors 0 through 9. By default, `minishell` uses 0..128 as its user fd range and reserves 129..256 for internal redirection backups. If the backup range is exhausted or unsupported by the host system, the redirection fails with a redirection error. A MAX_COMPAT build option can restrict the layout to 0..9 for user fds and 10..19 for backup fds, which is a more conservative POSIX-minimum layout but still does not guarantee that backup fds are available.
- `expander`:
	- as `fn_match()` is forbidden, regex matching is not implemented.

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
