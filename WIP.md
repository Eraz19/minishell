# FIX

- `builtin_set`:
	- shall throw `ERR_INVALID_USAGE` when `-o` / `+o` is used without `option` but `first_operand_index` < `argc`
- `builtin_env`:
	- implement `utility` execution:
		- *resolve* cmd_name => *external* vs *builtin*
		- *execute* => `fork` + `execve`

# OTHERS

- when shell options are invalid => requalify error in `ERR_INVALID_USAGE`
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
