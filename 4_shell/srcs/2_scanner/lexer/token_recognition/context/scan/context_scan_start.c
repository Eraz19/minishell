/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context_scan_start.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:12:25 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 16:12:26 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_recognition_priv.h"
#include "token_recognition_context_scan.h"

t_error	scan_context_start(t_token_recognition_context args)
{
	t_token_type	type;

	type = TOKEN_TOKEN;
	args.lexer->token->type = type;
	if (args.context_item != NULL)
		args.context_item->start = args.lexer->token->value.len;
	return (token_recognition_consume(args.lexer, type, args.opening_len));
}
