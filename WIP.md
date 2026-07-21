# WIP

- `cmd sub` parsing:
	- tester avec `(` dans l'input:
		- `reduce` sur `SYM_subshell` => success
		- `ACTION_ERROR` + last `token` == `SYM_RPARENT` => replace `lookahead` par `SYM_EOF` => `ACTION_ERROR || ACTION_SHIFT` = error
	- test `bash` hack : `comsub:     DOLPAREN compound_list ')'`

🚨 Don't `accept` on `EOF` while parsing `cmd_sub_end` !!

- `parser_init()`
- `runner_init()`

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
