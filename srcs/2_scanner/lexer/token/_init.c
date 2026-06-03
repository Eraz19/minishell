/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 15:45:13 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/03 15:12:24 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_token.h"

void	token_init(t_token *token)
{
	if (token == NULL)
		return ;
	*token = (t_token){0};
	buff_init(&token->value, 0, NULL, 0);
}

void	token_free(t_token *token)
{
	if (token == NULL)
		return ;
	buff_free(&token->value);
	*token = (t_token){0};
}

t_error	token_reset(t_token *res, size_t len)
{
	if (res == NULL)
		return (ERR_NULL_ARGS);
	token_free(res);
	if (!buff_init(&res->value, len, NULL, 0))
        return (ERR_TOKEN_INIT);
	return (ERR_NO);
}
