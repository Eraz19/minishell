#ifndef EXPANSION__H
# define EXPANSION__H

# include "expander.h"
# include "field_.h"

void	expansion_init(t_expansion *expansion);
t_error	expansion_load(t_expansion *out, t_fields *src);

// ============= MAIN FUNCTIONS ================

t_error	expansion_bpop(t_string *out, t_expansion *expansion);
t_error	expansion_fpop(t_string *out, t_expansion *expansion);
t_error	expansion_push(t_expansion *expansion, t_string *str);

#endif
