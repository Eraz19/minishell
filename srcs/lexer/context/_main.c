#include "lexer.h"

t_error	lexer_context(t_lexer *lexer, t_context context)
{
	if (context == CONTEXT_SQUOTE)
		return (lexer_context_squote(lexer));
	if (context == CONTEXT_DQUOTE)
		return (lexer_context_dquote(lexer));
	if (context == CONTEXT_DOLLAR_SQUOTE)
		return (lexer_context_dollar_squote(lexer));
	if (context == CONTEXT_BACKTICK)
		return (lexer_context_backtick(lexer));
	if (context == CONTEXT_ARITH)
		return (lexer_context_arith(lexer));
	if (context == CONTEXT_PARAM)
		return (lexer_context_param(lexer));
	if (context == CONTEXT_CMD_SUB)
		return (lexer_context_cmd_sub(lexer));
	if (context == CONTEXT_NONE)
		return (lexer->err = error(ERR_INCOHERENT_STATE));
	return (lexer->err = error(ERR_INCOHERENT_STATE));
}
