# A AJOUTER

- Toutes les APIs `*_init()`, `*_clear`, `*_free()` doivent être indempotentes et permettre la réutilisation ultérieure de l'item sans avoir à call `*_init()` à nouveau.
- Toutes les fonctions en charge du peuplement initial d'un objet doivent *init* cet objet elles-mêmes et le *free* elles-même en cas d'erreur durant le peuplement. C'est seulement une fois que le peuplement est succesful que le *free* ultérieur devient la responsabilité du caller.
- Lorsqu'on requalifie une erreur, il faut utiliser `err.type = ...` et non pas `err = error(...)` sinon on perd le `err.printed` et on risque un double print de l'erreur
- Tous les builtins doivent utiliser `builtin_print_and_qualify()` pour print / requalifier leurs erreurs avant de retourner

# PROMPT

On a fini notre shell fully POSIX-compliant.

On a juste, par manque de temps, fait l'impasse sur certaines `options`, `builtins` et `expansions` qu'on implémentera plus tard.
Les `options` non implémentées sont :
- `-b`: immediate notification of terminated jobs
- `-m`: enable job control (partially implemented)
- `-u`: error on unset variables
- `-v`: print input lines as read
- `-o nolog`: prevent function definitions from being entered in command history (may have no effect)
- `-o vi`: enable shell command line editing using the built-in vi editor
Les `builtins` non implémentés sont :
- `bg`
- `command`
- `fc`
- `fg`
- `getopts`
- `hash`
- `jobs`
- `kill`
- `read`
- `type`
- `ulimit`
- `umask`
- `exec`
- `times`
Les `expansions` non implémentées sont :
- `arithmetic expansion`

J'ai mis dans to knowledge le fichier `TO_DOCUMENT.md`. C'est le brouillon qui nous servira à rédiger la documentation finale.

Toutes les API `*_init()`, `*_clear()`, `*_free()` doivent être indempotentes et laisser l'objet dans un état permettant sa réutilisation ultérieure sans avoir à `*_init()` à nouveau après avoir `*_clear()` / `*_free()`.

Je vais te donner le code de chaque *module*, un par un.
Pour chacun d'entre eux je veux que tu vérifies :
- Si le code est *safe C* (pas de *segfault*, pas de *leak*, pas de *use after free*, etc):
	- On part toujours du principe que les *callers* / *callees* font correctement leur job, donc pas `NULL`-check inutile, pas de zèle sur un potentiel miss-use éventuel, etc. Je veux que tu reportes **UNIQUEMENT** les erreurs / bugs **RÉELS ET CONCRETS**
- Si les *erreurs* sont correctement requalifiées et printées:
	- Les *erreurs* retournées doivent faire du sens pour les *callers*
	- Les *erreurs* doivent être print avec `error_print()` dès qu'il est certain que le *caller* ne pourrait pas l'absorber
	- Par exemple: les `ERR_INDEX_OUT_OF_BOUND`, `ERR_SHELL_NOT_FOUND` etc doivent être immédiatement printées puis requalifiées en `ERR_INTERNAL` avant d'être retournées au *caller*.
- Si le comportement du *module* est fully POSIX-compliant :
	- Aucun comportement ne doit être **contraire** à ce que POSIX **impose**
	- Tous les comportements **imposés** par POSIX doivent:
		- être implémentés (hormis les exceptions citées ci-dessus)
		- Si la `whitelist` de fonctions autorisées ne nous permet pas d'implémenter le comportement **imposé** par POSIX:
			- une entrée correspondante doit exister dans `TO_DOCUMENT.md` dans la section `POSIX LIMITATIONS DUE 42 FUNCTIONS WHITELIST`
	- Chaque comportement cité comme *undefined* par POSIX doit:
		- trigger le call de `undefined_behaviour()`
		- avoir une entrée correspondante dans `TO_DOCUMENT.md` dans la section `POSIX UNDEFINED BEHAVIOURS`
	- Chaque comportement cité comme *unspecified* par POSIX doit:
		- trigger le call de `print_unspecified_behaviour()`
		- avoir une entrée correspondante dans `TO_DOCUMENT.md` dans la section `POSIX UNSPECIFIED IMPLEMENTATIONS`

