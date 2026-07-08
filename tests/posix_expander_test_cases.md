# POSIX Shell Expander Test Cases


Ce fichier regroupe les cas de tests générés pour valider l’`expander`.

Format des attentes :

```text
argv = [...]
```

sauf indication contraire.

Hypothèses générales :

```text
- ./test_exec affiche clairement argv.
- Les commandes sont exécutées dans l’ordre.
- Les comportements marqués “unspecified POSIX” ne doivent pas être utilisés comme tests stricts.
```

Sources POSIX principales :

```text
2.6 Word Expansions
2.6.1 Tilde Expansion
2.6.2 Parameter Expansion
2.6.5 Field Splitting
2.6.6 Pathname Expansion
2.6.7 Quote Removal
2.13 Pattern Matching Notation
2.13.3 Patterns Used for Filename Expansion
2.9.1.1 Order of Processing
```

---

# 1. Parameter Expansion

## Setup

```sh
unset IFS
unset U
A='a b'
B='c  d'
EMPTY=
CMD=./test_exec
CMD_SPLIT='./test_exec from_var'
```

## Tests

| # | Command | Expected |
|---|---|---|
| 1 | `./test_exec $A` | `argv = ["./test_exec", "a", "b"]` |
| 2 | `./test_exec "$A"` | `argv = ["./test_exec", "a b"]` |
| 3 | `./test_exec $B` | `argv = ["./test_exec", "c", "d"]` |
| 4 | `./test_exec "$B"` | `argv = ["./test_exec", "c  d"]` |
| 5 | `./test_exec before $U after` | `argv = ["./test_exec", "before", "after"]` |
| 6 | `./test_exec before "$U" after` | `argv = ["./test_exec", "before", "", "after"]` |
| 7 | `./test_exec before $EMPTY after` | `argv = ["./test_exec", "before", "after"]` |
| 8 | `./test_exec before "$EMPTY" after` | `argv = ["./test_exec", "before", "", "after"]` |
| 9 | `./test_exec pre${A}post` | `argv = ["./test_exec", "prea", "bpost"]` |
| 10 | `./test_exec pre"$A"post` | `argv = ["./test_exec", "prea bpost"]` |
| 11 | `./test_exec pre${EMPTY}post` | `argv = ["./test_exec", "prepost"]` |
| 12 | `./test_exec pre"$EMPTY"post` | `argv = ["./test_exec", "prepost"]` |
| 13 | `$CMD ok` | `argv = ["./test_exec", "ok"]` |
| 14 | `"$CMD" ok` | `argv = ["./test_exec", "ok"]` |
| 15 | `$U ./test_exec ok` | `argv = ["./test_exec", "ok"]` |
| 16 | `"$U" ./test_exec ok` | `command not found`, status `127`, `./test_exec` not executed |
| 17 | `$CMD_SPLIT end` | `argv = ["./test_exec", "from_var", "end"]` |
| 18 | `"$CMD_SPLIT" end` | `command not found`, status `127`, `./test_exec` not executed |
| 19 | `./test_exec ${U:-fallback}` | `argv = ["./test_exec", "fallback"]` |
| 20 | `./test_exec ${EMPTY:-fallback}` | `argv = ["./test_exec", "fallback"]` |
| 21 | `./test_exec ${U-fallback}` | `argv = ["./test_exec", "fallback"]` |
| 22 | `./test_exec before ${EMPTY-fallback} after` | `argv = ["./test_exec", "before", "after"]` |
| 23 | `./test_exec before "${EMPTY-fallback}" after` | `argv = ["./test_exec", "before", "", "after"]` |
| 24 | `./test_exec ${U:-"$A"}` | `argv = ["./test_exec", "a b"]` |
| 25 | `./test_exec ${A:+alt}` | `argv = ["./test_exec", "alt"]` |
| 26 | `./test_exec before ${EMPTY:+alt} after` | `argv = ["./test_exec", "before", "after"]` |
| 27 | `./test_exec ${EMPTY+alt}` | `argv = ["./test_exec", "alt"]` |
| 28 | `./test_exec before ${U+alt} after` | `argv = ["./test_exec", "before", "after"]` |
| 29 | `./test_exec before "${U+alt}" after` | `argv = ["./test_exec", "before", "", "after"]` |

## Tests multi-command

### `${parameter:=word}` avec unset

```sh
unset NEW1
./test_exec "${NEW1:=default}"
./test_exec "$NEW1"
```

Expected:

```text
first argv  = ["./test_exec", "default"]
second argv = ["./test_exec", "default"]
```

### `${parameter:=word}` avec null

```sh
NEW2=
./test_exec "${NEW2:=default}"
./test_exec "$NEW2"
```

