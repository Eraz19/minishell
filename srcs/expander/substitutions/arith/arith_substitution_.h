#ifndef ARITH_SUBSTITUTION__H
# define ARITH_SUBSTITUTION__H

# include "expander_.h"

t_error	arith_substitution(t_expander *expander);
bool	is_arith_substitution(t_word_item *current_item, uint flags);

#endif
