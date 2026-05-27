/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dquote.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 17:14:07 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/19 13:02:00 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_context.h"
#include "../stack/_stack.h"

bool	dquote_start(t_ctx_update_maybe *res, t_lexer *lexer)
{
	t_error	err;

	advance(lexer, 1);
	err = ctx_push(&lexer->ctx, DQUOTE);
	if (err != ERR_NO)
		return (on_ctx_update_failure(res, err), true);
	return (on_ctx_update_success(res, true), true);
}

bool	dquote_body(t_ctx_update_maybe *res, t_lexer *lexer)
{	
	char	*input_ptr;

	input_ptr = lexer->input + lexer->i;
	if (input_ptr[0] == '\\')
		return (backslash_in_dquote(res, lexer), true);
	else
	{
		if (is_param_start(lexer))
			return (param_start(res, lexer));
		else if (is_cmd_sub_start(lexer))
			return (cmd_sub_start(res, lexer));
		else if (is_arith_start(lexer))
			return (arith_start(res, lexer));
		else if (is_backtick_start(lexer))
			return (backtick_start(res, lexer));
	}
	return (on_ctx_update_success(res, false), true);
}

bool	dquote_end(t_ctx_update_maybe *res, t_lexer *lexer)
{
	advance(lexer, 1);
	ctx_pop(&lexer->ctx);
	return (on_ctx_update_success(res, true), true);
}

bool	is_dquote_start(t_lexer *lexer)
{
	char	*input_ptr;

	input_ptr = lexer->input + lexer->i;
	if (ctx_view(&lexer->ctx).type == DQUOTE ||
		ctx_view(&lexer->ctx).type == SQUOTE ||
		ctx_view(&lexer->ctx).type == COMMENT)
		return (false);
	return (input_ptr[0] == '"');
}

bool	dquote(t_ctx_update_maybe *res, t_lexer *lexer)
{
	char	*input_ptr;

	input_ptr = lexer->input + lexer->i;
	if (input_ptr[0] == '"')
		return (dquote_end(res, lexer));
	else
		return (dquote_body(res, lexer));
}