Expected:

```text
first argv  = ["./test_exec", "default"]
second argv = ["./test_exec", "default"]
```

### `${parameter=word}` avec null : pas d’assignation

```sh
NEW3=
./test_exec before "${NEW3=default}" after
./test_exec before "$NEW3" after
```

Expected:

```text
first argv  = ["./test_exec", "before", "", "after"]
second argv = ["./test_exec", "before", "", "after"]
```

### `${parameter:?word}` avec unset

```sh
unset U
./test_exec before ${U:?missing} after
```

Expected:

```text
diagnostic d’erreur
./test_exec ne doit pas être exécuté
status non-zero
en script: shell exit
en saisie: shell continue
```

### `${parameter:?word}` avec null

```sh
EMPTY=
./test_exec before ${EMPTY:?missing} after
```

Expected:

```text
diagnostic d’erreur
./test_exec ne doit pas être exécuté
status non-zero
```

### `${parameter?word}` avec null : pas d’erreur

```sh
EMPTY=
./test_exec before "${EMPTY?missing}" after
```

Expected:

```text
argv = ["./test_exec", "before", "", "after"]
```

## Assignment context

```sh
C=$A
./test_exec "$C"
```

Expected:

```text
argv = ["./test_exec", "a b"]
```

```sh
./test_exec C=$A
```

Expected:

```text
argv = ["./test_exec", "C=a", "b"]
```

```sh
unset D
export D=$A
./test_exec "$D"
```

Expected:

```text
argv = ["./test_exec", "a b"]
```

```sh
unset R
readonly R=$A
./test_exec "$R"
readonly -p
```

Expected:

```text
./test_exec argv = ["./test_exec", "a b"]
readonly -p shows R readonly with value "a b"
```

## Pièges

| Command | Expected |
|---|---|
| `./test_exec X${A}Y${B}Z` | `argv = ["./test_exec", "Xa", "bYc", "dZ"]` |
| `./test_exec X"$A"Y"$B"Z` | `argv = ["./test_exec", "Xa bYc  dZ"]` |
| `./test_exec X"$A"Y${B}Z` | `argv = ["./test_exec", "Xa bYc", "dZ"]` |
| `unset DEF; ./test_exec "${DEF:-$A}"` | `argv = ["./test_exec", "a b"]` |
| `unset DEF; ./test_exec ${DEF:-$A}` | `argv = ["./test_exec", "a", "b"]` |
| `unset U1; unset U2; $U1 $U2 ./test_exec ok` | `argv = ["./test_exec", "ok"]` |

---

# 2. Pathname Expansion

Hypothèses :

```text
- Pas de set -f.
- Ordre attendu supposé avec LC_ALL=C / ordre bytewise.
```

## Setup

```sh
rm -rf g
mkdir -p g/base g/tree/dir/sub g/tree/empty g/lit

: > g/base/1
: > g/base/10
: > g/base/2
: > g/base/a
: > g/base/aa
: > g/base/ab
: > g/base/ac
: > g/base/b
: > g/base/ba
: > g/base/file.c
: > g/base/file.h
: > g/base/main.c
: > g/base/main.o
: > g/base/notes.txt
: > g/base/.a
: > g/base/.hidden

: > g/tree/dir/x
: > g/tree/dir/y.c
: > g/tree/dir/.z
: > g/tree/dir/sub/deep

: > 'g/lit/star*name'
: > 'g/lit/quest?name'
: > 'g/lit/brack[abc]'
: > g/lit/normal
```

## `*`

| Command | Expected |
|---|---|
| `./test_exec g/base/*` | `argv = ["./test_exec", "g/base/1", "g/base/10", "g/base/2", "g/base/a", "g/base/aa", "g/base/ab", "g/base/ac", "g/base/b", "g/base/ba", "g/base/file.c", "g/base/file.h", "g/base/main.c", "g/base/main.o", "g/base/notes.txt"]`; dotfiles excluded |
| `./test_exec g/base/a*` | `argv = ["./test_exec", "g/base/a", "g/base/aa", "g/base/ab", "g/base/ac"]` |
| `./test_exec g/base/*.c` | `argv = ["./test_exec", "g/base/file.c", "g/base/main.c"]` |
| `./test_exec g/base/*o` | `argv = ["./test_exec", "g/base/main.o"]` |
| `./test_exec g/base/*.*` | `argv = ["./test_exec", "g/base/file.c", "g/base/file.h", "g/base/main.c", "g/base/main.o", "g/base/notes.txt"]` |

## `?`

