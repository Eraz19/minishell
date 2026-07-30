#include "token_recognition_context_scan_priv.h"

bool	has_innermost_unterminated_context(t_context *out, t_token *token)
{
	size_t					i;
	t_context_stack_item	*item;

	i = token->contexts.len;
	while (i > 0)
	{
		--i;
		context_stack_get(&token->contexts, &item, i);
		if (item->end == SIZE_MAX)
			return (*out = item->context, true);
	}
	return (false);
}

bool	get_message_on_unterminated_context(const char **out, t_lexer *lexer)
{
	t_context	context;

	if (!has_innermost_unterminated_context(&context, lexer->token))
		return (false);
	if (context == CONTEXT_SQUOTE)
		return (*out = "unterminated single quotes", true);
	else if (context == CONTEXT_DQUOTE)
		return (*out = "unterminated double quotes", true);
	else if (context == CONTEXT_DOLLAR_SQUOTE)
		return (*out = "unterminated $'...' quotes", true);
	else if (context == CONTEXT_BACKTICK)
		return (*out = "unterminated backquote substitution", true);
	else if (context == CONTEXT_CMD_SUB)
		return (*out = "unterminated command substitution", true);
	else if (context == CONTEXT_ARITH)
		return (*out = "unterminated arithmetic expansion", true);
	else if (context == CONTEXT_PARAM)
		return (*out = "unterminated parameter expansion", true);
	else
	 	return (*out = "unterminated unknown context", true);
}

t_error	error_unterminated_construct(t_lexer *lexer)
{
	const char	*error_message;

	if (!get_message_on_unterminated_context(&error_message, lexer))
		error_message = "unexpected end of input";
	if (lexer->err.type == ERR_VEOF)
		lexer->err = error(ERR_POSIX_SYNTAX);
	return (lexer->err = error_print(lexer->err, "scanner", error_message, NULL, NULL));
}
