# READ LINE BY LINE

```bash
printf 'read x\nfoo\necho $x' | ./minishell
```

# KEEP IN MIND

- 💡 Les erreurs dépendent de l'opération qui a échouée:
	- Donc une `ERR_EXPANSION` ne peut jamais être requalifiée en `ERR_REDIRECTION`, `ERR_ASSIGNMENT`, etc.

---

# TODO

- `reader`:
	- Read line by line even in *non-interactive* mode
```bash
printf 'read x\nfoo' | ./minishell
# piped into a script that reads — the read builtin gets the next line, proving no read-ahead.
```
- `builder`:
	- Split `builder/parser/qualifiers/build_table.c` into multiple files
- `signal`:
	- remove useless `#ifdef` cf [signal.h](https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/signal.h.html)
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
	- replace all `ERR_INDEX_OUT_OF_BOND`, etc by `error_print()` + `ERR_INTERNAL`
	- use `print_unspecified_behaviour()`
	- `const` partout
	- `inline` partout
	- `assert` partout
	- `out_` prefix de tous les args qui sont **générés** par une fonction (cf `C#` syntax)
	- `ref_` prefix de tous les args qui sont **potentiellement modifiés** par une fonction (cf `C#` syntax)
	- use `posix_write()` instead of `write()`
	- use `posix_open()` instead of `open()`
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
- 😂 `redirection`:
	- when `filename` expands to more than one field: redirect to one file per field
