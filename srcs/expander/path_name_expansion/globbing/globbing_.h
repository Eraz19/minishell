#ifndef GLOBBING__H
# define GLOBBING__H

# include "expander_.h"
# include "path_comps_.h"

t_error	path_globbing(t_expander *expander, t_path_comps *src, bool *globbed);

#endif
