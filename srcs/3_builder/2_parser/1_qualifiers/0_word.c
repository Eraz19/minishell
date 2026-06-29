#include "parser_type.h"
#include "qualifiers_priv.h"

t_error		qualify_word(void *parser, const t_token *token)
{
	(void)token;
	((t_parser *)parser)->lookahead_symbol = SYM_WORD;
	return (error(ERR_NO));
}
