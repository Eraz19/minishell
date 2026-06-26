#include "parser_type.h"
#include "token.h"
#include "utils.h"
#include "hooks.h"
#include <stdlib.h>

# include "debug.h"	// DEBUG
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
	fprintf(stderr, "[PARSER] %sfunction_name_is_valid = %s%s\n", YELLOW, bool_to_string(valid_name), NC);
	if (!valid_name)
	{
		err = error_print(error(ERR_INVALID_SYNTAX),
			"parser", NULL, "invalid function name: %s", token_value);
	}
	free(token_value);
	return (err);
}

t_error	hook_fname(
	t_parser *parser,
	t_parser_stack_item *rhs,
	size_t len,
	t_parser_stack_item *lhs)
{
	t_token		*token;
	t_error		err;

	if (len != 1)
		return (error_print(error(ERR_HOOK_INVALID_RHS_LEN), __func__,
			NULL, "expected 1 received %i", (int)len));
	token = &((t_token *)parser->tokens.data)[rhs[0].tokens_start_id];
	err = check_name(__func__, token);
	if (err.type != ERR_NO)
		return (err);
	return (hook_9_increment(parser, rhs, len, lhs));
}
