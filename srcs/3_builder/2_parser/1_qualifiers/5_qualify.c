#include "parser_type.h"
#include "qualifiers_priv.h"
# include <assert.h>	// DEBUG

t_error		qualify_5(void *parser, const t_token *token)
{
	assert(parser != NULL);
	assert(token != NULL);
	if (!qualify_try_name(token, &((t_parser *)parser)->lookahead_symbol))
		((t_parser *)parser)->lookahead_symbol = SYM_WORD;
	return (error(ERR_NO));
}
