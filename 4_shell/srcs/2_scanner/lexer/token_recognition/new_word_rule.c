/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_word_rule.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:13:50 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 16:13:51 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_recognition_priv.h"
#include "token_recognition_context.h"

t_error	recognize_token_new_word(t_lexer *lexer) // Rule 10
{
	if (lexer->input->str.data[lexer->input->i] == '\\')
		return (none_context_escape_rules(lexer));
	else
		return (token_recognition_consume(lexer, TOKEN_TOKEN, 1));
}
