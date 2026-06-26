#ifndef DOLLAR_SQUOTE_EXPANSION__H
# define DOLLAR_SQUOTE_EXPANSION__H

# include "expander_.h"

bool	is_dollar_squote_expansion(t_expander_word_item *current_item);
t_error	dollar_squote_expansion(t_expander *state, t_expander_word *word,
			t_expander_word *word_exp);

#endif
