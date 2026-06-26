#include "cmd_substitution_.h"

bool	is_cmd_substitution(t_expander_word_item *current_item)
{
	if (current_item->opt.context == CONTEXT_CMD_SUB)
		return (true);
	return (false);
}

t_error	cmd_substitution(
	t_expander *state,
	t_expander_word *word,
	t_expander_word *word_exp)
{
	(void)state;
	(void)word;
	(void)word_exp;
	return (state->err);
}
