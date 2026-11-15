/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:11:00 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 16:11:01 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

void	token_pool_init(t_token_pool *pool)
{
	(void)vector_init(pool, sizeof(t_token), 0);
}

void	token_pool_clear(t_token_pool *pool)
{
	vector_clear(pool, token_free_void);
}

void	token_pool_free(t_token_pool *pool)
{
	vector_free(pool, token_free_void);
}

void	token_pool_free_void(void *pool)
{
	token_pool_free(pool);
}
