#ifndef FIELD__H
# define FIELD__H

# include "error.h"
# include "libft.h"
# include "word_.h"

typedef t_vector	t_fields;

void	fields_init(t_fields *fields);
void	fields_free(t_fields *fields);

// ============= MAIN FUNCTIONS ================

t_error	fields_push(t_fields *fields, t_word item);
t_error	fields_fpop(t_word *out, t_fields *fields);

#endif
