#include "token.h"
#include <stdlib.h>

void	token_init(t_token *token)
{
	*token = (t_token){0};
	(void)string_init(&token->value, 0, NULL, 0);
	context_stack_init(&token->contexts);
	token->index.end = -1;
	token->index.start = -1;
	token->index.error = -1;
	token->assignment_offset = -1;
}

void	token_free(t_token *token)
{
	context_stack_free(&token->contexts);
	string_free(&token->value);
	*token = (t_token){0};
	token->index.end = -1;
	token->index.start = -1;
	token->index.error = -1;
	token->assignment_offset = -1;
}

void	token_free_void(void *token)
{
	token_free(token);
}

void	token_free_owned(void *token)
{
	token_free(token);
	free(token);
}

t_error	tokens_init(t_tokens *tokens, size_t cap)
{
	if (!vector_init(tokens, sizeof(t_token *), cap))
		return (error_sys());
	return (error(ERR_NO));
}

void	tokens_free(t_tokens *tokens, bool owned)
{
	if (owned == true)
		vector_free(tokens, token_free_owned);
	else
		vector_free(tokens, NULL);
}
