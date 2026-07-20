# TRAP SUBSHELL RESET

❌ Option A:
    détecter command substitution contenant seulement une seule commande trap
    dans ce cas seulement, ne pas reset les traps

✅ Option B:
	à l’entrée du subshell:
		snapshot des actions trap du parent
		reset réel des traps non ignored

	dans builtin trap sans opérandes / trap -p:
		si shell_is_subshell
		&& aucune commande trap avec operands n’a encore été exécutée dans ce subshell
			print snapshot parent
		else
			print état courant

- 📚 document:
	- `trap`:
		- as `bash`, *subshells* always reset *unignored traps* on entry and, while no *command* including `trap` with at least one *operand* has been executed, `trap` and `trap -p` always print *traps* are they were set immediatly before entering the *subshell* even if `trap -p` has one or more *operands*.

# WIP

- `shell`:
	- process `ENV` at startup:
		- See `ENVIRONMENT VARIABLES` -> `ENV` section in [sh](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/sh.html).
		- `If the expanded value of ENV is not an absolute pathname, the results are unspecified` ([sh](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/sh.html) -> `ENVIRONMENT VARIABLES` -> `ENV`)
- `builtins`:
	- `eval`
	- `continue`
	- `break`
	- `return`
	- `kill`
- `options`:
	- handle all options properly
- `undefined_behaviour()`:
	- print la tête à Xavier
- `runner-executor`:
	- `exec` specific flow
	- `command` specific flow
