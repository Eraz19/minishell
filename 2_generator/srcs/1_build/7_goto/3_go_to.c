#include "generator_goto.h"
#include "grammar_gotos.h"

bool	go_to(
			const size_t *gotos,
			size_t current_lr_state_id,
			t_symbol symbol,
			size_t *new_lr_state_id)
{
	size_t	col;
	size_t	row;
	size_t	tmp_lr_state_id;

	if (symbol < SYM_NON_TERMINAL_MIN || symbol > SYM_NON_TERMINAL_MAX)
		return (false);
	col = symbol - SYM_NON_TERMINAL_MIN;
	row = current_lr_state_id;
	row *= SYM_NON_TERMINAL_MAX - SYM_NON_TERMINAL_MIN + 1;
	tmp_lr_state_id = gotos[row + col];
	if (tmp_lr_state_id == GOTO_EMPTY)
		return (false);
	*new_lr_state_id = tmp_lr_state_id;
	return (true);
}
