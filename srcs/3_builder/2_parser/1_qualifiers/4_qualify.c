#include "parser_type.h"

t_error		qualify_4(void *parser, const char *token_value)
{
	if (str_cmp("esac", token_value) == 0)
		((t_parser *)parser)->lookahead_symbol = SYM_Esac;
	else
		((t_parser *)parser)->lookahead_symbol = SYM_WORD;
	return (error(ERR_NO));
}
