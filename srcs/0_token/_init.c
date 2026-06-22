#include "token.h"

void	token_init(t_token *token)
{
	*token = (t_token){0};
	buff_init(&token->value, 0, NULL, 0);
	context_stack_init(&token->contexts);
}

void	token_free(t_token *token)
{
	context_stack_free(&token->contexts);
	buff_free(&token->value);
	*token = (t_token){0};
}
