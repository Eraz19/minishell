# Parser/rules

2. Ajouter un (plusieurs ?!) pointeur de fonction dans la struct `t_rule` pour y linker la/les fonction à trigger lors de la réduction (word specific rules, trigger du here_doc mode du lexer...)
3. Ajouter les protoypes des initializers publics dans `parser_rules.h`
4. Appeler les initializers dans `1_parser_rules.c`
5. Implémenter les `items`
6. Implémenter `closure()`
...
