# WIP

1. *SYMBOLS*
`SYM_DOLPAREN` (terminal)
`SYM_cmd_sub` (non-terminal)
2. *RULES*
```
start	-> cmd_sub // NO IT COULD BE ANYWHERE ?!
cmd_sub	-> SYM_DOLPAREN coumpound_list ')'
```
3. call dans `rules_build()`
4. Add another initial `lr_state` with `RULE_START_2` in `build_initial_lr_state()`
5. Add `ACTION_ACCEPT` on all symbols when reducing `RULE_CMD_SUB_1`
```c
// ERR_NO / ERR_LR_CONFLICT
static t_error	add_cmd_sub_accepts(
					t_lr_machine *machine,
					size_t lr_state_id,
					t_rule_state rule_state)
{
	t_symbol	symbol;
	t_action	*action;

	symbol = 0;
	while (symbol <= SYM_TERMINAL_MAX)
	{
		action = &machine->actions[lr_state_id][symbol];
		if (action->type != ACTION_ERROR)
			return (print_conflict(action, lr_state_id, symbol,
					ACTION_ACCEPT, rule_state.rule_id));
		action->type = ACTION_ACCEPT;
		action->payload = rule_state.rule_id;
		symbol++;
	}
	return (error(ERR_NO));
}
```
and priorize this `ACTION_ACCEPT` over `RULE_START_1`'s `ACTION_ACCEPT` in `add_reduces_and_accept()`
```c
	if (rule_state.rule_id == RULE_CMD_SUB_1)
		return (add_cmd_sub_accepts(machine, lr_state_id, rule_state));
```
6. *IF parser creates itself the fake SYM_DOLPAREN token*
- `if (parser->search_cmd_sub_end == true && parser->token_pool.len == 0 && parser->lookahead_raw_symbol == SYM_LPARENTHESIS) => parser->lookahead_raw_symbol = SYM_DOLPAREN` in `parser_read_next_symbol()`
⚠️ Step `5.` `ACTION_REDUCE` instead of `ACTION_ACCEPT` + `ACTION_ACCEPT` on all `SYMBOLS` when `RULE_START_2.pos == rhs_len - 1`

- rewrite `RULE_CMD_SUB`:
	- `parser` génère un faux `SYM_DOLPAREN` ou `scanner` le génère ?
		- lors de l'init du nested `scanner` ?
		- garder un vrai format + input dans le `token`
- Si `SYM_EOF` alors que construction en attente (`SYM_SHIFT possible ?`)
	- call `scanner_get_next_token()` avec `continuation == true`
	- drop `SYM_EOF` (lookahead) + `SYM_NEWLINE` (`item_stack`) précédents

🚨 Don't `accept` on `EOF` while parsing `cmd_sub_end` !!

- rename `params` to `env`
- ⚠️ `qualify_2()`
- `shell`:
	- process `ENV` at startup:
		- See `ENVIRONMENT VARIABLES` -> `ENV` section in [sh](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/sh.html).
		- `If the expanded value of ENV is not an absolute pathname, the results are unspecified` ([sh](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/sh.html) -> `ENVIRONMENT VARIABLES` -> `ENV`)
- `builtins`:
	- `continue`
	- `break`
	- `return`
	- `kill`
- `options`:
	- handle all options properly
- `runner-executor`:
	- `exec` specific flow
	- `command` specific flow