Lorsque tu évalues le comportement d'un *module* tu peux, si nécessaire, regarder le code dans `codebase.md` dans ton knowledge pour vérifier le comportement des *callers* / *callees*. L'objectif n'est alors pas de faire une analyse complète des *callers* / *callees*, car ils seront analysés plus tard (ou déjà analysés), mais simplement de t'assurer que l'interaction entre le *module* actuellement analysé et les *callers* / *callees* produit bien le comportement visé par POSIX.

Pour chaque *module*, tu **DOIS** d'abord relire **L'INTÉGRALITÉ** de la documentation POSIX qui en dicte le comportement.
Tu as toute la documentation POSIX 2024 issue 8 dans ton knowledge donc vérifie d'abord ici et ne regarde sur internet **QUE** si c'est strictement nécessaire.
Ensuite analyse le code du *module*.
Ton analyse doit être stricte mais prendre en compte les limitations indiquées ci-dessus (parties non implémentées et limitations dues à la whitelist).
Tous les bullet points doivent indiquer le nom du fichier et le nom de la fonction correspondants.

Après analyse, je veux que tu me fasses un rapport complet de l'état du *module*.
Ce rapport doit être sous forme de bullet points.
Lorsque `de façon claire et concise` est utilisé ci-dessous, essaye autant que possible de n'utiliser qu'une seule phrase.
Les comportements valides n'ont pas besoin d'être cités, ça rendra ta réponse plus courte et plus lisible.
- Si tout est valide :
	- Réponds uniquement `Ce module est fully POSIX-compliant`
- Si un comportement est *unsafe C*:
	- Commence ce bullet point par `🚨 Bug: <file> <function>`
- Si un `free()` ou tout autre call pouvant modifier `errno` (hormis les calls à des fonctions de `libft`) est effectué entre la survenance de l'erreur et le call `error_sys()` ou `error_libc()` (uniquement ces deux calls là, les autres calls à `error(...)` sont OK):
	- Commence ce bullet point par `⚠️ Errno undefined: <file> <function>`
	- Montre un snippet du code incorrect, pas besoin de plus de précision, juste le titre du bullet point et le snippet du code existant.
- Si une *erreur* n'est pas correctement requalifiée ou printée
	- Commence ce bullet point par `⚠️ Errno undefined: <file> <function>`
	- Explique de façon claire et concise pourquoi l'erreur devrait être requalifiée ou printée ici.
- Si un comportement **contrevient** à ce que POSIX **impose** **OU** si un comportement **imposé** par POSIX n'est pas implémenté:
	- Si ce miss-match de comportement n'est **PAS** causé par une des limitations citées ci-dessus:
		- Commence ce bullet point par `❌ Comportement à corriger: <file> <function>`
		- Explique de façon claire et concise quel comportement POSIX impose.
		- Explique de façon claire et concise quel comportement le module produit actuellement.
		- Explique de façon claire et concise les modifications qu'il faudrait faire pour rendre le module fully POSIX-compliant.
		- Ne génère pas de code, uniquement des explications textuelles.
	- Si ce miss-match de comportement **EST** causé par une des limitations citées ci-dessus **OU** si le comportement est décrit comme *undefined* ou *unspecified* par POSIX:
		- Vérifie si une entrée existe déjà dans la section correspondante de `TO_DOCUMENT.md`.
		- Si une entrée correspondante existe déjà:
			- Si l'entrée correspondante explique déjà correctement:
				- Passe ce comportement sous silence, comme si c'était un comportement fully POSIX-compliant
			- Si l'entrée correspondante n'explique pas correctement:
				- Commence ce bullet point par `📚 Documentation à modifier: <file> <function>`
				- Génère une (et une seule) formulation correcte pour l'entrée
		- Si aucune entrée ne correspond:
			- Commence ce bullet point par `📚 Comportement à documenter: <file> <function>`
			- Génère une (et une seule) formulation pour l'entrée
	- Si un comportement cité comme *undefined* ou *unspecified* par POSIX ne trigger pas la fonction correspondante `undefined_behaviour()` ou `print_unspecified_behaviour()`:
		- Commence ce bullet point par `📄 Logs <undefined / unspecified> à ajouter: <file> <function>`
