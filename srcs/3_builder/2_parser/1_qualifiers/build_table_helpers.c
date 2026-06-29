#include "lr_state_type.h"
#include "qualifiers_priv.h"
# include <assert.h>	// DEBUG

bool	should_apply_qualifier_word(
		const t_lr_machine *machine,
		size_t lr_state_id)
{
	assert(machine != NULL);
	return (machine->actions[lr_state_id][SYM_WORD].type != ACTION_ERROR);
}

bool	should_apply_qualifier_1(
			const t_lr_machine *machine,
			size_t lr_state_id)
{
	assert(machine != NULL);
	if (machine->actions[lr_state_id][SYM_WORD].type != ACTION_ERROR)
		return (false);
	if (machine->actions[lr_state_id][SYM_NAME].type != ACTION_ERROR)
		return (false);
	if (machine->actions[lr_state_id][SYM_ASSIGNMENT_WORD].type != ACTION_ERROR)
		return (false);
	return (true);
}

bool	rule_is_at_target(
			const t_rule_state *rule_state,
			t_rule_id rule_id,
			size_t target_pos)
{
	assert(rule_state != NULL);
	return (rule_state->rule_id == rule_id && rule_state->pos == target_pos);
}

t_qualifier_id	qualifier_default_id(
					const t_lr_machine *machine,
					const t_rule_state *rule_state)
{
	const t_rule	*rule;

	assert(machine != NULL);
	assert(rule_state != NULL);
	rule = &machine->rules[rule_state->rule_id];
	if (rule_state->pos >= rule->rhs_len)
		return (QUALIFIER_NONE);
	if (rule->rhs[rule_state->pos] == SYM_WORD)
		return (QUALIFIER_WORD);
	return (QUALIFIER_NONE);
}

t_qualifier_id	qualifier_6_choose_variant(
					const t_lr_machine *machine,
					size_t lr_state_id)
{
	t_lr_state		*lr_state;
	t_rule_state	*rule_state;
	const t_rule	*rule;
	size_t			i;

	assert(machine != NULL);
	lr_state = &((t_lr_state *)machine->lr_states.data)[lr_state_id];
	i = 0;
	while (i < lr_state->len)
	{
		rule_state = &((t_rule_state *)lr_state->data)[i];
		rule = &machine->rules[rule_state->rule_id];
		if (rule_state->pos < rule->rhs_len)
		{
			if (rule->lhs == SYM_case_clause && rule->rhs[rule_state->pos] == SYM_in)
				return (QUALIFIER_6A);
			else if (rule->lhs == SYM_for_clause && rule->rhs[rule_state->pos] == SYM_in)
				return (QUALIFIER_6B);
			else if (rule->lhs == SYM_for_clause && rule->rhs[rule_state->pos] == SYM_do_group)
				return (QUALIFIER_6B);
		}
		i++;
	}
	return (QUALIFIER_NONE);
}
