#ifndef BACKTICK_SUBSTITUTION__H
# define BACKTICK_SUBSTITUTION__H

# include "expander_.h"

t_error	backtick_substitution(t_expander *expander);
bool	is_backtick_substitution(t_word_item *current_item, uint flags);
#endif
