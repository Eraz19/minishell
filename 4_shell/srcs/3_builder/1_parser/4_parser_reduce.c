#include "parser_priv.h"
#include "grammar_gotos.h"
#include "cst.h"
# include <assert.h>	// DEBUG

static inline t_error	parser_new_lr_state(
							const t_parser *parser,
							const t_lr_rule *rule,
							size_t *dst)
{
	const t_parser_item_stack	*stack;
	size_t						previous_item_id;
	t_parser_item				*previous_item;
	size_t						lr_state_from;
	size_t						lr_state_to;

	stack = &parser->item_stack;
	previous_item_id = stack->len - rule->rhs_len - 1;
	previous_item = &((t_parser_item *)stack->data)[previous_item_id];
	lr_state_from = previous_item->lr_state_id;
	lr_state_to = parser->tables->gotos[
		lr_state_from * GOTO_COL_COUNT + rule->lhs - SYM_NON_TERMINAL_MIN];
	if (lr_state_to == GOTO_EMPTY)
		return (error_print(
			error(ERR_PARSER_EMPTY_GOTO), "parser", NULL, NULL));
	*dst = lr_state_to;
	return (error(ERR_NO));
}

static inline size_t	parser_tokens_count_sum(
							const t_parser_item *rhs_items,
							size_t count)
{
	size_t				i;
	const t_parser_item	*item;
	size_t				token_count;

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

static inline t_error	parser_replace_items(
							t_parser *parser,
							size_t count,
							const t_parser_item	*item)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		if (!vector_pop(&parser->item_stack, NULL))
			return (parser_internal_error(error_sys()));
		i++;
	}
	if (!vector_push(&parser->item_stack, item))
		return (parser_internal_error(error_sys()));
	return (error(ERR_NO));
}

t_error	parser_reduce(t_parser *parser, size_t rule_id)
{
	const t_lr_rule	*rule;
	size_t			rhs_start;
	t_parser_item	*rhs;
	t_parser_item	item;
	t_error			err;

	assert(parser != NULL);
	rule = &parser->tables->rules[rule_id];
	rhs_start = parser->item_stack.len - rule->rhs_len;
	rhs = &((t_parser_item *)parser->item_stack.data)[rhs_start];
	item.symbol = rule->lhs;
	err = parser_new_lr_state(parser, rule, &item.lr_state_id);
	if (err.type)
		return (err);
	item.tokens_start_id = parser->lookahead_id;
	if (rule->rhs_len > 0)
		item.tokens_start_id = rhs[0].tokens_start_id;
	item.tokens_count = parser_tokens_count_sum(rhs, rule->rhs_len);
	item.cst_node = NULL;
	err = cst_node_new(&item, rhs, rule->rhs_len, (t_rule_id)rule_id);
	if (err.type == ERR_NO)
		err = parser_process_reduce_hooks(parser, rule_id, &item, rhs);
	if (err.type == ERR_NO)
		err = parser_replace_items(parser, rule->rhs_len, &item);
	if (err.type)
		cst_node_free(&item.cst_node);
	return (err);
}
