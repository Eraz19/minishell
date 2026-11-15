/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lr_tables.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:22:00 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 12:22:01 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LR_TABLES_H
# define LR_TABLES_H

# include "grammar_symbols.h"
# include "grammar_actions.h"
# include "grammar_qualifiers.h"
# include <stdbool.h>
# include <stddef.h>

// lr_states.len (1.775)
# define LR_STATE_COUNT		1

// SYM_TERMINAL_MAX + 1 (43)
# define ACTION_COL_COUNT	1
// lr_states.len * ACTION_COL_COUNT (76.325)
# define ACTION_COUNT		1

// SYM_NON_TERMINAL_MAX - SYM_NON_TERMINAL_MIN + 1 (50)
# define GOTO_COL_COUNT		1
// lr_states.len * GOTO_COL_COUNT (88.750)
# define GOTO_COUNT			1

typedef struct s_lr_rule
{
	t_symbol	lhs;
	size_t		rhs_len;
}	t_lr_rule;

typedef struct s_lr_tables
{
	// rules[rule_id]
	const t_lr_rule		*rules;
	// actions[lr_state_id * ACTION_COL_COUNT + terminal_symbol]
	const t_action		*actions;
	// gotos[lr_state_id * GOTO_COL_COUNT + symbol - SYM_NON_TERMINAL_MIN]
	const size_t		*gotos;
	// qualifiers[lr_state_id]
	const t_qualifier	*qualifiers;
	// expects_cmd_name_or_word[lr_state_id]
	const bool			*expects_cmd_name_or_word;
}	t_lr_tables;

void	lr_tables_init(t_lr_tables *tables);

#endif
