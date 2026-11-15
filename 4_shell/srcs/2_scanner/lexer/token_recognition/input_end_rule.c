/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_end_rule.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:13:39 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/06 22:26:33 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_recognition_priv.h"

t_error	recognize_token_input_end(t_lexer *lexer)
{
	token_recognition_delimit(lexer);
	if (lexer->token->type == TOKEN_NONE)
		lexer->token->type = TOKEN_EOF;
	return (lexer->err);
}
