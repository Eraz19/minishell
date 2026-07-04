#include "lexer.h"

t_error	lexer_rule_quoting(t_lexer *lexer, t_context context)
{
	return (lexer_context(lexer, context));
}

t_error	lexer_rule_expansion(t_lexer *lexer, t_context context)
{
	if (context != CONTEXT_ARITH)
		return (lexer_context(lexer, context));
	else
	{
		if (lexer_context(lexer, CONTEXT_ARITH).type == ERR_CTX_END_NOT_FOUND)
		{
			lexer->err = error(ERR_NO);
			return (lexer_context(lexer, CONTEXT_CMD_SUB));
		}
		return (lexer->err);
	}
}
