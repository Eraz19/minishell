# WIP

- handle `n` fields expansions :
	- `redirection`: always redirect to one file per field
	- `case`: 0 field => skip (match = false)
	- `case`: n fields => match sur chaque field
- ⚠️ `exit_status`:
	- remove some `exit_status = -1` to avoid losing expansion / redirection status ?
- 💡 Les erreurs dépendent de l'opération qui a échouée:
	- Donc une `ERR_EXPANSION` ne peut jamais être requalifiée en `ERR_REDIRECTION`, `ERR_ASSIGNMENT`, etc.
- `builder`:
	- handle `command substitution search`
- `runner-executor`:
	- ⚠️ `exec` specific flow
	- ⚠️ `command` specific flow
	- `execve fallback`: don't free `lr_machine` to avoid recomputing tables
- `posix_read_all()`

---

# TODO

- `walker`:
	- `walk_case_expand()` : implement expansion incorrect len handling
- `error`:
	- `error_sys()`: requalify as `ERR_INTERNAL` if `errno == 0`
- `shell`:
	- process `ENV`:
		- See `ENVIRONMENT VARIABLES` -> `ENV` section in [sh](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/sh.html).
		- `If the expanded value of ENV is not an absolute pathname, the results are unspecified` ([sh](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/sh.html) -> `ENVIRONMENT VARIABLES` -> `ENV`)
	- `shell_reset_unignored_traps()`: waiting for `trap` / `signal` implementation
- `builder`:
	- Split `builder/parser/qualifiers/build_table.c` into multiple files
- `libft`:
	- update `buff_get_index()` calls to handle new `ssize_t` return type + new form `buff_get_index_c()`
	- update `buff_append()`, `buff_prepend()`, `buff_insert()` et `buff_dup()` callers
	- ⚠️ Vérifier que les `buff_*()`, `vector_*()` etc de `libft` ne free pas en cas d'échec (sinon `errno` undefined):
		- 🚨 `buff_dup_n()` le fait !!
		- 🚨 `buff/format/append()` le fait !!
		- 🚨 `vector_dup()` le fait !!
		- 🚨 `vector_init()`, `vector_grow()` et `vector_dup()`, `vector_pop()`, `vector_insert()`, `vector_remove()` et `vector_merge()` retournent false dans d'autres cas qu'une erreur système !
	- Remove **wildcards** from `libft`'s `Makefile`
	- ⚠️ `libft/vector` => Arithmétique sur `void *` n'est pas **standard C**, c'est une **extension GCC** => Ok norme et compilation 42 ?!
	- ⚠️ `libft/vector` => Returns `false` on `libc` (`malloc`) failure **OR** `new_cap > SIZE_MAX / 2` !! (but `minishell` assumes `ERR_LIBC`!) => add `t_error` return type with `ERR_SIZE_MAX_REACHED` / `ERR_LIBC` value
- `ft_pidtostring()` et `ft_ltostring()` pour éviter double alloc
- `undefined_behaviour()`:
	- print la tête à Xavier
- `params`:
	- `variables`:
		- Switch `t_vector`s to `t_hashmap` ?
- `all`:
	- `clear()` API instead of `free()` for shell reset, subshell, etc (avoid rebuilding lr tables)
- **ALL REPO**:
	- use `print_unspecified_behaviour()`
	- Move `t_tokens` from `runner` to `token` module ?
	- Use `t_tokens` instead of `t_vector` of `t_token *` (`ast`...)
	- handle `options` properly (`-n` flag, ...)
	- `const` partout
	- `inline` partout
	- `assert` partout
	- `out_` prefix de tous les args qui sont **générés** par une fonction (cf `C#` syntax)
	- `ref_` prefix de tous les args qui sont **potentiellement modifiés** par une fonction (cf `C#` syntax)
	- use `posix_write()` instead of `write()`
	- use `posiw_open()` instead of `open()`
	- `errors`:
		- rename `ERR_LIBC` -> `ERR_SYS`
		- Ensure no `free()` / `libc` is done before `error_sys()`
		- Ensure all `error_print()` calls are **double** `NULL` terminated
		- handler `erros` at module-gates to only return meaning-full errors to callers
	- ⚠️ search for `open()` / `read()` / `write()` / ... remaining usages
	- `error_print()` return value must **NOT** be ignored (for `err.printed` update)
	- add doc + `make doc` / `github action`
	- **include** prototype header
	- ⚠️ don't call `undefined_behaviour()` when it's `unspecified`

---

# TO FIX

# `$@` / `$*` UNSPECIFIED CASES IMPLEMENTATIONS

**POSIX 2.5.2 Special Parameters**:
- `$@`					=> 1 field **per parameter**, join [first with before] + join [last with after]
- `$*` + unquoted		=> 1 field **per parameter**, join [first with before] + join [last with after]
- `$*` + quoted			=> **only** 1 field, joined with:
	- if `IFS` len > 0				=> `IFS[0]`
	- if `IFS` is *unset*			=> ` `
	- if `IFS` is *set but null*	=> *nothing*
- if no *field spillting*	=> UNSPECIFIED => **MINISHELL** => same behaviour as if field splitting was active

**MINISHELL**:
- `$@`:
	- `redirection`: always redirect to one file per field
	- `case`: 0 field => skip (match = false)
	- `case`: n fields => match sur chaque field

**YASH (normal / -o posixlycorrect)**
- `$@`:
	- `redirection`: always merge fields in `filename`
	- `case`: always merge patterns

**BASH --posix**:
- `$@`:
	- `redirection`: always merge fields in `filename`
	- `case`: unquoted => merge fields
	- `case`: quoted => only keep first field

**BASH**:
- `$@`:
	- `redirection`: error "redirection ambigue"
	- `case`: unquoted => merge fields
	- `case`: quoted => only keep first field

**ZSH**:
- `$@`:
	- `redirection`: always redirect to one file per field
	- `case`: always merge patterns

---

## MATHS AND ARITHMETIC EXPANSIONS

- [2.6.4 Arithmetic Expansion](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_06_04)
- [1.1.2.1 Arithmetic Precision and Operations](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap01.html#tag_18_01_02_01)
- [1.1.2.2 Mathematical Functions](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap01.html#tag_18_01_02_02)

---

# BEFORE SUBMIT

- delete `assert()` calls
- delete `logs` lib
- delete `printf()` calls
- delete `*_dump.c` files and `*_dump()` functions
- delete `debug.h` and `debug.c`
- delete all `DEBUG` sections
- check all `TODO` comments
