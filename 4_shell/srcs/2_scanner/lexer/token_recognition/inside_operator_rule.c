/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inside_operator_rule.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:13:43 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 16:34:01 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_recognition_priv.h"
#include "token_recognition_operator.h"

t_error	recognize_token_inside_operator(t_lexer *lexer)
{
	if (is_operator_char(lexer))
		return (token_recognition_consume_operator(lexer), lexer->err);
	else
		return (token_recognition_delimit(lexer), lexer->err);
}
