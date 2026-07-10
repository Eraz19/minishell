#include "token.h"
#include <stdlib.h>

t_error	tokens_init(t_tokens *tokens, size_t cap, bool own_ptrs, bool own_tokens)
{
	if (!vector_init(&tokens->pointers, sizeof(t_token *), cap))
		return (error_sys());
	tokens->own_ptrs = own_ptrs;
	tokens->own_tokens = own_tokens;
	return (error(ERR_NO));
}

void	tokens_free(t_tokens *tokens)
{
	void	(*free_func)(void *);

	if (tokens->own_ptrs == true && tokens->own_tokens == true)
		free_func = token_free_owned;
	else if (tokens->own_ptrs == true)
		free_func = free;
	else if (tokens->own_tokens == true)
		free_func = token_free_void;
	else
		free_func = NULL;
	vector_free(&tokens->pointers, free_func);
}
