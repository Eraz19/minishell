#ifndef QUOTE_REMOVAL__H
# define QUOTE_REMOVAL__H

# include "error.h"
# include "expander_.h"

t_error	quote_removal(t_expander *expander);
t_error	quote_remove_char(t_expander *expander);

#endif
