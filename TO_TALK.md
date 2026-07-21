# TO TALK

- 🚨 `cmd sub` dans une `fonction`:
	- premier run va free l'`ast` / la `string` de la `cmd_sub` ??

- 🚨 Invalid `subshell` handling:
	- ⚠️ `scanner_init_subshell()` always set input mode to `SCAN_MODE_STDIN_PIPE`:
		- ✅ only do it if current mode is `SCAN_MODE_STDIN_TTY`
	- ⚠️ always init subshell in main scanner / parser instead of current one
		- 👉 Need to restructure architecture to always have correct structs in callers
		- 👉 `lexer` <- `scanner` <- `parser` <- `runner`
		- 👉 remove `shell_get_*()` (expect `shell_get_params()` but only allow `params` callers)
		- 👉 always call `*_init_subshell` to top level struct
- 🧠 J'ai laissé l'archi actuelle mais trop complexe pour rien cf `lexer->rules.on_eoi` => plus simple d'appler directement la bonne fonction...

- 🤔 D'après ChatGPT les cmd sub sont expandues même sans le flag `EXP_CMD_SUB`, il parle notamment des expansions de prompt mais `bash` le fait aussi donc à discuter pour être certain que ça reste dans le cadre POSIX

- 🔎 check `// TO_TALK` implementations