| Command | Expected |
|---|---|
| `./test_exec g/base/?` | `argv = ["./test_exec", "g/base/1", "g/base/2", "g/base/a", "g/base/b"]` |
| `./test_exec g/base/??` | `argv = ["./test_exec", "g/base/10", "g/base/aa", "g/base/ab", "g/base/ac", "g/base/ba"]` |
| `./test_exec g/base/a?` | `argv = ["./test_exec", "g/base/aa", "g/base/ab", "g/base/ac"]` |
| `./test_exec g/base/*.?` | `argv = ["./test_exec", "g/base/file.c", "g/base/file.h", "g/base/main.c", "g/base/main.o"]` |

## Bracket expressions

| Command | Expected |
|---|---|
| `./test_exec g/base/[ab]` | `argv = ["./test_exec", "g/base/a", "g/base/b"]` |
| `./test_exec g/base/a[abc]` | `argv = ["./test_exec", "g/base/aa", "g/base/ab", "g/base/ac"]` |
| `./test_exec g/base/[a-b]` | `argv = ["./test_exec", "g/base/a", "g/base/b"]` |
| `./test_exec g/base/[0-9]` | `argv = ["./test_exec", "g/base/1", "g/base/2"]` |
| `./test_exec g/base/[!ab]` | `argv = ["./test_exec", "g/base/1", "g/base/2"]`; one-char only |
| `./test_exec g/base/a[!a]` | `argv = ["./test_exec", "g/base/ab", "g/base/ac"]` |

## Pas de match : pattern conservé

| Command | Expected |
|---|---|
| `./test_exec g/base/no_match_*` | `argv = ["./test_exec", "g/base/no_match_*"]` |
| `./test_exec g/base/z[abc]` | `argv = ["./test_exec", "g/base/z[abc]"]` |
| `./test_exec g/base/???` | `argv = ["./test_exec", "g/base/???"]` |

## Dotfiles

| Command | Expected |
|---|---|
| `./test_exec g/base/*` | same as above; must not include `g/base/.a` or `g/base/.hidden` |
| `./test_exec g/base/.*` | `argv = ["./test_exec", "g/base/.a", "g/base/.hidden"]`; according to your policy, verify `.` and `..` are not output |
| `./test_exec g/base/.?` | `argv = ["./test_exec", "g/base/.a"]` |
| `./test_exec g/base/?` | same as above; must not include `g/base/.a` |

## Slash : patterns do not cross `/`

| Command | Expected |
|---|---|
| `./test_exec g/tree/*` | `argv = ["./test_exec", "g/tree/dir", "g/tree/empty"]`; no nested files |
| `./test_exec g/tree/*/*` | `argv = ["./test_exec", "g/tree/dir/sub", "g/tree/dir/x", "g/tree/dir/y.c"]`; must not include `g/tree/dir/.z` |
| `./test_exec g/tree/*/*/*` | `argv = ["./test_exec", "g/tree/dir/sub/deep"]` |
| `./test_exec g/tree/dir/.*` | `argv = ["./test_exec", "g/tree/dir/.z"]` |

## Quotes / escapes disable metacharacters

| Command | Expected |
|---|---|
| `./test_exec "g/base/*"` | `argv = ["./test_exec", "g/base/*"]` |
| `./test_exec 'g/base/?'` | `argv = ["./test_exec", "g/base/?"]` |
| `./test_exec "g/base/[ab]"` | `argv = ["./test_exec", "g/base/[ab]"]` |
| `./test_exec g/base/"a"*` | `argv = ["./test_exec", "g/base/a", "g/base/aa", "g/base/ab", "g/base/ac"]`; `a` literal, `*` active |
| `./test_exec g/base/\*` | `argv = ["./test_exec", "g/base/*"]` |

## Filenames containing glob characters

| Command | Expected |
|---|---|
| `./test_exec g/lit/*` | `argv = ["./test_exec", "g/lit/brack[abc]", "g/lit/normal", "g/lit/quest?name", "g/lit/star*name"]` |
| `./test_exec 'g/lit/star*name'` | `argv = ["./test_exec", "g/lit/star*name"]` |
| `./test_exec g/lit/star*` | `argv = ["./test_exec", "g/lit/star*name"]` |
| `./test_exec g/lit/quest?name` | `argv = ["./test_exec", "g/lit/quest?name"]` |
| `./test_exec g/lit/brack[abc]` | `argv = ["./test_exec", "g/lit/brack[abc]"]`; ambiguous: pattern did not match, original preserved |
| `./test_exec 'g/lit/brack[abc]'` | `argv = ["./test_exec", "g/lit/brack[abc]"]`; literal quoted filename |

## After parameter expansion

