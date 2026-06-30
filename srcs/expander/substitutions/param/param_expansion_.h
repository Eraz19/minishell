#ifndef PARAM_EXPANSION__H
# define PARAM_EXPANSION__H

# include "expander_.h"

bool	is_param_expansion(
			t_expander *state,
			t_expander_word *word,
			t_expander_word_item *current_item);
t_error	param_expansion(
			t_expander *state,
			t_expander_fields *fields,
			t_expander_word *word,
			t_expander_word *word_exp);

#endif
