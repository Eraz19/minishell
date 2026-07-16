# Tests POSIX — ordre `expansions` / `redirections` / `assignments` / exécution

Objectif : vérifier l'ordre de traitement d'une `simple command` dans le `runner`, sans utiliser de comportement `unspecified` comme oracle.

Sources POSIX principales :

- `2.9.1.1 Simple Commands — Order of Processing`
- `2.9.1.2 Simple Commands — Variable Assignments`
- `2.9.1.4 Command Search and Execution`
- `2.9.1.6 Non-built-in Utility Execution`
- `2.6.2 Parameter Expansion`
- `2.15 Special Built-In Utilities`
- `export` special builtin, car `export` est une declaration utility

Hypothèses pratiques :

- Exécuter ces tests depuis la racine du projet.
- `set -x` doit être désactivé pour comparer les résultats bruts ci-dessous.
- Les résultats attendus sont les sorties `stdout` brutes.
- Les tests évitent volontairement :
  - les effets de bord des expansions d'`assignment words` en étape 4, car POSIX laisse une partie de leur visibilité `unspecified` pour les commandes non-special ;
  - la persistance des `assignments` après une fonction, car POSIX la laisse `unspecified` ;
  - les cas `no command name` ou `special builtin` utilisés pour vérifier l'ordre relatif étapes 3/4, car POSIX autorise l'inversion de ces deux étapes dans ces cas.
- Le choix projet "ne jamais inverser les étapes 3 et 4" est donc compatible avec ces tests, mais les tests ci-dessous ne l'utilisent pas comme oracle POSIX dans les cas où POSIX permettrait l'inversion.

---

## Test 1 — Test principal d'ordre global pour une commande externe

### Commande à effectuer

```sh
rm -f ./po_from_arg ./po_from_assignment
unset ORD_SIDE

ORD_SIDE=./po_from_assignment sh -c 'printf "child:ORD_SIDE=<%s>;arg1=<%s>\n" "$ORD_SIDE" "$1"' sh "${ORD_SIDE:=./po_from_arg}" > "$ORD_SIDE"

printf 'after_SIDE=<%s>\n' "$ORD_SIDE"

printf 'po_from_arg='
if test -f ./po_from_arg; then
    cat ./po_from_arg
else
    printf 'MISSING\n'
fi

printf 'po_from_assignment='
if test -f ./po_from_assignment; then
    cat ./po_from_assignment
else
    printf 'MISSING\n'
fi

rm -f ./po_from_arg ./po_from_assignment
```

### Résultat attendu brut

```text
after_SIDE=<./po_from_arg>
po_from_arg=child:ORD_SIDE=<./po_from_assignment>;arg1=<./po_from_arg>
po_from_assignment=MISSING
```

### Explication rapide du résultat attendu

La `simple command` centrale est :

```sh
ORD_SIDE=./po_from_assignment sh -c '...' sh "${ORD_SIDE:=./po_from_arg}" > "$ORD_SIDE"
```

Ordre POSIX attendu :

1. `ORD_SIDE=./po_from_assignment` est reconnu comme `assignment word` et sauvegardé pour l'étape 4.
2. Les `words` de commande sont expansés. L'argument `"${ORD_SIDE:=./po_from_arg}"` assigne `ORD_SIDE=./po_from_arg` dans le shell courant, car c'est une expansion de paramètre régulière, pas une expansion d'`assignment word`.
3. La `redirection` `> "$ORD_SIDE"` est effectuée. Elle doit donc cibler `./po_from_arg`, pas `./po_from_assignment`.
4. L'`assignment word` `ORD_SIDE=./po_from_assignment` est appliqué à l'environnement de la commande externe `sh`.
5. Le `sh` enfant voit donc `ORD_SIDE=./po_from_assignment`.
6. Après la commande, comme `sh` n'est ni une fonction ni un `special builtin`, l'`assignment word` ne persiste pas dans le shell courant. En revanche, le side-effect de `"${ORD_SIDE:=./po_from_arg}"` persiste, donc `after_SIDE=<./po_from_arg>`.

Ce test détecte notamment ces erreurs :