| Command | Expected |
|---|---|
| `P='g/base/*.c'; ./test_exec $P` | `argv = ["./test_exec", "g/base/file.c", "g/base/main.c"]` |
| `P='g/base/*.c'; ./test_exec "$P"` | `argv = ["./test_exec", "g/base/*.c"]` |
| `EXT=c; ./test_exec g/base/*.$EXT` | `argv = ["./test_exec", "g/base/file.c", "g/base/main.c"]` |
| `EXT=c; ./test_exec g/base/*."$EXT"` | `argv = ["./test_exec", "g/base/file.c", "g/base/main.c"]`; `*` remains active |
| `P='g/base/*.c g/base/*.h'; ./test_exec $P` | `argv = ["./test_exec", "g/base/file.c", "g/base/main.c", "g/base/file.h"]`; split fields are expanded independently, not globally resorted |

## Assignment context

| Command | Expected |
|---|---|
| `GLOB=g/base/*.c; ./test_exec "$GLOB"` | `argv = ["./test_exec", "g/base/*.c"]` |
| `GLOB=g/base/*.c ./test_exec "$GLOB"` | `argv = ["./test_exec", ""]`; temp assignment does not affect same command word expansion |
| `unset GLOB; export GLOB=g/base/*.c; ./test_exec "$GLOB"` | `argv = ["./test_exec", "g/base/*.c"]` |

## Pathname expansion in command-name position

| Command | Expected |
|---|---|
| `./test_exec g/base/a` | `argv = ["./test_exec", "g/base/a"]` |
| `g/base/no_match_*` | `command not found`, status `127` |
| `g/base/a` | `command found but not executable`, status `126`, if `g/base/a` is not executable |

---

# 3. Field Splitting

Hypothèses :

```text
- Pas de pathname expansion parasite dans les valeurs utilisées.
```

## 3.1 IFS par défaut : whitespace splitting

### Setup

```sh
unset IFS
X='  a  b  '
Y='a b c'
EMPTY=
UNSET_ME=
unset UNSET_ME
```

| Command | Expected |
|---|---|
| `./test_exec $X` | `argv = ["./test_exec", "a", "b"]` |
| `./test_exec $Y` | `argv = ["./test_exec", "a", "b", "c"]` |
| `./test_exec "$X"` | `argv = ["./test_exec", "  a  b  "]` |
| `./test_exec before $UNSET_ME after` | `argv = ["./test_exec", "before", "after"]` |
| `./test_exec before "$UNSET_ME" after` | `argv = ["./test_exec", "before", "", "after"]` |
| `./test_exec before $EMPTY after` | `argv = ["./test_exec", "before", "after"]` |
| `./test_exec before "$EMPTY" after` | `argv = ["./test_exec", "before", "", "after"]` |

## 3.2 `IFS` vide : aucun field splitting

### Setup

```sh
IFS=
X='  a  b  '
Y='a:b:c'
```

| Command | Expected |
|---|---|
| `./test_exec $X` | `argv = ["./test_exec", "  a  b  "]` |
| `./test_exec $Y` | `argv = ["./test_exec", "a:b:c"]` |
| `unset U; ./test_exec before $U after` | `argv = ["./test_exec", "before", "after"]`; unset non quotée reste supprimée |

## 3.3 `IFS=:` : séparateur non-whitespace

### Setup

```sh
IFS=:
X='a:b:c'
Y='a::b:'
Z=':a::b:'
ONLY=':'
DOUBLE='::'
```

| Command | Expected |
|---|---|
| `./test_exec $X` | `argv = ["./test_exec", "a", "b", "c"]` |
| `./test_exec $Y` | `argv = ["./test_exec", "a", "", "b"]`; trailing `:` does not add an extra arg |
| `./test_exec $Z` | `argv = ["./test_exec", "", "a", "", "b"]` |
| `./test_exec $ONLY` | `argv = ["./test_exec", ""]` |
| `./test_exec $DOUBLE` | `argv = ["./test_exec", "", ""]` |
| `./test_exec "$Z"` | `argv = ["./test_exec", ":a::b:"]` |

## 3.4 `IFS=' ,'` : whitespace + non-whitespace

### Setup

```sh
IFS=' ,'
X=' a , b ,, c , '
Y=',a,,b,'
Z='  ,  a  ,  b  '
```

| Command | Expected |
|---|---|
| `./test_exec $X` | `argv = ["./test_exec", "a", "b", "", "c"]`; `,,` produces empty field |
| `./test_exec $Y` | `argv = ["./test_exec", "", "a", "", "b"]` |
| `./test_exec $Z` | `argv = ["./test_exec", "", "a", "b"]`; leading comma produces empty field |

## 3.5 `IFS=' '` : whitespace only explicite

### Setup

```sh
IFS=' '
X='  a  b  '
Y='a::b'
```

