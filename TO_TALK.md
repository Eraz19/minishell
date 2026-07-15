# ALEXANDER

- ⚠️ docs:
	- Replace `Same contract as @ref ...` par les erreurs retournées (insup à utiliser)
- `token`: keep `history_list_index` in `t_token_index` ?
```bash
VAR=value          => status 0
VAR=$(true)        => status 0
VAR=$(false)       => status 1
VAR=${bad syntax}  => ERR_POSIX_EXPANSION
```
- ⚠️ **all**:
	- replace all `ERR_INDEX_OUT_OF_BOND`, etc by `error_print()` + `ERR_INTERNAL`
- 🤔 move `heredoc.h` into `srcs/scanner/` ?
- `echo` (and other builtins):
	- Minimal 42 implementation or POSIX implementation ?
- 🚧 `shell`:
	- `shell_init_subshell()`: (only missing traps / signal handling)
- 🤔 **OLD**:
	- `utils`:
		- Utiliser `free_char_ptr_void()` au lieu de `free` comme callback pour les `vector_fre()` contenant des `char *`
	- replace `string_read_all()` by `posix_read()` and make `posix_read()` use `string_read_all()` (don't retry auto !)
	- Pour debug sous `Linux` => `launch.json` => `"MIMode": "gdb"`
