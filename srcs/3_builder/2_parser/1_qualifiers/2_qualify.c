#include "parser_type.h"

t_error		qualify_2(void *parser, const char *token_value)
{
	t_parser	*parser_;

	(void)token_value;
	parser_ = (t_parser *)parser;
	/*
	TODO:
		"The expansions specified in 2.7 Redirection shall occur.
		As specified there, exactly one field can result (or the result is unspecified).
		And there are additional requirements on pathname expansion.""	
	*/
	parser_->lookahead_symbol = SYM_WORD;
	return (error(ERR_NO));
}
