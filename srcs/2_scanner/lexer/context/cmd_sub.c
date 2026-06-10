/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_sub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 14:22:55 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/10 16:51:02 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_.h"
	
bool	context_cmd_sub(t_lexer *lexer)
{
	if (lexer->token.type == NONE)
		lexer->token.type = TOKEN;
	(void)lexer;
	return (true);
}
