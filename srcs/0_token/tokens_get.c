#include "token.h"

t_error	tokens_get(const t_tokens *tokens, size_t i, t_token **out_token_ptr)
{
	if (i >= tokens->len)
		return (error(ERR_INDEX_OUT_OF_BOUND));
	*out_token_ptr = ((t_token **)tokens->data)[i];
	return (error(ERR_NO));
}
