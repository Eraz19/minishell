#ifndef QUALIFIERS_TYPE_H
# define QUALIFIERS_TYPE_H

# include "token.h"
# include "symbols_type.h"
# include <stddef.h>

typedef void	(*t_qualifier)(
					const t_token *token,
					bool assignment_disabled,
					t_symbol *out_symbol);

#endif
