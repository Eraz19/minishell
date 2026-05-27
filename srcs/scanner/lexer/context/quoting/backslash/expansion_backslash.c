/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_backslash.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 16:19:05 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/19 10:31:16 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_backslash.h"

bool	backslash_in_param(t_ctx_update_maybe *res, t_lexer *lexer)
{
	char	*input_ptr;
	
	input_ptr = lexer->input + lexer->i;
	if (input_ptr[1] == '\n')
	{
		consume_line_continuation(lexer);
		return (on_ctx_update_success(res, true));
	}
	else
		return (advance(lexer, 2), on_ctx_update_success(res, true));
}

bool	backslash_in_arithm(t_ctx_update_maybe *res, t_lexer *lexer)
{
	char	*input_ptr;
	
	input_ptr = lexer->input + lexer->i;
	if (input_ptr[1] == '\n')
	{
		consume_line_continuation(lexer);
		return (on_ctx_update_success(res, true));
	}
	else
		return (advance(lexer, 2), on_ctx_update_success(res, true));
}

bool	backslash_in_cmd_sub(t_ctx_update_maybe *res, t_lexer *lexer)
{
	char	*input_ptr;
	
	input_ptr = lexer->input + lexer->i;
	if (input_ptr[1] == '\n')
	{
		consume_line_continuation(lexer);
		return (on_ctx_update_success(res, true));
	}
	else
		return (advance(lexer, 2), on_ctx_update_success(res, true));
}

bool	backslash_in_backtick(t_ctx_update_maybe *res, t_lexer *lexer)
{
	char	*input_ptr;

	input_ptr = lexer->input + lexer->i;
	if (input_ptr[1] == '$' || input_ptr[1] == '`' || input_ptr[1] == '\\')
		return (advance(lexer, 2), on_ctx_update_success(res, true));
	else
		return (advance(lexer, 1), on_ctx_update_success(res, true));
}
