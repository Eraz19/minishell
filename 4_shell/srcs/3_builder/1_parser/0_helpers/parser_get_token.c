#include "parser_type.h"
#include <assert.h>	// DEBUG

t_token	*parser_get_token(const t_parser *parser, size_t index)
{
	assert(parser != NULL);
	return (token_pool_get(&parser->token_pool, index));
}
