#ifndef TILDE_EXPANSION__H
# define TILDE_EXPANSION__H

#include "expander_.h"

t_error	tilde_expansion(t_expander *expander);
t_error	expand_user_path(t_expander *expander);
bool	is_tilde_expansion(t_expander *expander, t_word_item *current_item);

#endif
