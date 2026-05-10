# READER

- Choix de la source de lecture :
	- **if** `is_option_valid(OPT_STDIN_INPUT) == true`		=> read from `STDIN_FILENO`
	- **else if** `is_option_valid(OPT_CMD_STRING) == true`	=> read from `shell->params.source` (string)
	- **else**												=> read from `shell->params.source` (fichier à open et read)
- **if** `readline() == NULL && is_option_active(OPT_INTERACTIVE) == true && is_option_active(OPT_IGNOREEOF) == false` => `exit()`:
	- You can store `is_option_active(OPT_INTERACTIVE) && is_option_active(OPT_IGNOREEOF)` as `scanner.should_exit_on_eof` when `scanner_load()` is executed because these options cannot be modified after `shell` invocation.

# GENERAL

- **USE** `void	undefined_behaviour(void)` => Pour l'instant simple message de troll mais soon Xavier en ASCII art
- **USE** `void shell_exit(t_error error)` => Free le `shell` et `exit` (ne print aucun log!)

# TESTS

- Check `asm_stubs` on `Linux`