- appliquer les `assignment words` avant les expansions des arguments ;
- effectuer les `assignments` avant les `redirections` pour une commande externe ;
- ne pas exporter les `assignments` vers l'environnement de la commande externe ;
- faire persister dans le shell courant un `assignment word` précédant une commande externe.

---

## Test 2 — Les arguments sont expansés avant les `assignments`, mais les `assignments` sont visibles dans l'environnement externe

### Commande à effectuer

```sh
unset ORD_EXT

ORD_EXT=env_value sh -c 'printf "child:ORD_EXT=<%s>;arg1=<%s>\n" "$ORD_EXT" "$1"' sh "$ORD_EXT"

printf 'after_EXT=<%s>\n' "$ORD_EXT"
```

### Résultat attendu brut

```text
child:ORD_EXT=<env_value>;arg1=<>
after_EXT=<>
```

### Explication rapide du résultat attendu

`"$ORD_EXT"` est un argument de la commande ; il est donc expansé en étape 2, avant que `ORD_EXT=env_value` soit appliqué en étape 4. Comme `ORD_EXT` est unset à ce moment-là, l'argument reçu par le `sh` enfant est vide.

En revanche, l'`assignment word` est exporté dans l'environnement de la commande externe, donc le `sh` enfant voit `ORD_EXT=env_value`.

Après la commande, `ORD_EXT` reste unset dans le shell courant, car l'`assignment word` précède une commande qui n'est ni une fonction ni un `special builtin`.

---

## Test 3 — Les `redirections` utilisent l'environnement courant avant les `assignments` d'une commande externe

### Commande à effectuer

```sh
rm -f ./po_redir_old ./po_redir_new
unset ORD_REDIR

ORD_REDIR=./po_redir_old

ORD_REDIR=./po_redir_new sh -c 'printf "redir_child=<%s>\n" "$ORD_REDIR"' > "$ORD_REDIR"

printf 'after_REDIR=<%s>\n' "$ORD_REDIR"

printf 'po_redir_old='
if test -f ./po_redir_old; then
    cat ./po_redir_old
else
    printf 'MISSING\n'
fi

printf 'po_redir_new='
if test -f ./po_redir_new; then
    cat ./po_redir_new
else
    printf 'MISSING\n'
fi

rm -f ./po_redir_old ./po_redir_new
```

### Résultat attendu brut

```text
after_REDIR=<./po_redir_old>
po_redir_old=redir_child=<./po_redir_new>
po_redir_new=MISSING
```

### Explication rapide du résultat attendu

La `redirection` `> "$ORD_REDIR"` est effectuée en étape 3. À ce moment-là, l'`assignment word` `ORD_REDIR=./po_redir_new` n'a pas encore été appliqué, donc la redirection utilise l'ancienne valeur `./po_redir_old`.

Ensuite, l'étape 4 applique `ORD_REDIR=./po_redir_new` à l'environnement de la commande externe. Le `sh` enfant imprime donc `redir_child=<./po_redir_new>` dans `./po_redir_old`.

Après la commande, le shell courant garde `ORD_REDIR=./po_redir_old`, car l'`assignment word` ne persiste pas pour une commande externe.

---

## Test 4 — Un `assignment` sans `command name` affecte le shell courant

### Commande à effectuer

```sh
unset ORD_NONE

ORD_NONE=kept

printf 'after_none=<%s>\n' "$ORD_NONE"
```

### Résultat attendu brut

```text
after_none=<kept>
```

### Explication rapide du résultat attendu

Quand une `simple command` ne produit aucun `command name`, ses `variable assignments` affectent le `current execution environment`.

Ce test ne contient pas de `redirection`, afin d'éviter le cas POSIX où les redirections d'une commande sans `command name` ont des règles spécifiques.

---

## Test 5 — Un `assignment` précédant un `special builtin` persiste

### Commande à effectuer

```sh
unset ORD_SPECIAL

ORD_SPECIAL=kept :

printf 'after_special=<%s>\n' "$ORD_SPECIAL"
```

### Résultat attendu brut

```text
after_special=<kept>
```

### Explication rapide du résultat attendu

