# Classes

| Catégorie POSIX | Définition | PATH search ? | Accessible via `exec*()` requis par POSIX ? | Shell exit sur utility error ? |
|----------------|-----------|---------------|---------------------------------------------|--------------------------------|
| Special built-in | Utilities listées dans XCU 2.15 (`break`, `:`, `continue`, `.`, `eval`, `exec`, `exit`, `export`, `readonly`, `return`, `set`, `shift`, `times`, `trap`, `unset`) | **Non** : résolues avant toute recherche PATH (XCU 2.9.1.4, étape 1a) | **Non requis** (XCU 2.15) | **Oui** en shell non interactif si exécuté directement (XCU 2.8.1) |
| Intrinsic utility | Utilities listées dans XCU 1.7 (`alias`, `cd`, `read`, `wait`, etc.) | **Non** : résolues avant PATH, après fonctions (XCU 2.9.1.4, étape 1d) | **Non requis**, sauf `kill` (XCU 1.6, 1.7) | **Non** |
| Other standard utility | Toute utility standard qui n’est ni special built-in ni intrinsic | **Oui** (XCU 2.9.1.4, étape 1e) | **Oui** (XCU 1.6) | **Non** |
| Regular built-in | Mode d’implémentation interne d’une utility standard (pas une catégorie normative POSIX) | Selon la catégorie POSIX de l’utility implémentée | Selon la catégorie POSIX de l’utility implémentée | Selon la catégorie POSIX de l’utility implémentée |

# [2.15 Special Built-In Utilities](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_15)

- Output on `stdout`
- Any `utility` can be a `built-in`
- A **SPECIAL** `built-in` is different from a `built-in` because:
	- **Errors**: May exit `shell` (if not, exit-value shall be non_zero)

> 2. As described in [2.9.1 Simple Commands](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_09_01), variable assignments preceding the invocation of a special built-in utility affect the current execution environment; this shall not be the case with a regular built-in or other utility.
The special built-in utilities in this section need not be provided in a manner accessible via the exec family of functions defined in the System Interfaces volume of POSIX.1-2024.
>
> Some of the special built-ins are described as conforming to [XBD 12.2 Utility Syntax Guidelines](https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/V1_chap12.html#tag_12_02). For those that are not, the requirement in [1.4 Utility Description Defaults](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap01.html#tag_18_04) that "--" be recognized as a first argument to be discarded does not apply and a conforming application shall not use that argument.

# Errors

[1.4 Utility Description Defaults](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap01.html#tag_18_04)
```
STDERR
[...]
Default Behavior: When this section is listed as "The standard error shall be used only for diagnostic messages.", it means that, unless otherwise stated, the diagnostic messages shall be sent to the standard error only when the exit status indicates that an error occurred and the utility is used as described by this volume of POSIX.1-2024.
```

# Undefined behaviours

[12. Utility Conventions](https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/V1_chap12.html)
```
If an option that does not have option-arguments is repeated, the results are undefined, unless otherwise stated.
```

[12. Utility Conventions](https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/V1_chap12.html)
```
When multiple synopsis lines are given for a utility, it is an indication that the utility has mutually-exclusive arguments.
[...]
The use of conflicting mutually-exclusive arguments produces undefined results, unless a utility description specifies otherwise.
```