#include <assert.h> // DEBUG
#include "token_recognition_priv.h"
#include "token_recognition_operator.h"

bool	is_char_pipe_fit_operator(t_lexer *lexer)
{
	if (lexer->token->type == TOKEN_PIPE)
		return (true);
	else if (lexer->token->type == TOKEN_GREAT)
		return (true);
	else if (!is_inside_operator(lexer))
		return (true);
	return (false);
}

t_error	token_recognition_consume_pipe(t_lexer *lexer)
{
	if (lexer->token->type == TOKEN_PIPE)
		return (token_recognition_consume(lexer, TOKEN_OR_IF, 1));
	else if (lexer->token->type == TOKEN_GREAT)
		return (token_recognition_consume(lexer, TOKEN_CLOBBER, 1));
	else if (lexer->token->type == TOKEN_NONE)
		return (token_recognition_consume(lexer, TOKEN_PIPE, 1));
	assert(false);
	return (error(ERR_NO));
}
