#ifndef EXPANDER_FIELD__H
# define EXPANDER_FIELD__H

# include "error.h"
# include "libft.h"
# include "expander_word_.h"

typedef t_vector	t_expander_fields;

void	expander_fields_init(t_expander_fields *fields);
void	expander_fields_free(t_expander_fields *fields);

t_error	expander_fields_push(t_expander_fields *fields, t_expander_word item);
t_error	expander_fields_pop(t_expander_fields *fields, t_expander_word *item);

#endif
