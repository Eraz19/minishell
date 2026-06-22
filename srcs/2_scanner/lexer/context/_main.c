#include "lexer_context_.h"

t_error	lexer_context(t_lexer *state, t_context context)
{
	if (context == CONTEXT_SQUOTE)
		return (lexer_context_squote(state));
	if (context == CONTEXT_DQUOTE)
		return (lexer_context_dquote(state));
	if (context == CONTEXT_DOLLAR_SQUOTE)
		return (lexer_context_dollar_squote(state));
	if (context == CONTEXT_BACKTICK)
		return (lexer_context_backtick(state));
	if (context == CONTEXT_ARITH)
		return (lexer_context_arith(state));
	if (context == CONTEXT_PARAM)
		return (lexer_context_param(state));
	if (context == CONTEXT_CMD_SUB)
		return (state->err = error(ERR_NOT_IMPLEMENTED));
	if (context == CONTEXT_NONE)
		return (state->err = error(ERR_INCOHERENT_STATE));
	return (state->err = error(ERR_INCOHERENT_STATE));
}
