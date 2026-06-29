#ifndef CMD_SUBSTITUTION__H
# define CMD_SUBSTITUTION__H

# include "expander_.h"

bool	is_cmd_substitution(t_expander_word_item *current_item);
t_error	cmd_substitution(t_expander *state, t_expander_word *word,
			t_expander_word *word_exp);

#endif
