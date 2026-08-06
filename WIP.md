# NOW

- Norme:
	- ⚠️ **ALEX**:
		- `builtins/pwd.c`
		- `0_utils/ft_getpwnam.c`
		- `types.h` remove (move content to correct headers / `utils.h`)
	- keep comments for `42_SH`:
		- `error.h`
		- `0_utils/ft_getopt.h`
		- `1_shell/4_shell_exec_env.c`
		- `4_runner/1_walker/walk_pipeline/5_walk_pipe_finalize.c`
		- `4_runner/1_walker/walk_pipeline/walk_pipeline.c`
		- `builtins/return.c`
		- `env/1_options/options.h`
	- keep macros for `42_SH`:
		- `shell.h`
		- `0_posix_helpers/posix_open/guard.c`
		- `asm_stubs`: macros can NOT contain `(...)` + must only be in *global scope* (=> AI)
	- keep logs for `42_SH`:
		- `1_shell/5_shell_run.c`
		- `1_shell/7_shell_get_new.c`
		- `3_builder/1_parser/2_parser_read.c`
		- `3_builder/1_parser/6_parser_store_cst.c`
		- `3_builder/1_parser/0_helpers/parser_process_reduce_hooks.c`
		- `3_builder/1_parser/0_helpers/parser_read_heredoc.c`
		- `4_runner/1_walker/1_walk_simple_cmd.c`
		- `4_runner/1_walker/9_walk_function.c`
		- `cmd/4_cmd_execute/*`
		- `cmd/cmd_finalize.c`
		- `cmd_sub/*`
		- `env/1_options/2_helpers.c`
		- `env/1_options/5_load.c`
		- `env/2_specials/2_load.c`
		- `4_runner/2_runner_handle_errors.c`
		- `error/error.c`
	- keep placeholders for `42_sh`:
		- `TODO.c`
- Error qualifying
- Funkcheck en -s +i only

# WIP (ALIAS)

> "With both the backquoted and $(commands) forms, the commands string shall be tokenized and parsed. It is unspecified whether the commands string is parsed and executed incrementally as a program (as for a shell script), or is parsed as a single compound_list that is executed after the string has been completely parsed.”

`2.6.3 Command Substitution`:
> “If the commands string is parsed as a single compound_list, before any commands are executed, alias and unalias commands in commands have no effect during parsing.”

Changements incrémentaux d'alias dans une cmd_sub sont *unspecified* donc
```bash
echo $(alias abc='echo ok'; abc)
# POSIX autorise [abc: cmd not found] ou [ok] (bash produit cmd not found)
alias abc='echo ok' && echo $(abc)
# POSIX autorise [abc: cmd not found] ou [ok] (bash produit cmd not found)
echo `alias abc='echo ok'; abc`
# POSIX autorise [abc: cmd not found] ou [ok] (bash produit "ok")
alias abc='echo ok' && echo `abc`
# POSIX autorise [abc: cmd not found] ou [ok] (bash produit "ok")
```
peut **ou pas** expandre `x` en `echo ok`

# WIP (LR MACHINE)

- `generator`:
	- compute and store in `lr_generator`:
		- `ACTION_COL_COUNT`
		- `ACTION_COUNT`
		- `GOTO_COL_COUNT`
		- `GOTO_COUNT`
	- only store `t_qualifier_id` in `lr_generator`
	- Compress tables (`SLR(1)` / `LALR(1)` / `SLALR(1)` ??)

# WIP

- **ALEX**:
	- `libft` updated
	- `gitignore` add `2_generator/lr_generator` and `3_lr_tables/2_generated/*`
- ⚠️ `exit`:
	- quid `EINTR` lors du `write()`
- ⚠️ `scanner` + `SCAN_MODE_FILE` from `sh` vs `dot` / `eval` / `env`...:
	- Pas le même système de fallback ? (`dot` cherche lui-même alors que `sh` délègue le search)
	- qui doit `path search` ?
- ⚠️ `set`:
	- "If no options or arguments are specified, set shall write the names and values of all shell variables in the collation sequence of the current locale" => create `merge_sort()` in `libft/sort/` and use it in `builtin_set`...
- ⚠️ `alias`:
	- "the alias definition shall not affect the parent process of the current shell nor any utility environment invoked by the shell" => `alias` should not be expanded while `scanner` is used inside a `utility` (`env`, `dot`, `eval`...?)
- 👉 `params`:
	- remove wrappers ? 
	- move `history` table to `params` ?
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
