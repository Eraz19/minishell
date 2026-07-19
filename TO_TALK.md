# ALEXANDER

- ⚠️ `scanner_set_cmd_sub_input()`
- ⚠️ wrong error message:
	- `wrong "error` puis `CTRL+D` should print `syntax error` / `unexpected end of input` ?
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
- 🚧 `shell`:
	- `shell_init_subshell()`: (only missing traps / signal handling)
- 🤔 **OLD**:
	- `utils`:
		- Utiliser `free_char_ptr_void()` au lieu de `free` comme callback pour les `vector_fre()` contenant des `char *`
	- replace `string_read_all()` by `posix_read()` and make `posix_read()` use `string_read_all()` (don't retry auto !)
	- Pour debug sous `Linux` => `launch.json` => `"MIMode": "gdb"`
- ✅ `exit`:
	- ✅ fixed: citation (section + wording)
	- ✅ fixed: didn't handle `--`
	- ✅ fixed: didn't handle `n < 0` case
	- ✅ fixed: correctly handle `n == 256` case
	- ✅ fixed: correctly handle `n > 256` by checking if corresponds to `128 + sig`
	- ✅ fixed: always return `ERR_EXIT` / `ERR_EXIT_WITH_CURRENT_STATUS`:
		- "**shall** cause the shell to **exit** from its current execution environment"
		- "the **wait status** of the shell or subshell is **unspecified**"
		- user expect to exit
