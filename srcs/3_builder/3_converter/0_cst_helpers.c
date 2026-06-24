#include "parser_type.h"
#include "cst_type.h"
#include "token.h"
#include <stdbool.h>

t_error	converter_get_buff(
	t_parser *parser,
	t_cst_node *node,
	size_t node_token_id,
	t_buff **dst)
{
	t_token	*token;
	size_t	token_id;

	if (node_token_id >= node->tokens_count)
		return (error(ERR_INDEX_OUT_OF_BOUND));
	token_id = node->tokens_start_id + node_token_id;
	token = &((t_token *)parser->tokens.data)[token_id];
	*dst = &token->value;
	return (error(ERR_NO));
}

t_error	converter_dup_buff(
	t_parser *parser,
	t_cst_node *node,
	size_t node_token_id,
	t_buff *dst)
{
	t_buff	*token_buff;
	t_error	err;

	err = converter_get_buff(parser, node, node_token_id, &token_buff);
	if (err.type)
		return (err);
	if (!buff_dup_n(dst, token_buff, token_buff->len))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	converter_get_string(
	t_parser *parser,
	t_cst_node *node,
	size_t node_token_id,
	char **dst)
{
	t_buff	*buff;
	t_error	err;

	err = converter_get_buff(parser, node, node_token_id, &buff);
	if (err.type)
		return (err);
	*dst = buff_get_string(buff);
	if (!*dst)
		return (error_sys());
	return (error(ERR_NO));
}
