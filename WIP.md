# WIP (MAKEFILE)

- `$(LR_TAB_GEN_FILES):` suit les `.c`, mais pas encore les `.h` du `generator` et de la `grammar`.

# WIP (LR MACHINE)

- `generator`:
	- compute and store in `lr_generator`:
		- `ACTION_COL_COUNT`
		- `ACTION_COUNT`
		- `GOTO_COL_COUNT`
		- `GOTO_COUNT`
	- only store `t_qualifier_id` in `lr_generator`

# WIP

- **ALEX**:
	- `gitignore` add `2_generator/lr_generator` and `3_lr_tables/2_generated/*`
- ⚠️ `exit`:
	- quid `EINTR` lors du `write()`
- ⚠️ `scanner` + `SCAN_MODE_FILE` from `sh` vs `dot` / `eval` / `env`...:
	- Pas le même système de fallback ? (`dot` cherche lui-même alors que `sh` délègue le search)
	- qui doit `path search` ?
- ⚠️ `set`:
	- "If no options or arguments are specified, set shall write the names and values of all shell variables in the collation sequence of the current locale" => create `merge_sort()` (or quivalent) in `libft/sort/` and use it in `builtin_set`...
- ⚠️ `alias`:
	- "the alias definition shall not affect the parent process of the current shell nor any utility environment invoked by the shell" => `alias` should not be expanded while `scanner` is used inside a `utility` (`env`, `dot`, `eval`...?)
- 👉 `params`:
	- remove wrappers ? 
	- move `history` table to `params` ?
- 👉 précompiler les tables `LR`
- 👉 `ast`: use `t_ast_command` ast `root` instead of `t_ast_list` (`command` can contain a `list` anyway...)
- 👉 `options`:
	- `-u` (`expander`):
		- `parameter expansion` and `arithmetic expansion` must fail if *variable is not set*
		- **except** for `$@`, `$*` and *parameters* which handles *unset variables* (`${foo-word}`, `${foo=word}`, `${foo+word}`, ...)
	- `-v` (`reader`):
		- print input lines as read (on `stderr`)
- 👉 **all** *sub-modules*:
	- *print* / *qualify* errors if needed
	- use `assert()` instead of `t_error` when possible

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
