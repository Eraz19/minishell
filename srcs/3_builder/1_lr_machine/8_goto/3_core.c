#include "goto.h"

bool	go_to(
	size_t **gotos,
	size_t current_lr_state_id,
	t_symbol symbol,
	size_t *new_lr_state_id)
{
	size_t	symbol_offset;
	size_t	tmp_lr_state_id;

	if (symbol < SYM_NON_TERMINAL_MIN || symbol > SYM_NON_TERMINAL_MAX)
		return (false);
	symbol_offset = symbol - SYM_NON_TERMINAL_MIN;
	tmp_lr_state_id = gotos[current_lr_state_id][symbol_offset];
	if (tmp_lr_state_id == GOTO_EMPTY)
		return (false);
	*new_lr_state_id = tmp_lr_state_id;
	return (true);
}