`:` est un `special builtin`. POSIX impose que les `variable assignments` précédant un `special builtin` affectent le shell courant avant l'exécution du builtin et restent en effet après la fin de la commande.

Ce test ne vérifie pas l'attribut d'export éventuel, car POSIX laisse cet aspect `unspecified` sauf si `set -a` est actif.

---

## Test 6 — Un `assignment` précédant une fonction est visible pendant l'exécution de la fonction

### Commande à effectuer

```sh
unset ORD_FUNC

ord_func() {
    printf 'inside_func=<%s>\n' "$ORD_FUNC"
}

ORD_FUNC=visible ord_func
```

### Résultat attendu brut

```text
inside_func=<visible>
```

### Explication rapide du résultat attendu

Pour une fonction shell qui n'est pas une standard utility implémentée comme fonction, les `variable assignments` précédant le `command name` affectent le shell courant pendant l'exécution de la fonction.

Le test ne vérifie pas la valeur de `ORD_FUNC` après l'appel de fonction, car POSIX laisse la persistance après fonction `unspecified`. Votre choix projet est de faire persister ces `assignments`, mais ce choix ne doit pas être mélangé avec une suite de tests POSIX-stricte.

---

## Test 7 — `export` reconnu comme declaration utility : expansion en contexte d'assignment

### Commande à effectuer

```sh
unset ORD_DECL ORD_SRC

ORD_SRC='a b'

export ORD_DECL=$ORD_SRC

printf 'decl=<%s>\n' "$ORD_DECL"
```

### Résultat attendu brut

```text
decl=<a b>
```

### Explication rapide du résultat attendu

`export` est une `declaration utility`. Quand `export` est reconnu comme `command name`, les mots suivants qui seraient des `variable assignments` en isolation sont expansés comme des assignments : pas de field splitting, pas de pathname expansion.

Donc `ORD_DECL=$ORD_SRC` assigne la valeur complète `a b` à `ORD_DECL`, au lieu de produire plusieurs champs.

---

## Test 8 — Un `PATH=...` temporaire est utilisé pour la recherche d'une commande externe

### Commande à effectuer

```sh
PATH=./tests test_exec >/dev/null

printf 'path_status=<%s>\n' "$?"

case ":$PATH:" in
    *:./tests:*) printf 'after_PATH=LEAK\n' ;;
    *) printf 'after_PATH=NO_LEAK\n' ;;
esac
```

### Résultat attendu brut

```text
path_status=<0>
after_PATH=NO_LEAK
```

### Explication rapide du résultat attendu

Ce test suppose que l'exécutable `./tests/test_exec` existe et retourne `0`.

`PATH=./tests` est un `assignment word` précédant une commande externe. Il doit être utilisé pour l'environnement d'exécution et pour la recherche de `test_exec`, mais il ne doit pas persister dans le shell courant après la commande.

Le test redirige la sortie de `test_exec` vers `/dev/null`, car seul son statut de réussite est utilisé ici.

---

## Test 9 — ???

### Commande à effectuer

```bash
unset A B
A=foo B=$A :
printf 'A=<%s>;B=<%s>\n' "$A" "$B"
```

### Résultat attendu brut

```text
A=<foo>;B=<foo>
```

### Explication rapide du résultat attendu

`:` est un `special builtin`; les `assignments` sont traités de gauche à droite et affectent le `current execution environment`. Donc `A=foo` est appliqué avant l’expansion/assignment de `B=$A`, puis les deux persistent après `:`. L’ordre général “du début du texte de commande vers la fin” est imposé par `POSIX 2.9.1.1`.

---

## Ce que cette suite ne prétend pas prouver

Ces tests augmentent fortement la confiance dans l'ordre du `executor`, mais ils ne prouvent pas une conformité POSIX à 100 %. Ils ne couvrent pas tous les cas de grammaire, toutes les erreurs de redirection, toutes les formes d'expansion, ni toutes les `utilities`.

En particulier, cette suite évite volontairement les oracles fondés sur des comportements `unspecified`, même si votre projet a choisi une politique déterministe pour certains d'entre eux.