| Command | Expected |
|---|---|
| `./test_exec $X` | `argv = ["./test_exec", "a", "b"]` |
| `./test_exec $Y` | `argv = ["./test_exec", "a::b"]` |

## 3.6 Field splitting dans un word collé à du texte

### Setup

```sh
unset IFS
A='x y'
EMPTY=
```

| Command | Expected |
|---|---|
| `./test_exec pre${A}post` | `argv = ["./test_exec", "prex", "ypost"]` |
| `./test_exec pre"$A"post` | `argv = ["./test_exec", "prex ypost"]` |
| `./test_exec pre${EMPTY}post` | `argv = ["./test_exec", "prepost"]` |
| `./test_exec pre"$EMPTY"post` | `argv = ["./test_exec", "prepost"]`; no separate empty arg because quoted empty is glued to literal text |

## 3.7 Plusieurs expansions dans le même word

### Setup

```sh
unset IFS
A='a b'
B='c d'
```

| Command | Expected |
|---|---|
| `./test_exec X${A}Y${B}Z` | `argv = ["./test_exec", "Xa", "bYc", "dZ"]` |
| `./test_exec X"$A"Y"$B"Z` | `argv = ["./test_exec", "Xa bYc dZ"]` |
| `./test_exec X"$A"Y${B}Z` | `argv = ["./test_exec", "Xa bYc", "dZ"]` |

## 3.8 Position critique : command name

### Setup

```sh
unset IFS
CMD='./test_exec ok'
EMPTY=
unset U
```

| Command | Expected |
|---|---|
| `$CMD end` | `argv = ["./test_exec", "ok", "end"]` |
| `"$CMD" end` | `command not found`, status `127` |
| `$U ./test_exec ok` | `argv = ["./test_exec", "ok"]` |
| `"$U" ./test_exec ok` | `command not found`, status `127`, `./test_exec` not executed |

## 3.9 Assignment context : pas de field splitting

### Setup

```sh
unset IFS
A='a b'
```

| Command | Expected |
|---|---|
| `C=$A; ./test_exec "$C"` | `argv = ["./test_exec", "a b"]` |
| `./test_exec C=$A` | `argv = ["./test_exec", "C=a", "b"]` |
| `unset D; export D=$A; ./test_exec "$D"` | `argv = ["./test_exec", "a b"]` |
| `unset R; readonly R=$A; ./test_exec "$R"` | `argv = ["./test_exec", "a b"]` |

## 3.10 `IFS` modifié dans la même simple command

### Setup

```sh
unset IFS
X='a:b c'
```

| Command | Expected |
|---|---|
| `IFS=: ./test_exec $X` | `argv = ["./test_exec", "a:b", "c"]`; temp `IFS=:` does not affect expansion of words in same command |
| `IFS=:; ./test_exec $X` | `argv = ["./test_exec", "a", "b c"]` |

## 3.11 Interaction avec pathname expansion après field splitting

### Setup

```sh
unset IFS
mkdir -p fs_glob
: > fs_glob/a.c
: > fs_glob/b.c
: > fs_glob/a.h
P='fs_glob/*.c fs_glob/*.h'
```

| Command | Expected |
|---|---|
| `./test_exec $P` | `argv = ["./test_exec", "fs_glob/a.c", "fs_glob/b.c", "fs_glob/a.h"]` |
| `./test_exec "$P"` | `argv = ["./test_exec", "fs_glob/*.c fs_glob/*.h"]` |

## 3.12 Tests pièges utiles

### Setup

```sh
IFS=:
A=':'
B='::'
C='a::'
D='::a'
E='a:::b'
```

| Command | Expected |
|---|---|
| `./test_exec $A` | `argv = ["./test_exec", ""]` |
| `./test_exec $B` | `argv = ["./test_exec", "", ""]` |
| `./test_exec $C` | `argv = ["./test_exec", "a", ""]` |
| `./test_exec $D` | `argv = ["./test_exec", "", "", "a"]` |
| `./test_exec $E` | `argv = ["./test_exec", "a", "", "", "b"]` |

---

# 4. Tilde Expansion

Conventions :

```text
<HOME> = valeur actuelle de HOME
<VALID_USER> = un login valide sur la machine, par exemple root si disponible
<VALID_HOME> = home directory de <VALID_USER>
<INVALID_USER> = un login portable mais inexistant, par exemple __nosuchuser__
```

## Setup

À adapter selon la machine :

```sh
HOME='/tmp/home with spaces'
VALID_USER=root
INVALID_USER=__nosuchuser__
```

Attention : `VALID_USER=root` suppose que `root` existe. Le résultat attendu est alors `<VALID_HOME>`, souvent `/root` sur Linux, mais pas POSIX-garanti.

