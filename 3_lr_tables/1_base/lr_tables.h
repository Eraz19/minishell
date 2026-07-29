#ifndef LR_TABLES_H
# define LR_TABLES_H

# include "grammar_symbols.h"
# include "grammar_actions.h"
# include "grammar_qualifiers.h"
# include <stdbool.h>
# include <stddef.h>

// lr states
# define LR_STATE_COUNT		1

// actions
# define ACTION_COL_COUNT	1
# define ACTION_COUNT		1

// gotos
# define GOTO_COL_COUNT		1
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

void	lr_tables_load(t_lr_tables *tables);

#endif
