#include "parser_type.h"
#include "token.h"
#include <stdlib.h>

# include "debug.h"	// DEBUG
t_error	parser_qualify_symbol(
	t_parser *parser,
	size_t lr_state_id,
	t_token	*token)
{
	char	*token_value;
	t_error	err;

	err = error(ERR_NO);
	parser->lookahead_symbol = parser->lookahead_raw_symbol;
	if (parser->lookahead_symbol != SYM_TOKEN)
		return (err);
	token_value = buff_get_string(&token->value);
	if (!token_value)
		return (error_print(error_sys(), "parser", __func__,
			"unable to get token value", NULL, NULL));
	if (parser->qualifiers[lr_state_id])
	{
		printf("[QUALIFIER RUN] state=%zu raw=%s value=%s qualifier=%p\n",
			lr_state_id,
			symbol_to_string(parser->lookahead_raw_symbol),
			token_value,
			parser->qualifiers[lr_state_id]);
		err = parser->qualifiers[lr_state_id](parser, token_value);
		printf("[QUALIFIER RUN] state=%zu result=%s\n",
			lr_state_id,
			symbol_to_string(parser->lookahead_symbol));
	}
	free(token_value);
	return (err);
}
