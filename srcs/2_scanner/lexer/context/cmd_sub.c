/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_sub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 14:22:55 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/09 16:20:17 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "__lexer.h"
	
bool	context_cmd_sub(t_lexer *lexer)
{
	if (lexer->token.type == NONE)
		lexer->token.type = TOKEN;
	(void)lexer;
	return (true);
}
