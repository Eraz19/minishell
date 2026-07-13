#ifndef EXPANSION__H
# define EXPANSION__H

# include "expander.h"
# include "field_.h"

void	expansion_init(t_expansion *expansion);
t_error	expansion_load(t_expansion *out, t_fields *src);

/**
 * @brief Initializes @p out as an expansion holding a single empty field
 *        with an allocated (non-NULL) buffer.
 *
 * POSIX result of expanding an empty value or here-document body: one
 * empty field (no field to split, nothing to glob).
 *
 * @param out Expansion initialized by the function (borrowed).
 * @return @c ERR_LIBC if the allocation fails, @c ERR_NO on success.
 */
t_error	expansion_load_empty(t_expansion *out);

// ============= MAIN FUNCTIONS ================

t_error	expansion_bpop(t_string *out, t_expansion *expansion);
t_error	expansion_fpop(t_string *out, t_expansion *expansion);
t_error	expansion_push(t_expansion *expansion, t_string *str);

#endif
