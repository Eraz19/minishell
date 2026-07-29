#ifndef GRAMMAR_ACTIONS_H
# define GRAMMAR_ACTIONS_H

# include <stddef.h>
# include <stdint.h>

# define ACTION_PAYLOAD_EMPTY	SIZE_MAX

/*
For performance purpose, actions table is contigously alloc'd.
Therefore, instead of accessing it via actions[lr_state][terminal_symbol],
it must be accessed via actions[row + terminal_symbol] where:
- row = lr_state * (SYM_TERMINAL_MAX + 1)
*/

typedef enum e_action_type
{
	ACTION_SHIFT,
	ACTION_REDUCE,
	ACTION_ACCEPT,
	ACTION_ERROR
}	t_action_type;

/*
action.payload can be:
- SHIFT: to_lr_state_id
- REDUCE: rule_id
- ACCEPT: none (ACTION_PAYLOAD_EMPTY)
- ERROR: none (ACTION_PAYLOAD_EMPTY)
*/
typedef struct s_action
{
	t_action_type	type;
	size_t			payload;
}	t_action;

#endif
