#include "backtick_substitution_.h"

bool	is_backtick_substitution(t_expander_word_item *current_item)
{
	if (current_item->opt.context == CONTEXT_BACKTICK)
		return (true);
	return (false);
}

t_error	backtick_substitution(
	t_expander *state,
	t_expander_word *word,
	t_expander_word *word_exp)
{
	(void)state;
	(void)word;
	(void)word_exp;
	return (state->err);
}
