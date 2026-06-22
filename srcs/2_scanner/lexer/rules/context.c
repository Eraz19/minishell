#include "lexer_rules_.h"

t_error	lexer_rule_quoting(t_lexer *state, t_context context)
{
	return (lexer_context(state, context));
}

t_error	lexer_rule_expansion(t_lexer *state, t_context context)
{
	if (context != CONTEXT_ARITH)
		return (lexer_context(state, context));
	else
	{
		if (lexer_context(state, CONTEXT_ARITH).type == ERR_CTX_END_NOT_FOUND)
		{
			state->err = error(ERR_NO);
			return (lexer_context(state, CONTEXT_CMD_SUB));
		}
		return (state->err);
	}
}
