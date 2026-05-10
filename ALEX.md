# READER

- Choix de la source de lecture :
	- `shell` = `shell_get()`:
		- SHOULD not fail (but if `NULL` => you should return `ERR_SHELL_NOT_FOUND`)
		- Or `is_option_valid(<OPTION>)` get the `shell` itself ? (seems we NEVER need to check parent `shell` options...)
		- Or all functions take directly the entire `shell` struct ?? (don't like that...)
	- `options` = `shell->params.options`
	- `is_option_valid(options, OPT_TODO) == true`	=> `STDIN_FILENO`
	- `is_option_valid(options, OPT_TODO) == true`	=> shell->params.source (string)
	- `is_option_valid(options, OPT_TODO) == true`	=> shell->params.source (fichier à open et read)
- `exit()` **if** `readline() == NULL` **&&** `is_option_active() == true` **&&** `is_option_active() == false`

## 

- Check `asm_stubs` on `Linux`
