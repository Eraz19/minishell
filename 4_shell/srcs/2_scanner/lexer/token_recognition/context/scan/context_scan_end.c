/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context_scan_end.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:12:15 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 16:51:47 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "scanner_priv.h"
#include "token_recognition_priv.h"
#include "token_recognition_context_scan.h"
#include "token_recognition_context_scan_priv.h"

t_error	on_context_scan_eoi(t_lexer *lexer)
{
	if (lexer->input_stack.len > 1)
		return (lexer_pop_alias(lexer));
	lexer->err = read_and_propagate_ps2(lexer->scanner);
	if (lexer->err.type == ERR_POSIX_SYNTAX || lexer->err.type == ERR_VEOF)
		return (error_unterminated_construct(lexer));
	return (lexer->err);
}

t_error	scan_context_end(t_token_recognition_context args)
{
	t_token_type	type;

	type = args.lexer->token->type;
	if (args.context_item != NULL)
		args.context_item->end = args.lexer->token->value.len;
	return (token_recognition_consume(args.lexer, type, args.closing_len));
}
