/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_qualifiers_build_helpers.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:16:24 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 18:45:30 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generator_qualifiers_priv.h"

bool	qualifier_should_apply_word(
			const t_action *actions,
			size_t lr_state_id)
{
	size_t	index;

	index = lr_state_id * (SYM_TERMINAL_MAX + 1) + SYM_WORD;
	return (actions[index].type != ACTION_ERROR);
}

bool	qualifier_should_apply_1(
			const t_action *actions,
			size_t lr_state_id)
{
	size_t	row_offset;

	row_offset = lr_state_id * (SYM_TERMINAL_MAX + 1);
	if (actions[row_offset + SYM_WORD].type != ACTION_ERROR)
		return (false);
	if (actions[row_offset + SYM_NAME].type != ACTION_ERROR)
		return (false);
	if (actions[row_offset + SYM_ASSIGNMENT_WORD].type != ACTION_ERROR)
		return (false);
	return (true);
}

bool	qualifier_rule_is_at_target(
			const t_rule_state *rule_state,
			t_rule_id rule_id,
			size_t target_pos)
{
	return (rule_state->rule_id == rule_id && rule_state->pos == target_pos);
}

t_qualifier_id	qualifier_default_id(
					const t_rule rules[RULE_COUNT],
					const t_rule_state *rule_state)
{
	const t_rule	*rule;

	rule = &rules[rule_state->rule_id];
	if (rule_state->pos >= rule->rhs_len)
		return (QUALIFIER_NONE);
	else if (rule->rhs[rule_state->pos] == SYM_WORD)
		return (QUALIFIER_WORD);
	return (QUALIFIER_NONE);
}

t_qualifier_id	qualifier_6_choose_variant(
					const t_rule rules[RULE_COUNT],
					const t_lr_state *lr_state)
{
	const t_rule_state	*rule_state;
	const t_rule		*rule;
	size_t				i;

	i = 0;
	while (i < lr_state->len)
	{
		rule_state = &((const t_rule_state *)lr_state->data)[i];
		rule = &rules[rule_state->rule_id];
		if (rule_state->pos < rule->rhs_len)
		{
			if (rule->lhs == SYM_case_clause
				&& rule->rhs[rule_state->pos] == SYM_in)
				return (QUALIFIER_6A);
			else if (rule->lhs == SYM_for_clause
				&& rule->rhs[rule_state->pos] == SYM_in)
				return (QUALIFIER_6B);
			else if (rule->lhs == SYM_for_clause
				&& rule->rhs[rule_state->pos] == SYM_do_group)
				return (QUALIFIER_6B);
		}
		i++;
	}
	return (QUALIFIER_NONE);
}
