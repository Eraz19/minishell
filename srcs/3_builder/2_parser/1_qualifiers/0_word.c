#include "parser_type.h"

t_error		qualify_word(void *parser, const char *token_value)
{
	(void)token_value;
	((t_parser *)parser)->lookahead_symbol = SYM_WORD;
	return (error(ERR_NO));
}
