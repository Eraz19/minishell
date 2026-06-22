#ifndef QUALIFIERS_TYPE_H
# define QUALIFIERS_TYPE_H

# include "error.h"
# include <stddef.h>

typedef t_error		(*t_qualifier)(void *parser, const char *token_value);

#endif