## Sans username, sans quote

| Command | Expected |
|---|---|
| `./test_exec ~` | `argv = ["./test_exec", "/tmp/home with spaces"]`; single field despite spaces in HOME |
| `./test_exec ~/dir` | `argv = ["./test_exec", "/tmp/home with spaces/dir"]` |
| `./test_exec ~/` | `argv = ["./test_exec", "/tmp/home with spaces/"]` |
| `./test_exec pre~` | `argv = ["./test_exec", "pre~"]`; no expansion, `~` not at word start |
| `./test_exec a/~` | `argv = ["./test_exec", "a/~"]`; no expansion |

## Sans username, avec quote

| Command | Expected |
|---|---|
| `./test_exec "~"` | `argv = ["./test_exec", "~"]` |
| `./test_exec '~/dir'` | `argv = ["./test_exec", "~/dir"]` |
| `./test_exec \~` | `argv = ["./test_exec", "~"]` |
| `./test_exec \~/dir` | `argv = ["./test_exec", "~/dir"]` |

## Avec username valide, sans quote

Remplacer `root` par un login valide si besoin.

| Command | Expected |
|---|---|
| `./test_exec ~root` | `argv = ["./test_exec", "<VALID_HOME>"]` |
| `./test_exec ~root/dir` | `argv = ["./test_exec", "<VALID_HOME>/dir"]` |
| `./test_exec pre~root` | `argv = ["./test_exec", "pre~root"]`; no expansion |
| `./test_exec a/~root` | `argv = ["./test_exec", "a/~root"]`; no expansion |

## Avec username valide, avec quote

| Command | Expected |
|---|---|
| `./test_exec "~root"` | `argv = ["./test_exec", "~root"]` |
| `./test_exec '~root/dir'` | `argv = ["./test_exec", "~root/dir"]` |
| `./test_exec \~root` | `argv = ["./test_exec", "~root"]` |
| `./test_exec ~"root"` | `unspecified POSIX` |

## Avec username invalide, sans quote

| Command | Expected |
|---|---|
| `./test_exec ~__nosuchuser__` | `unspecified POSIX` |
| `./test_exec ~__nosuchuser__/dir` | `unspecified POSIX` |

## Avec username invalide, avec quote

| Command | Expected |
|---|---|
| `./test_exec "~__nosuchuser__"` | `argv = ["./test_exec", "~__nosuchuser__"]` |
| `./test_exec '~__nosuchuser__/dir'` | `argv = ["./test_exec", "~__nosuchuser__/dir"]` |
| `./test_exec \~__nosuchuser__` | `argv = ["./test_exec", "~__nosuchuser__"]` |

## Assignment context : sans username

| Command | Expected |
|---|---|
| `T=~; ./test_exec "$T"` | `argv = ["./test_exec", "/tmp/home with spaces"]` |
| `T=~/dir; ./test_exec "$T"` | `argv = ["./test_exec", "/tmp/home with spaces/dir"]` |
| `T="~"; ./test_exec "$T"` | `argv = ["./test_exec", "~"]` |
| `T='~/dir'; ./test_exec "$T"` | `argv = ["./test_exec", "~/dir"]` |

## Assignment context : après `:`

POSIX permet plusieurs `tilde-prefixes` dans une assignment : après `=` et après chaque `:` non quoted.

| Command | Expected |
|---|---|
| `T=~/a:~/b; ./test_exec "$T"` | `argv = ["./test_exec", "/tmp/home with spaces/a:/tmp/home with spaces/b"]` |
| `T=prefix:~/b; ./test_exec "$T"` | `argv = ["./test_exec", "prefix:/tmp/home with spaces/b"]` |
| `T=~:~root; ./test_exec "$T"` | `argv = ["./test_exec", "/tmp/home with spaces:<VALID_HOME>"]` |
| `T=~:"~"; ./test_exec "$T"` | `argv = ["./test_exec", "/tmp/home with spaces:~"]` |

## Non-assignment : `:` ne déclenche pas tilde expansion

| Command | Expected |
|---|---|
| `./test_exec ~:~` | `unspecified POSIX`; tilde-prefix login name would be `:~` |
| `./test_exec x:~` | `argv = ["./test_exec", "x:~"]`; `~` not at word start |

## Declaration utility context

| Command | Expected |
|---|---|
| `unset TD; export TD=~/x; ./test_exec "$TD"` | `argv = ["./test_exec", "/tmp/home with spaces/x"]` |
| `unset TR; readonly TR=~/x; ./test_exec "$TR"` | `argv = ["./test_exec", "/tmp/home with spaces/x"]` |
| `unset TD2; export TD2="~/x"; ./test_exec "$TD2"` | `argv = ["./test_exec", "~/x"]` |

