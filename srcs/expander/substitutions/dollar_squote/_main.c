#include "dollar_squote_expansion_.h"

bool	is_dollar_squote_expansion(t_expander_word_item *current_item)
{
	if (current_item->opt.quoted == CONTEXT_DOLLAR_SQUOTE)
		return (true);
	return (false);
}

t_error	dollar_squote_expansion(
	t_expander *state,
	t_expander_word *word,
	t_expander_word *word_exp)
{
	(void)state;
	(void)word;
	(void)word_exp;
	return (state->err);
}
