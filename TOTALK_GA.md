# 11/05/26

## READER

- `t_error scanner_load(t_read_mode mode, const char *source)` :
	- **if** `is_option_valid(OPT_STDIN_INPUT) == true`		=> read from `STDIN_FILENO`
	- **else if** `is_option_valid(OPT_CMD_STRING) == true`	=> read from `shell->params.source` (string)
	- **else**												=> read from `shell->params.source` (fichier à open et read)

## GENERAL

- [**YES**] **USE** `t_error` because ULTRA CHIANT à implémenter à postériori (je l'ai fait pour `lr_machine` => INSUP'):
	- user `error_print()` (POSIX impose des logs de diagnostique d'erreur sur `stderr`)
- [**YES**] **USE** `t_shell *shell_get(void)` if you need main `shell` data struct
- [**YES**] **USE** `void undefined_behaviour(void)` => Pour l'instant simple message de troll mais soon Xavier en ASCII art
- [**YES**] **USE** `void shell_exit(t_error error)` => Free all the `t_shell` struct and `exit` (this do **NOT** print any log!)

## TESTS

- [**YES**] Check `asm_stubs` on `linux` (works on `Docker` container)
- [**YES**] **20 sec** sur `mac` à cause de `-fsanitize` !! (**2 sec** sans ✌️ mais **4 min** avec `valgrind` 🙈)
- [**YES**] Utiliser `assert()` from `assert.h` pour tester direct grâce au compilo !