## Résumé matrice

```text
~                         => HOME
"~" / '~' / \~             => literal "~"

~valid                    => valid user's home
"~valid" / '~valid'        => literal "~valid"

~invalid                  => unspecified POSIX
"~invalid" / '~invalid'    => literal "~invalid"

assignment: A=~            => HOME
assignment: A=~:~valid     => HOME:valid user's home
assignment: A="~"          => literal "~"
```

---

# 5. Dollar-Single-Quotes `$'...'`

Point central : `$'...'` est une forme de quoting ; les backslash-escapes sont traités, puis le résultat est protégé comme du single-quoted, donc **pas de parameter expansion, pas de field splitting, pas de pathname expansion** sur le résultat.

Les caractères non imprimables sont donnés en **bytes hex**.

## Setup

```sh
unset IFS
A='hello world'
mkdir -p dsq
: > dsq/a.c
: > dsq/b.c
```

## Littéraux simples

| Command | Expected |
|---|---|
| `./test_exec $'abc'` | `argv = ["./test_exec", "abc"]` |
| `./test_exec $'a b c'` | `argv = ["./test_exec", "a b c"]`; no field splitting |
| `./test_exec $'*.c'` | `argv = ["./test_exec", "*.c"]`; no pathname expansion |
| `./test_exec dsq/$'*.c'` | `argv = ["./test_exec", "dsq/*.c"]`; generated `*` is quoted |

## Pas d’expansions internes

| Command | Expected |
|---|---|
| `./test_exec $'$A'` | `argv = ["./test_exec", "$A"]` |
| `./test_exec $'${A}'` | `argv = ["./test_exec", "${A}"]` |
| `./test_exec $'$(echo hi)'` | `argv = ["./test_exec", "$(echo hi)"]` |
| `./test_exec $'$((1+2))'` | `argv = ["./test_exec", "$((1+2))"]` |

## Concaténation avec autres parties du même word

| Command | Expected |
|---|---|
| `./test_exec pre$'MID'post` | `argv = ["./test_exec", "preMIDpost"]` |
| `./test_exec $'a b'X` | `argv = ["./test_exec", "a bX"]` |
| `./test_exec X$'a b'Y$'c d'Z` | `argv = ["./test_exec", "Xa bYc dZ"]` |

## Quotes et backslash échappés

| Command | Expected |
|---|---|
| `./test_exec $'don\'t'` | `argv = ["./test_exec", "don't"]` |
| `./test_exec $'a\\b'` | `argv = ["./test_exec", "a\\b"]`; `argv[1] bytes = 61 5c 62` |
| `./test_exec $'a\"b'` | `argv = ["./test_exec", "a\"b"]` |
| `./test_exec $'a"b'` | `argv = ["./test_exec", "a\"b"]` |

## Escapes classiques

| Command | Expected |
|---|---|
| `./test_exec $'a\nb'` | `argv[1] bytes = 61 0a 62` |
| `./test_exec $'a\tb'` | `argv[1] bytes = 61 09 62` |
| `./test_exec $'a\rb'` | `argv[1] bytes = 61 0d 62` |
| `./test_exec $'a\bb'` | `argv[1] bytes = 61 08 62` |
| `./test_exec $'a\fb'` | `argv[1] bytes = 61 0c 62` |
| `./test_exec $'a\vb'` | `argv[1] bytes = 61 0b 62` |
| `./test_exec $'a\ab'` | `argv[1] bytes = 61 07 62` |
| `./test_exec $'a\eb'` | `argv[1] bytes = 61 1b 62` |

## Octal escapes

| Command | Expected |
|---|---|
| `./test_exec $'\101'` | `argv = ["./test_exec", "A"]`; bytes `41` |
| `./test_exec $'\141'` | `argv = ["./test_exec", "a"]`; bytes `61` |
| `./test_exec $'a\040b'` | `argv = ["./test_exec", "a b"]`; bytes `61 20 62`; no field splitting |
| `./test_exec $'a\012b'` | `argv[1] bytes = 61 0a 62` |
| `./test_exec $'\101\102\103'` | `argv = ["./test_exec", "ABC"]`; bytes `41 42 43` |

## Hex escapes

| Command | Expected |
|---|---|
| `./test_exec $'\x41'` | `argv = ["./test_exec", "A"]`; bytes `41` |
| `./test_exec $'\x61'` | `argv = ["./test_exec", "a"]`; bytes `61` |
| `./test_exec $'a\x20b'` | `argv = ["./test_exec", "a b"]`; bytes `61 20 62` |
| `./test_exec $'a\x2fb'` | `argv = ["./test_exec", "a/b"]`; bytes `61 2f 62` |
| `./test_exec $'a\x0ab'` | `argv[1] bytes = 61 0a 62` |

