#ifndef QUALIFIERS_TYPE_H
# define QUALIFIERS_TYPE_H

# include "error.h"
# include "token.h"
# include <stddef.h>

typedef t_error		(*t_qualifier)(void *parser, const t_token *token);

#endif
