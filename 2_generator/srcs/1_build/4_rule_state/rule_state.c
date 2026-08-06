/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rule_state.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:43:19 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 12:13:58 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generator_rule_state.h"

bool	rule_state_equal(const t_rule_state *a, const t_rule_state *b)
{
	return (a->rule_id == b->rule_id
		&& a->pos == b->pos
		&& a->lookahead == b->lookahead);
}

bool	rule_state_is_complete(
			const t_rule *rules,
			const t_rule_state *rule_state)
{
	return (rule_state->pos >= rules[rule_state->rule_id].rhs_len);
}

t_symbol	rule_state_next_symbol(
				const t_rule *rules,
				const t_rule_state *rule_state)
{
	if (rule_state_is_complete(rules, rule_state))
		return (SYM_error);
	return (rules[rule_state->rule_id].rhs[rule_state->pos]);
}
