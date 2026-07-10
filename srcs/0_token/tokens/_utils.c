#include "token.h"
#include <stdlib.h>

t_error	tokens_get(const t_tokens *tokens, size_t i, t_token **out_token_ptr)
{
	if (i >= tokens->pointers.len)
		return (error(ERR_INDEX_OUT_OF_BOUND));
	*out_token_ptr = ((t_token **)tokens->pointers.data)[i];
	return (error(ERR_NO));
}

t_error	tokens_push(t_tokens *tokens, t_token *src)
{
	if (!vector_push(&tokens->pointers, &src))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	tokens_deep_copy(t_tokens *dst, const t_tokens *src)
{
	size_t	i;
	t_token	*src_token;
	t_token	*dst_token;
	t_error	err;

	err = tokens_init(dst, src->pointers.cap, true, true);
	if (err.type)
		return (err);
	i = 0;
	while (i < src->pointers.len)
	{
		dst_token = malloc(sizeof(*dst_token));
		if (dst_token == NULL)
			return (err = error_sys(), tokens_free(dst), err);
		token_init(dst_token);
		err = tokens_get(src, i, &src_token);
		if (err.type == ERR_NO)
			err = token_deep_copy(dst_token, src_token);
		if (err.type == ERR_NO)
			err = tokens_push(dst, dst_token);
		if (err.type)
			return (token_free_owned(dst_token), tokens_free(dst), err);
	}
	return (err);
}
