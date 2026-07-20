# TRAP SUBSHELL RESET

Option A:
    détecter command substitution contenant seulement une seule commande trap
    dans ce cas seulement, ne pas reset les traps

Option B:
    ne pas faire ce check
    reset toujours les traps en subshell
    mais garder une snapshot parent
    et faire afficher cette snapshot par trap/trap -p tant qu’aucun trap avec opérandes
    n’a été exécuté depuis l’entrée dans le subshell

à l’entrée du subshell:
    snapshot des actions trap du parent
    reset réel des traps non ignored

dans builtin trap sans opérandes / trap -p:
    si shell_is_subshell
    && aucune commande trap avec operands n’a encore été exécutée dans ce subshell
        print snapshot parent
    else
        print état courant

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
