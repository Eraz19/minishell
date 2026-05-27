/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   squote.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 17:13:37 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/19 14:04:23 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_context.h"
#include "../stack/_stack.h"

bool	squote_start(t_ctx_update_maybe *res, t_lexer *lexer)
{
	t_error	err;

	advance(lexer, 1);
	err = ctx_push(&lexer->ctx, SQUOTE);
	if (err != ERR_NO)
		return (on_ctx_update_failure(res, err), true);
	return (on_ctx_update_success(res, true), true);
}

bool	squote_body(t_ctx_update_maybe *res, t_lexer *lexer)
{
	char	*input_ptr;

	input_ptr = lexer->input + lexer->i;
	if (input_ptr[0] == '\\')
		return (backslash_in_squote(res, lexer), true);
	else
		return (advance(lexer, 1), on_ctx_update_success(res, true));
}

bool	squote_end(t_ctx_update_maybe *res, t_lexer *lexer)
{
	advance(lexer, 1);
	ctx_pop(&lexer->ctx);
	return (on_ctx_update_success(res, true), true);
}

bool	is_squote_start(t_lexer *lexer)
{
	char	*input_ptr;

	input_ptr = lexer->input + lexer->i;
	if (ctx_view(&lexer->ctx).type == SQUOTE ||
		ctx_view(&lexer->ctx).type == DQUOTE ||
		ctx_view(&lexer->ctx).type == COMMENT)
		return (false);
	return (input_ptr[0] == '\'');
}

bool	squote(t_ctx_update_maybe *res, t_lexer *lexer)
{
	char	*input_ptr;

	input_ptr = lexer->input + lexer->i;
	if (input_ptr[0] == '\'')
		return (squote_end(res, lexer));
	else
		return (squote_body(res, lexer));
}

$((2 + 1) + 4)


aritm 