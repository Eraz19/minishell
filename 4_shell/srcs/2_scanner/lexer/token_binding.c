#include "lexer.h"
#include "lexer_priv.h"

void	bind_lexer_token(t_lexer *lexer, t_token *out)
{
	if (lexer->token == NULL)
	{
		token_init(out);
		lexer->token = out;
	}
}

void	unbind_lexer_token(t_lexer *lexer)
{
	lexer->token = NULL;
}
