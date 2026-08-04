#include "parser_type.h"
#include <assert.h>	// DEBUG

void	parser_take_token(t_parser *parser, size_t index, t_token *dst)
{
	assert(parser != NULL);
	assert(dst != NULL);
	token_pool_take(&parser->token_pool, index, dst);
}
