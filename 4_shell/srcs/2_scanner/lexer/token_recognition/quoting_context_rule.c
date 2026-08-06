/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting_context_rule.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:13:53 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 16:13:54 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_recognition_priv.h"
#include "token_recognition_context.h"

t_error	recognize_token_quoting_context(t_lexer *lexer, t_context context)
{
	return (token_recognition_consume_context(lexer, context));
}
