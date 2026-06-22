#include "parser_type.h"
#include "qualifiers_priv.h"

t_error		qualify_7a(void *parser, const char *token_value)
{
	t_parser	*parser_;

	parser_ = (t_parser *)parser;
	if (qualify_try_reserved_word(token_value, &parser_->lookahead_symbol))
		return (error(ERR_NO));
	return (qualify_7b(parser, token_value));
}
