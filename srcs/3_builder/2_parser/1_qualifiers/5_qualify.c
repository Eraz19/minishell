#include "parser_type.h"
#include "qualifiers_priv.h"

t_error		qualify_5(void *parser, const char *token_value)
{
	if (!qualify_try_name(token_value, &((t_parser *)parser)->lookahead_symbol))
		((t_parser *)parser)->lookahead_symbol = SYM_WORD;
	return (error(ERR_NO));
}
