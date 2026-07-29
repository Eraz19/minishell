# WIP (LR MACHINE)

- `qualifiers` required data:
	- `const char *token_value` -> `token->value.data`
	- `ssize_t assignment_offset` -> `token->assignment_offset`

- Previous `hooks`:
	- `RULE_COMPLETE_COMMAND_1` + `RULE_COMPLETE_COMMAND_2` => `hook_store_cst`
	- `RULE_FNAME_1` => `hook_fname`
	- `RULE_IO_HERE_1` + `RULE_IO_HERE_2` => `hook_3`

# WIP

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
