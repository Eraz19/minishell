/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 15:45:13 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/16 14:33:38 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

void	token_init(t_token *token)
{
	*token = (t_token){0};
	buff_init(&token->value, 0, NULL, 0);
	token_context_queue_init(&token->contexts);
}

void	token_free(t_token *token)
{
	token_context_queue_free(&token->contexts);
	buff_free(&token->value);
	*token = (t_token){0};
}
