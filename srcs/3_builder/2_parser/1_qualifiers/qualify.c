#include "parser_type.h"
#include "token.h"
#include "qualifiers.h"
#include <stdlib.h>
# include <assert.h>	// DEBUG

t_error	parser_qualify_symbol(
	t_parser *parser,
	size_t lr_state_id,
	const t_token *token)
{
	assert(parser != NULL);
	assert(token != NULL);
	parser->lookahead_symbol = parser->lookahead_raw_symbol;
	if (parser->lookahead_symbol != SYM_TOKEN)
		return (error(ERR_NO));
	if (parser->qualifiers[lr_state_id])
		return (parser->qualifiers[lr_state_id](parser, token));
	return (error(ERR_NO));
}
