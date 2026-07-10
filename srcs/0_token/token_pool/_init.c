#include "token.h"

void	token_pool_init(t_token_pool *pool)
{
	(void)vector_init(pool, sizeof(t_token), 0);
}

void	token_pool_clear(t_token_pool *pool)
{
	size_t	i;
	t_token	*token;

	i = 0;
	while (i < pool->len)
	{
		token = token_pool_get(pool, i);
		token_free(token);
		i++;
	}
	pool->len = 0;
}

void	token_pool_free(t_token_pool *pool)
{
	vector_free(pool, token_free_void);
}

void	token_pool_free_void(void *pool)
{
	token_pool_free(pool);
}
