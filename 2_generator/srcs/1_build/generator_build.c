/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator_build.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:09:42 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 18:44:45 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generator.h"
#include "generator_rules.h"
#include "generator_symbols.h"
#include "generator_first.h"
#include "generator_lr_state.h"
#include "generator_transitions.h"
#include "generator_goto.h"
#include "generator_actions.h"
#include "generator_qualifiers.h"
#include "generator_expects.h"
#include <stdio.h>

#define TRANSITION_INITIAL_CAP		6000
#define LR_STATE_INITIAL_CAP		2000

static inline bool	generator_alloc_tables(t_lr_generator *generator)
{
	if (!vector_init(
			&generator->transitions,
			sizeof(t_transition),
			TRANSITION_INITIAL_CAP))
		return (perror("generator"), false);
	if (!vector_init(
			&generator->lr_states,
			sizeof(t_lr_state),
			LR_STATE_INITIAL_CAP))
		return (perror("generator"), false);
	return (true);
}

bool	generator_build_tables(t_lr_generator *gen)
{
	rules_build(gen->rules);
	symbols_build_nullables_table(gen->rules, gen->nullable_symbols);
	first_build_table(gen->rules, gen->nullable_symbols, gen->first);
	if (!generator_alloc_tables(gen))
		return (false);
	if (!transition_build_table(gen))
		return (false);
	if (!goto_build_table(&gen->transitions, gen->lr_states.len, &gen->gotos))
		return (false);
	if (!action_build_table(
			gen->rules,
			&gen->lr_states,
			&gen->transitions,
			&gen->actions))
		return (false);
	if (!qualifiers_build_table(
			&gen->qualifiers,
			gen->rules,
			&gen->lr_states,
			gen->actions))
		return (false);
	if (!expects_build_table(&gen->expects, gen->rules, &gen->lr_states))
		return (false);
	return (true);
}
