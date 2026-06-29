#include "parser_type.h"
#include "qualifiers_priv.h"
# include <assert.h>	// DEBUG

t_error		qualify_2(void *parser, const t_token *token)
{
	t_parser	*parser_;

	assert(parser != NULL);
	(void)token;
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
