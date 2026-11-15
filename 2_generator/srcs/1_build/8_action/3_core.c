/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_core.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:15:31 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 12:15:32 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generator_actions.h"
#include "generator_actions_priv.h"
#include "generator_transitions.h"
#include "generator_lr_state.h"

static inline bool	add_shifts(
						const t_transition *transitions,
						size_t transition_count,
						t_action *actions)
{
	size_t		i;
	size_t		lr_state_id;
	t_symbol	symbol;
	t_action	*action;
	size_t		payload;

	i = 0;
	while (i < transition_count)
	{
		lr_state_id = transitions[i].from_lr_state_id;
		symbol = transitions[i].symbol;
		if (symbol <= SYM_TERMINAL_MAX)
		{
			action = &actions[lr_state_id * (SYM_TERMINAL_MAX + 1) + symbol];
			payload = transitions[i].to_lr_state_id;
			if (action_is_conflict(action, ACTION_SHIFT, payload))
				return (false);
			action->type = ACTION_SHIFT;
			action->payload = payload;
		}
		i++;
	}
	return (true);
}

static inline bool	add_reduces(
						t_action *actions,
						size_t lr_state_id,
						const t_rule_state *rule_state)
{
	t_symbol	symbol;
	t_action	*action;
	size_t		payload;

	symbol = rule_state->lookahead;
	action = &actions[lr_state_id * (SYM_TERMINAL_MAX + 1) + symbol];
	payload = rule_state->rule_id;
	if (action_is_conflict(action, ACTION_REDUCE, payload))
		return (false);
	action->type = ACTION_REDUCE;
	action->payload = payload;
	return (true);
}

static inline bool	add_reduces_and_accept(
						const t_rule rules[RULE_COUNT],
						t_action *actions,
						size_t lr_state_id,
						const t_rule_state *rule_state)
{
	const t_rule	*rule;
	t_action		*action;

	rule = &rules[rule_state->rule_id];
	if (rule_state->pos < rule->rhs_len)
		return (true);
	if (rule_state->rule_id == RULE_ACCEPT && rule_state->lookahead == SYM_EOF)
	{
		action = &actions[lr_state_id * (SYM_TERMINAL_MAX + 1) + SYM_EOF];
		if (action_is_conflict(action, ACTION_ACCEPT, ACTION_PAYLOAD_EMPTY))
			return (false);
		action->type = ACTION_ACCEPT;
		action->payload = ACTION_PAYLOAD_EMPTY;
		return (true);
	}
	return (add_reduces(actions, lr_state_id, rule_state));
}

static inline bool	compute_rule_states(
						const t_rule rules[RULE_COUNT],
						const t_lr_state *lr_states,
						t_action *actions,
						size_t lr_state_id)
{
	const t_lr_state	*lr_state;
	size_t				rule_state_id;
	const t_rule_state	*rule_state;

	lr_state = &lr_states[lr_state_id];
	rule_state_id = 0;
	while (rule_state_id < lr_state->len)
	{
		rule_state = &((const t_rule_state *)lr_state->data)[rule_state_id];
		if (!add_reduces_and_accept(rules, actions, lr_state_id, rule_state))
			return (false);
		rule_state_id++;
	}
	return (true);
}

bool	action_build_table(
			const t_rule rules[RULE_COUNT],
			const t_vector *lr_states,
			const t_vector *transitions,
			t_action **actions)
{
	size_t	lr_state_id;

	if (!action_build_default_table(actions, lr_states->len))
		return (false);
	else if (!add_shifts(transitions->data, transitions->len, *actions))
		return (action_free(actions), false);
	lr_state_id = 0;
	while (lr_state_id < lr_states->len)
	{
		if (!compute_rule_states(rules, lr_states->data, *actions, lr_state_id))
			return (action_free(actions), false);
		lr_state_id++;
	}
	return (true);
}
