/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_pool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:11:03 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 16:11:04 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "utils.h"
#include <assert.h>

t_error	token_pool_push(t_token_pool *pool, t_token *token)
{
	if (!vector_push(pool, token))
		return (error_sys());
	token_init(token);
	return (error(ERR_NO));
}

t_token	*token_pool_get(const t_token_pool *pool, size_t index)
{
	assert(index < pool->len);
	return (&((t_token *)pool->data)[index]);
}

void	token_pool_take(t_token_pool *pool, size_t index, t_token *dst)
{
	t_token	*src_token;

	src_token = token_pool_get(pool, index);
	token_transfer(dst, src_token);
}

t_error	token_pool_transfer(t_token_pool *dst, t_token_pool *src, size_t index)
{
	t_token	*src_token;
	t_token	dst_token;
	t_error	err;

	src_token = token_pool_get(src, index);
	token_transfer(&dst_token, src_token);
	err = token_pool_push(dst, &dst_token);
	if (err.type)
		token_transfer(src_token, &dst_token);
	return (err);
}

t_error	token_pool_deep_dup(void *dst, const void *src)
{
	return (vector_deep_dup(dst, src, token_dup_void, token_free_void));
}
