# WIP (COMMAND SUBSTITUTION PARSING)

```bash
# segfault
$(( echo hello ); foo() { echo hello; }; echo bye )
# abort
$( echo hello )
```

- ⚠️ store `ast` into `token`:
	- 

```bash
alias test="echo before; echo $( echo inside ); echo after"
```

⚠️ `t_error	scanner_set_cmd_sub_input(const t_string *cmd_string);`

// TODO: keep cmd sub generated `AST`
```bash
echo before; echo $( cat << EOF ); echo after
# write it manually:
inside
EOF
```

- ⚠️ only handle `$(...)` form because `backquote` form only needs to find next `backquote`.
- ⚠️ `scanner` must handle empty `$()` itself.
- ⚠️ Continuations read inside the `cmd sub scanner` must also be added to the `main scanner`.

```bash
bash-5.2$ echo $(echo "hello
> boy"
> )
hello boy
# historique bash --posix:
echo $(echo "hello
boy"
)
```

# WIP (OTHER)

- **all**:
	- ⚠️ retry on `EINTR` => shell only compute signals in *safe points*
	- handle all `options` properly
- `runner-executor`:
	- ⚠️ `exec` specific flow
	- ⚠️ `command` specific flow
- `posix_read_all()` and replace all `string_read*()` calls

---

# KEEP IN MIND

- 💡 Les erreurs dépendent de l'opération qui a échouée:
	- Donc une `ERR_EXPANSION` ne peut jamais être requalifiée en `ERR_REDIRECTION`, `ERR_ASSIGNMENT`, etc.

---

# TODO

- `shell`:
	- process `ENV`:
		- See `ENVIRONMENT VARIABLES` -> `ENV` section in [sh](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/sh.html).
		- `If the expanded value of ENV is not an absolute pathname, the results are unspecified` ([sh](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/sh.html) -> `ENVIRONMENT VARIABLES` -> `ENV`)
	- `shell_reset_unignored_traps()`: waiting for `trap` / `signal` implementation
- `undefined_behaviour()`:
	- print la tête à Xavier
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
	- ⚠️ `libft/vector` => remplacer arithmétique `void *` par `char *`
	- ⚠️ `libft/vector` => Returns `false` on `libc` (`malloc`) failure **OR** `new_cap > SIZE_MAX / 2` !! (but `minishell` assumes `ERR_LIBC`!) => add `t_error` return type with `ERR_SIZE_MAX_REACHED` / `ERR_LIBC` value
- `ft_pidtostring()` et `ft_ltostring()` pour éviter double alloc
- **ALL REPO**:
	- use `print_unspecified_behaviour()`
	- Move `t_tokens` from `runner` to `token` module ?
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

# TODO IF ON A QUE ÇA A FOUTRE

- `params`:
	- `variables`:
		- Switch `t_vector`s to `t_hashmap`
- `redirection`:
	- when `filename` expands to more than one field: redirect to one file per field

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
