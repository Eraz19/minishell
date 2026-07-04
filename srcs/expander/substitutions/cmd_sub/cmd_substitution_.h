#ifndef CMD_SUBSTITUTION__H
# define CMD_SUBSTITUTION__H

# include "expander_.h"

t_error	cmd_substitution(t_expander *expander);
bool	is_cmd_substitution(t_word_item *current_item, uint flags);

#endif
