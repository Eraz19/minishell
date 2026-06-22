#include "parser_type.h"
#include "token.h"
#include "utils.h"
#include "hooks.h"
#include <stdlib.h>

static t_error	check_name(const char *hook_name, t_token *token)
{
	char		*token_value;
	bool		valid_name;
	t_error		err;

	err = error(ERR_NO);
	token_value = buff_get_string(&token->value);
	if (!token_value)
		return (error_print(error_sys(), "parser", hook_name,
			"unable to get token value", NULL, NULL));
	valid_name = name_is_valid(token_value);
	if (!valid_name)
	{
		(void)error_print(error(ERR_PARSER_INVALID_FUNCTION_NAME),
			"parser", NULL, "%s", token_value);
		err = error(ERR_INVALID_SYNTAX);
	}
	free(token_value);
	return (err);
}

t_error	hook_fname(t_parser_stack_item *rhs, size_t len, void *ctx)
{
	t_parser	*parser;
	t_token		*token;
	t_error		err;

	if (len != 1)
		return (error_print(error(ERR_HOOK_INVALID_RHS_LEN), __func__,
			NULL, "expected 1 received %i", (int)len));
	parser = (t_parser *)ctx;
	token = &((t_token *)parser->tokens.data)[rhs[0].tokens_start_id];
	err = check_name(__func__, token);
	if (err.type != ERR_NO)
		return (err);
	return (hook_9_increment(rhs, len, ctx));
}
