# FIX GRAMMAR CONTINUATION ISSUE

- Si `SYM_EOF` alors que construction en attente (`SYM_SHIFT possible ?`)
	- call `scanner_get_next_token()` avec `continuation == true`
	- drop `SYM_EOF` (lookahead) + `SYM_NEWLINE` (`item_stack`) précédents

# OTHERS

- rename `params` to `env`
- ⚠️ `qualify_2()`
- `shell`:
	- process `ENV` at startup:
		- See `ENVIRONMENT VARIABLES` -> `ENV` section in [sh](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/sh.html).
		- `If the expanded value of ENV is not an absolute pathname, the results are unspecified` ([sh](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/sh.html) -> `ENVIRONMENT VARIABLES` -> `ENV`)
- `builtins`:
	- `continue`
	- `break`
	- `return`
	- `kill`
- `options`:
	- handle all options properly
- `runner-executor`:
	- `exec` specific flow
	- `command` specific flow
