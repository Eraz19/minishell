#ifndef ARITH_SUBSTITUTION__H
# define ARITH_SUBSTITUTION__H

# include "expander_.h"

bool	is_arith_substitution(t_expander_word_item *current_item);
t_error	arith_substitution(t_expander *state, t_expander_word *word,
			t_expander_word *word_exp);

#endif
