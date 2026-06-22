#include "parser_type.h"
#include "qualifiers_priv.h"

t_error		qualify_1(void *parser, const char *token_value)
{
	t_parser	*parser_;

	parser_ = (t_parser *)parser;
	if (qualify_try_reserved_word(token_value, &parser_->lookahead_symbol))
		return (error(ERR_NO));
	parser_->lookahead_symbol = SYM_WORD;
	return (error(ERR_NO));
}
