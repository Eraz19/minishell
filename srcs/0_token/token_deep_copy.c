#include "token.h"
#include <stdlib.h>

t_error	token_deep_copy(t_token *dst, const t_token *src)
{
	t_error	err;

	err = token_dup(dst, src);
	if (err.type)
		return (err);
	dst->index.start = -1;
	dst->index.end = -1;
	dst->index.error = -1;
	return (err);
}

t_error	tokens_deep_copy(t_tokens *dst, const t_tokens *src)
{
	size_t	i;
	t_token	*src_token;
	t_token	*dst_token;
	t_error	err;

	err = tokens_init(dst, src->cap);
	if (err.type)
		return (err);
	i = 0;
	while (i < src->len)
	{
		dst_token = malloc(sizeof(*dst_token));
		if (dst_token == NULL)
			return (err = error_sys(), tokens_free(dst, true), err);
		err = tokens_get(src, i, &src_token);
		if (err.type)
			return (free(dst_token), tokens_free(dst, true), err);
		err = token_deep_copy(dst_token, src_token);
		if (err.type)
			return (free(dst_token), tokens_free(dst, true), err);
		if (err.type == ERR_NO && !vector_push(dst, &dst_token))
			return (err = error_sys(), token_free_owned(dst_token),
				tokens_free(dst, true), err);
	}
	return (err);
}
