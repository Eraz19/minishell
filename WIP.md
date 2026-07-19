# SIGNAL MANAGE

- 🏁 *safe point* après chaque `simple command`
- ⚠️ `POSIX` requirements before `fork`, etc ?
- ⚠️ `shell`:
	- ⚠️ `shell_init_subshell()`:
		- Do the optional check of cmd sub containing only a trap command (lex only):
		- too complicated to handle the otherwise statement
		- document it in unspecified behaviours
	- ⚠️ `shell_ignore_signal()`:
		- let `sig` module handle it !
