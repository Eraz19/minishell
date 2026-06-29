#include "parser_type.h"
#include "qualifiers_priv.h"
# include <assert.h>	// DEBUG

t_error		qualify_1(void *parser, const t_token *token)
{
	t_parser	*parser_;

	assert(parser != NULL);
	assert(token != NULL);
	parser_ = (t_parser *)parser;
	if (qualify_try_reserved_word(token, &parser_->lookahead_symbol))
		return (error(ERR_NO));
	parser_->lookahead_symbol = SYM_WORD;
	return (error(ERR_NO));
}
