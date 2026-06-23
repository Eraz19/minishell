#ifndef LR_MACHINE_TYPE_H
# define LR_MACHINE_TYPE_H

# include "libft.h"
# include "rules__type.h"
# include "action_type.h"

typedef struct s_lr_machine
{
	t_rule		rules[RULE_COUNT];
	bool		nullable_symbols[SYM_COUNT];
	bool		first[SYM_COUNT][SYM_TERMINAL_MAX + 1];
	t_vector	lr_states;
	t_vector	transitions;
	size_t		**gotos;		// [lr_state][non-terminal_symbol]
	t_action	**actions;		// [lr_state][terminal_symbol]
}	t_lr_machine;

#endif
