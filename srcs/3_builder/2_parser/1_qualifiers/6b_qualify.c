#include "parser_type.h"

t_error		qualify_6b(void *parser, const char *token_value)
{
	if (str_cmp("in", token_value) == 0)
		((t_parser *)parser)->lookahead_symbol = SYM_In;
	else if (str_cmp("do", token_value) == 0)
		((t_parser *)parser)->lookahead_symbol = SYM_Do;
	else
		((t_parser *)parser)->lookahead_symbol = SYM_WORD;
	return (error(ERR_NO));
}
