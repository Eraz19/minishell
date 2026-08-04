/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:39:10 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/04 16:39:11 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERATOR_H
# define GENERATOR_H

# include "grammar_rules.h"
# include "grammar_actions.h"
# include "grammar_qualifiers.h"
# include "libft.h"
# include <stdbool.h>
# include <stddef.h>

typedef struct s_lr_generator
{
	t_rule		rules[RULE_COUNT];
	bool		nullable_symbols[SYM_COUNT];
	bool		first[SYM_COUNT * (SYM_TERMINAL_MAX + 1)];
	t_vector	lr_states;
	t_vector	transitions;
	size_t		*gotos;			// see generator_goto.h
	t_action	*actions;		// see generator_actions.h
	t_qualifier	*qualifiers;	// [lr_state]
	bool		*expects;		// [lr_state]
}	t_lr_generator;

void	generator_init(t_lr_generator *generator);
void	generator_free(t_lr_generator *generator);

bool	generator_build_tables(t_lr_generator *gen);

#endif
