/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 18:09:53 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/19 13:26:38 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_context.h"
#include "../stack/_stack.h"

bool	comment_start(t_ctx_update_maybe *res, t_lexer *lexer)
{
	t_error	err;

	advance(lexer, 1);
	err = ctx_push(&lexer->ctx, COMMENT);
	if (err != ERR_NO)
		return (on_ctx_update_failure(res, err), true);
	return (on_ctx_update_success(res, true), true);
}

bool	comment_body()
{
	
}

bool	comment_end(t_ctx_update_maybe *res, t_lexer *lexer)
{
	ctx_pop(&lexer->ctx);
	return (on_ctx_update_success(res, false), true);
}

bool	is_comment(t_lexer *lexer)
{
	char	*input_ptr;

	input_ptr = lexer->input + lexer->i;
	if (ctx_view(&lexer->ctx).type != NONE)
		return (false);
	return (input_ptr[0] == '#' && (size_t)lexer->i == lexer->start_token_i);
}

bool	comment(t_ctx_update_maybe *res, t_lexer *lexer)
{
	char	*input_ptr;

	input_ptr = lexer->input + lexer->i;
	if (input_ptr[0] == '\n')
		return (leave_comment(res, lexer));
	else
		return (on_ctx_update_success(res, false), true);
}
