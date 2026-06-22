#ifndef ACTION_TYPE_H
# define ACTION_TYPE_H

# include <stddef.h>

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
