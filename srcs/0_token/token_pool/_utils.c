#include "token.h"
#include <assert.h>

t_error	token_pool_push(t_token_pool *pool, t_token *token)
{
	if (!vector_push(pool, token))
		return (error_sys());
	token_init(token);
	return (error(ERR_NO));
}

t_token	*token_pool_get(t_token_pool *pool, size_t i)
{
	assert(i < pool->len);
	return (&((t_token *)pool->data)[i]);
}

void	token_pool_take(t_token_pool *pool, size_t i, t_token *dst)
{
	t_token	*src_token;

	src_token = token_pool_get(pool, i);
	token_transfer(dst, src_token);
}
