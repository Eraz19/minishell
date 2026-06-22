#include "lexer_context_.h"

t_error	lexer_context(t_lexer *state, t_context context)
{
	if (context == SQUOTE)
		return (lexer_context_squote(state));
	if (context == DQUOTE)
		return (lexer_context_dquote(state));
	if (context == DOLLAR_SQUOTE)
		return (lexer_context_dollar_squote(state));
	if (context == BACKTICK)
		return (lexer_context_backtick(state));
	if (context == ARITH)
		return (lexer_context_arith(state));
	if (context == PARAM)
		return (lexer_context_param(state));
	if (context == CMD_SUB)
		return (state->err = error(ERR_NOT_IMPLEMENTED));
	if (context == NONE_)
		return (state->err = error(ERR_INCOHERENT_STATE));
	return (state->err = error(ERR_INCOHERENT_STATE));
}
