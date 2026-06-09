/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 15:45:13 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/05 19:37:47 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "__lexer_token.h"

void	token_init(t_token *token)
{
	*token = (t_token){0};
	buff_init(&token->value, 0, NULL, 0);
}

void	token_free(t_token *token)
{
	buff_free(&token->value);
	*token = (t_token){0};
}

t_error	token_reset(t_token *token, size_t len)
{
	token_free(token);
	if (!buff_init(&token->value, len, NULL, 0))
        return (ERR_TOKEN_INIT);
	return (ERR_NO);
}
