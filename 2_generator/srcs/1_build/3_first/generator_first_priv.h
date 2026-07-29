#ifndef GENERATOR_FIRST_PRIV_H
# define GENERATOR_FIRST_PRIV_H

# include <stdbool.h>

void	first_add(bool *dst, bool *did_add);
void	first_add_list(bool *dst, const bool *src, bool *did_add);

#endif
