/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_sub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 14:22:55 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/28 15:16:40 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_context.h"

bool	lexer_ctx_cmd_sub(t_lexer *lexer)
{
	if (lexer->token.type == NONE)
		lexer->token.type = TOKEN;
	(void)lexer;
	return (true);
}
