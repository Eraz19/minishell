/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_generator_life_cycle.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:09:11 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 12:09:12 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generator.h"
#include "generator_lr_state.h"
#include "generator_transitions.h"
#include "generator_goto.h"
#include "generator_actions.h"
#include "generator_qualifiers.h"
#include "generator_expects.h"

void	generator_init(t_lr_generator *generator)
{
	lr_state_table_init(&generator->lr_states);
	transition_init(&generator->transitions);
	goto_init(&generator->gotos);
	action_init(&generator->actions);
	qualifiers_init(&generator->qualifiers);
	expects_init(&generator->expects);
}

void	generator_free(t_lr_generator *generator)
{
	lr_state_table_free(&generator->lr_states);
	transition_free(&generator->transitions);
	goto_free(&generator->gotos);
	action_free(&generator->actions);
	qualifiers_free(&generator->qualifiers);
	expects_free(&generator->expects);
}
