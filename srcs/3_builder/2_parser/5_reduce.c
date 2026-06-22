#include "parser_priv.h"
#include "goto.h"

static inline t_error	parser_new_lr_state(
	t_parser *parser,
	t_lr_machine *machine,
	t_rule *rule,
	size_t *dst)
{
	t_parser_stack			*stack;
	size_t			previous_item_id;
	t_parser_stack_item	*previous_item;
	size_t			lr_state_from;
	size_t			lr_state_to;

	stack = &parser->stack;
	previous_item_id = stack->len - rule->rhs_len - 1;
	previous_item = &((t_parser_stack_item *)stack->data)[previous_item_id];
	lr_state_from = previous_item->lr_state_id;
	lr_state_to = machine->gotos[lr_state_from][rule->lhs - SYM_NON_TERMINAL_MIN];
	if (lr_state_to == GOTO_EMPTY)
		return (error_print(error(ERR_PARSER_EMPTY_GOTO), "parser", NULL, NULL));
	*dst = lr_state_to;
	return (error(ERR_NO));
}

static inline size_t	parser_tokens_count_sum(
	t_parser_stack_item *rhs_items,
	size_t count)
{
	size_t			i;
	t_parser_stack_item	*item;
	size_t			token_count;

	token_count = 0;
	i = 0;
	while (i < count)
	{
		item = &rhs_items[i];
		token_count += item->tokens_count;
		i++;
	}
	return (token_count);
}

static t_error	parser_replace_items(
	t_parser *parser,
	size_t count,
	t_parser_stack_item *item)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		if (!parser_stack_pop(&parser->stack, NULL))
			return (parser_internal_error());
		i++;
	}
	if (!parser_stack_push(&parser->stack, item))
		return (parser_internal_error());
	return (error(ERR_NO));
}

# include <stdio.h>
t_error	parser_reduce(t_parser *parser, t_lr_machine *machine, size_t rule_id)
{
	t_rule			*rule;
	size_t			rhs_start;
	t_parser_stack_item	*rhs;
	t_parser_stack_item	item;
	t_error			err;

	rule = &machine->rules[rule_id];
	rhs_start = parser->stack.len - rule->rhs_len;
	rhs = &((t_parser_stack_item *)parser->stack.data)[rhs_start];
	item.symbol = rule->lhs;
	err = parser_new_lr_state(parser, machine, rule, &item.lr_state_id);
	if (err.type != ERR_NO)
		return (err);
	item.tokens_start_id = parser->lookahead_id;
	if (rule->rhs_len > 0)
		item.tokens_start_id = rhs[0].tokens_start_id;
	item.tokens_count = parser_tokens_count_sum(rhs, rule->rhs_len);
	printf("[PARSER] REDUCE rule=%zu lhs=%s goto=%zu rhs_len=%zu token_start=%zu token_count=%zu\n",
		rule_id,
		symbol_to_string(item.symbol),
		item.lr_state_id,
		rule->rhs_len,
		item.tokens_start_id,
		item.tokens_count);
	for (size_t i = 0; i < rule->rhs_len; i++)
	{
		printf("[PARSER] RHS[%zu] symbol=%s state=%zu token_start=%zu token_count=%zu\n",
			i,
			symbol_to_string(rhs[i].symbol),
			rhs[i].lr_state_id,
			rhs[i].tokens_start_id,
			rhs[i].tokens_count);
	}
	item.cst_node = NULL;
	err = error(ERR_NO);
	if (rule->hook)
		err = rule->hook(rhs, rule->rhs_len, parser);
	if (err.type == ERR_NO)
		err = parser_cst_node_new(&item, rhs, rule->rhs_len, &item.cst_node);
	if (err.type == ERR_NO)
		err = parser_replace_items(parser, rule->rhs_len, &item);
	if (err.type != ERR_NO)
		parser_cst_node_free(&item.cst_node);
	return (err);
}
