# WIP

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
