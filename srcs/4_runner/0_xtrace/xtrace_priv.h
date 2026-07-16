#ifndef XTRACE_PRIV_H
# define XTRACE_PRIV_H

# include "libft.h"
# include "error.h"
# include <stddef.h>

t_error	xtrace_print_prefix(void);
t_error	xtrace_print_content(const t_string *string, size_t i, size_t count);

#endif
