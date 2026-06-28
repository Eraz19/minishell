#include "token.h"

void	token_init(t_token *const token)
{
	*token = (t_token){0};
	string_init(&token->value, 0, NULL, 0);
	context_stack_init(&token->contexts);
	token->assignment_offset = -1;
}

void	token_free(t_token *const token)
{
	context_stack_free(&token->contexts);
	string_free(&token->value);
	*token = (t_token){0};
	token->assignment_offset = -1;
}

void	token_free_void(void *const token)
{
	token_free(token);
}
