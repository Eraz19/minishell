# EXCALIDRAW

- J'ai broken le partage en sauvegardant un backup ?

# READER

- Tokenize one token at a time ?? (cf `could_be_a_command_name()` in excalidraw)
- Choix de la source de lecture :
	- **if** `is_option_valid(OPT_STDIN_INPUT) == true`		=> read from `STDIN_FILENO`
	- **else if** `is_option_valid(OPT_CMD_STRING) == true`	=> read from `shell->params.source` (string)
	- **else**												=> read from `shell->params.source` (fichier à open et read)
- **if** `readline() == NULL && is_option_active(OPT_INTERACTIVE) == true && is_option_active(OPT_IGNOREEOF) == false` => `exit()`:
	- You can store `is_option_active(OPT_INTERACTIVE) && is_option_active(OPT_IGNOREEOF)` as `scanner.should_exit_on_eof` when `scanner_load()` is executed because these options cannot be modified after `shell` invocation.

# GENERAL

- **USE** `t_error` because ULTRA CHIANT à implémenter à postériori (je l'ai fait pour `lr_machine` => INSUP'):
	- user `error_print()` (POSIX impose des logs de diagnostique d'erreur sur `stderr`)
- **USE** `t_shell *shell_get(void)` if you need main `shell` data struct
- **USE** `void	undefined_behaviour(void)` => Pour l'instant simple message de troll mais soon Xavier en ASCII art
- **USE** `void shell_exit(t_error error)` => Free all the `t_shell` struct and `exit` (this do **NOT** print any log!)

# TESTS

- Check `asm_stubs` on `linux` (works on `Docker` container)
- **20 sec** sur `mac` à cause de `-fsanitize` !! (**2 sec** sans ✌️ mais **4 min** avec `valgrind` 🙈)
- Utiliser `assert()` from `assert.h` pour tester direct grâce au compilo !
