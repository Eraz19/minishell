/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_binding.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:14:29 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/05 16:13:26 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	bind_lexer_token(t_lexer *lexer, t_token *out)
{
	if (lexer->token == NULL)
	{
		token_init(out);
		lexer->token = out;
	}
}

void	lexer_unbind_token(t_lexer *lexer)
{
	lexer->token = NULL;
}
