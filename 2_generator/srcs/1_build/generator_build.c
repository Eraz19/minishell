/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator_build.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:09:42 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 12:09:51 by gastesan         ###   ########.fr       */
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
#include "logs.h"

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
	print_pass("rules table built                      (entries: %'6i)\n", RULE_COUNT);
	symbols_build_nullables_table(gen->rules, gen->nullable_symbols);
	print_pass("nullable symbols table built           (entries: %'6i)\n", SYM_COUNT);
	first_build_table(gen->rules, gen->nullable_symbols, gen->first);
	print_pass("first table built                      (entries: %'6i)\n", SYM_COUNT * (SYM_TERMINAL_MAX + 1));
	if (!generator_alloc_tables(gen))
		return (false);
	if (!transition_build_table(gen))
		return (false);
	print_pass("transitions table built                (entries: %'6zu)\n", gen->transitions.len);
	print_pass("lr_states table built                  (entries: %'6zu)\n", gen->lr_states.len);
	if (!goto_build_table(&gen->transitions, gen->lr_states.len, &gen->gotos))
		return (false);
	print_pass("gotos table built                      (entries: %'6zu)\n", gen->lr_states.len * (SYM_NON_TERMINAL_MAX - SYM_NON_TERMINAL_MIN + 1));
	if (!action_build_table(
			gen->rules,
			&gen->lr_states,
			&gen->transitions,
			&gen->actions))
		return (false);
	print_pass("actions table built                    (entries: %'6zu)\n", gen->lr_states.len * (SYM_TERMINAL_MAX + 1));
	if (!qualifiers_build_table(
			&gen->qualifiers,
			gen->rules,
			&gen->lr_states,
			gen->actions))
		return (false);
	print_pass("qualifiers table built                 (entries: %'6zu)\n", gen->lr_states.len);
	if (!expects_build_table(&gen->expects, gen->rules, &gen->lr_states))
		return (false);
	print_pass("expects table built                    (entries: %'6zu)\n", gen->lr_states.len);
	return (true);
}
