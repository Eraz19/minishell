#include "parser.h"
#include "converter_priv.h"
#include "cst_type.h"
#include "token.h"
#include <stdbool.h>
# include <assert.h>	// DEBUG

t_error	converter_get_token(
			const t_parser *parser,
			const t_cst_node *node,
			size_t node_token_id,
			t_token **dst)
{
	size_t	token_id;

	assert(parser != NULL);
	assert(node != NULL);
	assert(dst != NULL);
	if (node_token_id >= node->tokens_count)
		return (error(ERR_INDEX_OUT_OF_BOUND));
	token_id = node->tokens_start_id + node_token_id;
	return (parser_get_token(__func__, parser, token_id, dst));
}
