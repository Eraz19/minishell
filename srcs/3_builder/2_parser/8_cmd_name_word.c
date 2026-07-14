#include "parser_type.h"
#include "parser.h"
#include "lr_machine_type.h"
#include "lr_state_type.h"
#include "rule_state_type.h"
#include "goto.h"
#include <stdlib.h>
# include <assert.h>	// DEBUG

// @ret ERR_LIBC
static inline t_error	get_lr_state_ids_from_stack(
							const t_parser *parser,
							t_vector *dst)
{
	size_t						i;
	const t_parser_item	*item;

	if (!vector_init(dst, sizeof(size_t), parser->stack.len))
		return (error_sys());
	i = 0;
	while (i < parser->stack.len)
	{
		item = &((t_parser_item *)parser->stack.data)[i];
		if (!vector_push(dst, &item->lr_state_id))
			return (vector_free(dst, NULL), error_sys());
		i++;
	}
	return (error(ERR_NO));
}

static inline bool	state_expects_cmd_name_or_word(
						const t_lr_machine *machine,
						size_t lr_state_id)
{
	const t_lr_state	*state;
	const t_rule_state	*item;
	const t_rule		*rule;
	size_t				i;

	state = &((t_lr_state *)machine->lr_states.data)[lr_state_id];
	i = 0;
	while (i < state->len)
	{
		item = &((t_rule_state *)state->data)[i];
		rule = &machine->rules[item->rule_id];
		if ((rule->lhs == SYM_cmd_name || rule->lhs == SYM_cmd_word)
			&& item->pos < rule->rhs_len
			&& rule->rhs[item->pos] == SYM_WORD)
			return (true);
		i++;
	}
	return (false);
}

// @ret ERR_PARSER_INVALID_STATE / ERR_PARSER_EMPTY_GOTO / ERR_LIBC
static inline t_error	simulate_reduction(
							const t_lr_machine *machine,
							t_vector *lr_state_ids,
							size_t rule_id)
{
	const t_rule	*rule;
	size_t			lr_state_from;
	size_t			lr_state_to;

	rule = &machine->rules[rule_id];
	if (rule->rhs_len >= lr_state_ids->len)
		return (error_print(error(ERR_PARSER_INVALID_STATE), "parser",
			"unable to simulate reduction", NULL, NULL));
	lr_state_ids->len -= rule->rhs_len;
	lr_state_from = ((size_t *)lr_state_ids->data)[lr_state_ids->len - 1];
	lr_state_to = machine->gotos[lr_state_from][rule->lhs - SYM_NON_TERMINAL_MIN];
	if (lr_state_to == GOTO_EMPTY)
		return (error_print(error(ERR_PARSER_EMPTY_GOTO), "parser",
			"unable to simulate reduction", NULL, NULL));
	if (!vector_push(lr_state_ids, &lr_state_to))
		return (error_sys());
	return (error(ERR_NO));
}

static inline t_error	free_and_return(t_vector *vector)
{
	vector_free(vector, NULL);
	return (error(ERR_NO));
}

t_error	parser_can_next_token_be_a_cmd_name_or_word(
			const t_parser *parser,
			const t_lr_machine *machine,
			bool *dst)
{
	t_vector		lr_state_ids;
	size_t			lr_state_id;
	const t_action	*action;
	t_error			err;

	assert(parser != NULL);
	assert(machine != NULL);
	assert(dst != NULL);
	err = get_lr_state_ids_from_stack(parser, &lr_state_ids);
	if (err.type)
		return (err);
	while (true)
	{
		lr_state_id = ((size_t *)lr_state_ids.data)[lr_state_ids.len - 1];
		if (state_expects_cmd_name_or_word(machine, lr_state_id))
			return (*dst = true, free_and_return(&lr_state_ids));
		action = &machine->actions[lr_state_id][SYM_WORD];
		if (action->type != ACTION_REDUCE)
			return (*dst = false, free_and_return(&lr_state_ids));
		err = simulate_reduction(machine, &lr_state_ids, action->payload);
		if (err.type)
			break ;
	}
	vector_free(&lr_state_ids, NULL);
	return (err);
}
