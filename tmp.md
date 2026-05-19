# Variables

Les tests doivent vérifier, pour chaque test :
- dans le DUMP VARIABLES: présence/absence + valeur + attributs (exported et readonly)
- dans le DUMP PARAMS: présence/absence + valeur

Les tests ne doivent PAS contenir d'options ni d'opérandes puisqu'on teste ici les VARIABLES UNIQUEMENT

## Cas basique
1. `envp` vide :
- IFS initialisé à <space><newline><tab> (export=false readonly=false)
- PPID initialisé à l'équivalent de echo $$ (export=false readonly=false)
- PWD initialisé à l'équivalent de pwd -P (export=false readonly=false)
- PS1 initialisé à '$ ' (export=false readonly=false)
- PS2 initialisé à '> ' (export=false readonly=false)
- PS4 initialisé à '+ ' (export=false readonly=false)
- Aucune autre variable dans les DUMPS

## IFS
2. `envp` avec IFS=<space><newline><tab> :
- IFS initialisé à <space><newline><tab> (export=true readonly=false)
3. `envp` avec IFS='abc'
- IFS initialisé à <space><newline><tab> (export=true readonly=false)

## PPID
4. `envp` avec PPID="$(echo $$)"
- PPID initialisé à l'équivalent de echo $$ (export=true readonly=false)
5. `envp` avec PPID='abc'
- PPID initialisé à l'équivalent de echo $$ (export=true readonly=false)

## PWD
6. `envp` avec PWD valide avec symlink :
- PWD non modifié (export=true readonly=false)
7. `envp` avec PWD invalide car contient un dot component :
- PWD initialisé à l'équivalent de pwd -P (export=true readonly=false)
8. `envp` avec PWD invalide car contient un dot-dot component :
- PWD initialisé à l'équivalent de pwd -P (export=true readonly=false)

## PS1/PS2/PS4
9. `envp` avec PS1, PS2 et PS4 :
- PS1, PS2 et PS4 non modifiés (export=true readonly=false)

## Autres variables

10. Nom valide avec valeur:
- La variable doit être présente dans les dump avec la bonne valeur (export=true readonly=false)
11. Nom valide sans valeur:
- La variable doit être présente dans les dump avec la valeur '' (export=true readonly=false)

---

# OLD TESTS

--- OPTIONS / PARAMS '-' getter ---

Test O01: env -i ./minishell                                     ⇢ options                   ⇢ defaults to stdin mode .............. ✔
Test O02: env -i ./minishell -c 'echo hello'                     ⇢ options                   ⇢ sets command_string mode ............ ✔
Test O03: env -i ./minishell -s                                  ⇢ options                   ⇢ explicit stdin mode ................. ✔
Test O04: env -i ./minishell -a -c ':'                           ⇢ options                   ⇢ sets -a ............................. ✔
Test O05: env -i ./minishell -b -c ':'                           ⇢ options                   ⇢ sets -b ............................. ✔
Test O06: env -i ./minishell -C -c ':'                           ⇢ options                   ⇢ sets -C ............................. ✔
Test O07: env -i ./minishell -e -c ':'                           ⇢ options                   ⇢ sets -e ............................. ✔
Test O08: env -i ./minishell -f -c ':'                           ⇢ options                   ⇢ sets -f ............................. ✔
Test O09: env -i ./minishell -h -c ':'                           ⇢ options                   ⇢ sets -h ............................. ✔
Test O10: env -i ./minishell -i -c ':'                           ⇢ options                   ⇢ sets -i ............................. ✔
Test O11: env -i ./minishell -m -c ':'                           ⇢ options                   ⇢ sets -m ............................. ✔
Test O12: env -i ./minishell -n -c ':'                           ⇢ options                   ⇢ sets -n ............................. ✔
Test O13: env -i ./minishell -u -c ':'                           ⇢ options                   ⇢ sets -u ............................. ✔
Test O14: env -i ./minishell -v -c ':'                           ⇢ options                   ⇢ sets -v ............................. ✔
Test O15: env -i ./minishell -x -c ':'                           ⇢ options                   ⇢ sets -x ............................. ✔
Test O16: env -i ./minishell -o ignoreeof -c ':'                 ⇢ options                   ⇢ sets -o ignoreeof ................... ✔
Test O17: env -i ./minishell -o nolog -c ':'                     ⇢ options                   ⇢ sets -o nolog ....................... ✔
Test O18: env -i ./minishell -o pipefail -c ':'                  ⇢ options                   ⇢ sets -o pipefail .................... ✔
Test O19: env -i ./minishell -o vi -c ':'                        ⇢ options                   ⇢ sets -o vi .......................... ✔
Test O20: env -i ./minishell -o noclobber -c ':'                 ⇢ options                   ⇢ sets -o noclobber ................... ✔
Test O21: env -i ./minishell -o notify -c ':'                    ⇢ options                   ⇢ sets -o notify ...................... ✔
Test O22: env -i ./minishell -o nounset -c ':'                   ⇢ options                   ⇢ sets -o nounset ..................... ✔
Test O23: env -i ./minishell -e +e -c ':'                        ⇢ options                   ⇢ +e overrides -e ..................... ✔
Test O24: env -i ./minishell +e -e -c ':'                        ⇢ options                   ⇢ last option wins .................... ✔
Test O25: env -i ./minishell -o pipefail +o pipefail -c ':'      ⇢ options                   ⇢ +o reverses -o ...................... ✔
Test O26: env -i ./minishell -axv -c ':'                         ⇢ options                   ⇢ sets grouped short options .......... ✔
Test O27: env -i ./minishell -axv +av -c ':'                     ⇢ options                   ⇢ unsets grouped short options ........ ✔
Test O28: env -i ./minishell -efux +fu -x -c ':'                 ⇢ options                   ⇢ keeps final short state ............. ✔
Test O29: env -i ./minishell -o nounset +o nounset -o nounset -c ':' ⇢ options                   ⇢ keeps final -o/+o state ......... ✔
Test O30: env -i ./minishell -C +C -o noclobber -c ':'           ⇢ options                   ⇢ merges short and -o aliases ......... ✔