## Control escapes `\cX`

À tester si vous avez implémenté `\cX`.

| Command | Expected |
|---|---|
| `./test_exec $'\cA'` | `argv[1] bytes = 01` |
| `./test_exec $'\cZ'` | `argv[1] bytes = 1a` |
| `./test_exec $'\c['` | `argv[1] bytes = 1b` |
| `./test_exec $'a\cIb'` | `argv[1] bytes = 61 09 62`; Ctrl-I = tab |

Évite `\c@` / NUL pour les tests de conformité shell, parce qu’un NUL dans une string C / shell word n’est pas représentable proprement.

## Plusieurs escapes dans le même argument

| Command | Expected |
|---|---|
| `./test_exec $'A\nB\tC'` | `argv[1] bytes = 41 0a 42 09 43` |
| `./test_exec $'\101\x42\103'` | `argv = ["./test_exec", "ABC"]`; bytes `41 42 43` |
| `./test_exec $'quote:\' backslash:\\ tab:\t end'` | `argv[1] = "quote:' backslash:\\ tab:\t end"`; bytes include `27`, `5c`, `09` |

## Interaction avec field splitting

| Command | Expected |
|---|---|
| `./test_exec $'a b' c` | `argv = ["./test_exec", "a b", "c"]` |
| `IFS=:; X=$'a:b:c'; ./test_exec $X` | `argv = ["./test_exec", "a", "b", "c"]`; later unquoted `$X` is split |
| `IFS=:; ./test_exec $'a:b:c'` | `argv = ["./test_exec", "a:b:c"]`; direct `$'...'` result is quoted |

## Interaction avec pathname expansion

| Command | Expected |
|---|---|
| `./test_exec $'dsq/*.c'` | `argv = ["./test_exec", "dsq/*.c"]` |
| `P=$'dsq/*.c'; ./test_exec $P` | `argv = ["./test_exec", "dsq/a.c", "dsq/b.c"]`; stored pattern later expanded via unquoted `$P` |
| `P=$'dsq/*.c'; ./test_exec "$P"` | `argv = ["./test_exec", "dsq/*.c"]` |

## Assignment context

| Command | Expected |
|---|---|
| `D=$'a b'; ./test_exec "$D"` | `argv = ["./test_exec", "a b"]` |
| `D=$'a\nb'; ./test_exec "$D"` | `argv[1] bytes = 61 0a 62` |
| `export E=$'x y'; ./test_exec "$E"` | `argv = ["./test_exec", "x y"]` |
| `readonly R=$'x\ty'; ./test_exec "$R"` | `argv[1] bytes = 78 09 79` |

## En position command name

| Command | Expected |
|---|---|
| `$'./test_exec' ok` | `argv = ["./test_exec", "ok"]` |
| `$'./test_exec arg'` | `command not found`, status `127`; one field containing space, not split |
| `CMD=$'./test_exec arg'; $CMD end` | `argv = ["./test_exec", "arg", "end"]`; later unquoted `$CMD` is split |
| `CMD=$'./test_exec arg'; "$CMD" end` | `command not found`, status `127` |

## `$'...'` dans quotes normales

| Command | Expected |
|---|---|
| `./test_exec "$'a\nb'"` | `argv = ["./test_exec", "$'a\\nb'"]`; inside double-quotes, `$'...'` is literal text |
| `./test_exec '$'\''a\nb'\'''` | `argv = ["./test_exec", "$'a\\nb'"]`; literal construction |

## Cas unspecified / hors scope

Ne pas utiliser comme tests stricts de conformité :

| Command | Expected |
|---|---|
| `./test_exec $'\q'` | `unspecified / dépend de votre politique` |
| `./test_exec $'\x'` | `unspecified / erreur selon votre politique` |
| `./test_exec $'\400'` | `hors plage 8-bit / dépend de votre politique` |
| `./test_exec $'\0'` | `à éviter : NUL non représentable proprement dans argv C` |

## Mini matrice

```text
$'abc'          => abc
$'a b'          => one field "a b"
$'$A'           => literal "$A"
$'*.c'          => literal "*.c"
$'a\nb'         => bytes 61 0a 62
$'a\tb'         => bytes 61 09 62
$'a\\b'         => bytes 61 5c 62
$'don\'t'       => don't
$'\101'         => A
$'\x41'         => A
$'\cA'          => byte 01, if implemented
pre$'x'post     => prexpost
$'./test_exec'  => usable as command name
```
