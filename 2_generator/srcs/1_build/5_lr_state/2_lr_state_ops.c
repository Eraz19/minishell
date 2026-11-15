/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_lr_state_ops.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:43:26 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/04 16:43:27 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generator_lr_state.h"
#include "generator_rule_state.h"
#include <stdio.h>

static inline bool	lr_state_contains_rule_state(
						const t_lr_state *lr_state,
						const t_rule_state *rule_state)
{
	const t_rule_state	*items;
	size_t				i;

	items = (const t_rule_state *)lr_state->data;
	i = 0;
	while (i < lr_state->len)
	{
		if (rule_state_equal(&items[i], rule_state))
			return (true);
		i++;
	}
	return (false);
}

bool	lr_state_add_rule_state(
			t_lr_state *lr_state,
			const t_rule_state *rule_state,
			bool *did_add)
{
	if (lr_state_contains_rule_state(lr_state, rule_state))
		return (true);
	if (!vector_push(lr_state, rule_state))
		return (perror("generator"), false);
	if (did_add != NULL)
		*did_add = true;
	return (true);
}

bool	lr_state_equal(const t_lr_state *a, const t_lr_state *b)
{
	const t_rule_state	*items;
	size_t				i;

	if (a->len != b->len)
		return (false);
	items = (const t_rule_state *)a->data;
	i = 0;
	while (i < a->len)
	{
		if (lr_state_contains_rule_state(b, &items[i]) == false)
			return (false);
		i++;
	}
	return (true);
}
