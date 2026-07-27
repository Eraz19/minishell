# WIP

- ⚠️ `set`:
	- "If no options or arguments are specified, set shall write the names and values of all shell variables in the collation sequence of the current locale" => create `merge_sort()` (or quivalent) in `libft/sort/` and use it in `builtin_set`...
- 👉 `params`:
	- move `alias` table and print API in `params`
	- rename to `env`
	- create wrappers for `options` module API
	- create wrappers for `cmd_cache` module API
	- create wrappers for `fd` module API
	- create wrappers for `signal` module API
	- move `history` table to `params` ?
- 👉 précompiler les tables `LR`
- 👉 `ast`: use `t_ast_command` ast `root` instead of `t_ast_list` (`command` can contain a `list` anyway...)
- 👉 `options`:
	- `-u` (`expander`):
		- `parameter expansion` and `arithmetic expansion` must fail if *variable is not set*
		- **except** for `$@`, `$*` and *parameters* which handles *unset variables* (`${foo-word}`, `${foo=word}`, `${foo+word}`, ...)
	- `-v` (`reader`):
		- print input lines as read (on `stderr`)

---

# BEFORE SUBMIT

- regénérer **toute** la doc
- créer une doc en ligne comme pour `libft`

**FORK**

- delete `assert()` calls
- delete `logs` lib
- delete `printf()` calls
- delete `*_dump.c` files and `*_dump()` functions
- delete `debug.h` and `debug.c`
- delete all `DEBUG` sections
- check all `TODO` comments
