#ifndef TILDE_EXPANSION__H
# define TILDE_EXPANSION__H

#include "expander_.h"

bool	is_tilde_expansion(t_expander *state, t_expander_word *word,
			t_expander_word_item *current_item);
t_error	tilde_expansion(t_expander *state, t_expander_word *word,
			t_expander_word *word_exp);

#endif