--- SPECIALS / PARAMS getter ---

Test S01: env -i ./minishell -c ':'                              ⇢ specials                  ⇢ initializes $? to 0 ................. ✔
Test S02: env -i ./minishell -c ':'                              ⇢ specials                  ⇢ abstracts $! unset .................. ✔
Test S03: env -i ./minishell -c ':'                              ⇢ specials                  ⇢ keeps $$ consistent ................. ✔
Test S04: env -i ./minishell                                     ⇢ source                    ⇢ stdin source is NULL ................ ✔
Test S05: env -i ./minishell -c 'echo hello'                     ⇢ source                    ⇢ stores command_string ............... ✔
Test S06: env -i ./minishell -s                                  ⇢ source                    ⇢ explicit stdin source is NULL ....... ✔
Test S07: env -i ./minishell                                     ⇢ specials                  ⇢ sets $0 to argv[0] .................. ✔
Test S08: env -i ./minishell -c ':'                              ⇢ specials                  ⇢ keeps argv[0] as $0 ................. ✔
Test S09: env -i ./minishell -c ':' cmd_name                     ⇢ specials                  ⇢ uses command_name as $0 ............. ✔
Test S10: env -i ./minishell -c ':' -cmd                         ⇢ specials                  ⇢ allows dash command_name ............ ✔
Test S11: env -i ./minishell script.sh                           ⇢ specials                  ⇢ uses command_file as $0 ............. ✔
Test S12: env -i ./minishell -- +script.sh                       ⇢ specials                  ⇢ protects + command_file ............. ✔

--- POSITIONALS / PARAMS getter ---

Test P01: env -i ./minishell -c ':'                              ⇢ positionals               ⇢ starts with zero args ............... ✔
Test P02: env -i ./minishell -c ':' cmd a b                      ⇢ positionals               ⇢ loads args after command_name ....... ✔
Test P03: env -i ./minishell -c ':' cmd -e +x                    ⇢ positionals               ⇢ keeps signed operands ............... ✔
Test P04: env -i ./minishell -s a b                              ⇢ positionals               ⇢ loads -s arguments .................. ✔
Test P05: env -i ./minishell script.sh a b                       ⇢ positionals               ⇢ loads command_file args ............. ✔
Test P06: env -i ./minishell - a b                               ⇢ positionals               ⇢ ignores single hyphen operand ....... ✖
    missing: SPECIAL 0=./minishell
    missing: PARAMS 0='./minishell'
    missing: POSITIONALS #=2
    missing: PARAMS #='2'
    missing: POSITIONALS[0] 0='a'
    missing: PARAMS 1='a'
    missing: POSITIONALS[0] 1='b'
    missing: PARAMS 2='b'
    Dump: /Users/gui/repos/minishell/tests/logs/test_init.4/test_P06.log

✖ 1 / 59 tests failed
⚠ Logs kept in: /Users/gui/repos/minishell/tests/logs/test_init.4
make: *** [test] Error 1

# Alex

Bon, j'ai passé une **ÉTERNITÉ** à réussir à faire pondre des tests pertinents, exhaustifs et qui fonctionnent à ChatGPT (23 versions et 4h d'allers-retours 🫠) pour mon module `params` qui se charge de parser et initialiser les `variables`, `options`, `special parameters` et `positional arguments` au lancement du shell.

Je pense que ça couvre tous les cas définis par POSIX mais dans le doute je suis chaud pour que tu balances le script de test dans la gueule de Claude pour qu'il check s'il manque pas des tests importants à faire 🙏 (`tests/test_init.zsh`, je te le mets en PJ pour que t'aies pas besoin de `pull`).

Pour ce qui est de l'orga du dossier `tests` je suis parti là-dessus :
- `tests/`: contient les scripts de tests (exécutables par `make test`)
- `tests/fixtures/<nom_du_testeur>`: contient les fixtures nécessaires aux testeurs (supprimé par `make clean`)
- `tests/logs/<nom_du_testeur>.<itération>`: contient les logs de `minishell` qui ont été output pendant les tests (supprimé par `make clean`)

Si ça te va tu peux ajouter tes scripts de test là-dedans, la commande `make test` les découvrira et les lancera tous automatiquement.

Pour faciliter l'automatisation des tests personnellement je fais des "dump" de la mémoire en texte brut sur stdout pour que le script puisse facilement les parser, on pourra en parler si besoin mais je pense que c'est une solution simple et efficace.

Sur ce, bonne nuit 🤜🤛