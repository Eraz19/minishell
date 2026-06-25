#ifndef TILDE_EXPANSION__H
# define TILDE_EXPANSION__H

#include "expander_.h"

t_error	tilde_expansion(t_expander *state);
bool	is_tilde_expansion(t_expander *state, t_expander_word *word);

#endif
