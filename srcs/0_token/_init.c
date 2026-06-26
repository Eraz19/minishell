#include "token.h"

void	token_init(t_token *token)
{
	*token = (t_token){0};
	buff_init(&token->value, 0, NULL, 0);
	context_stack_init(&token->contexts);
	token->assignment_offset = -1;
}

void	token_free(t_token *token)
{
	context_stack_free(&token->contexts);
	buff_free(&token->value);
	*token = (t_token){0};
	token->assignment_offset = -1;
}

void	token_free_void(void *token)
{
	token_free(token);
}
