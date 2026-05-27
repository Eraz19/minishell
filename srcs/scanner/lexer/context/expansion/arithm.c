/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 17:59:46 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/19 14:06:38 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_context.h"
#include "../stack/_stack.h"

bool	enter_arith_expansion(t_ctx_update_maybe *res, t_lexer *lexer)
{
	t_error	err;

	advance(lexer, 1);
	err = ctx_push(&lexer->ctx, ARITH);
	if (err != ERR_NO)
		return (on_ctx_update_failure(res, err), true);
	return (on_ctx_update_success(res, true), true);
}

bool	arith_expansion_nesting(t_ctx_update_maybe *res, t_lexer *lexer)
{
	char	*input_ptr;

	input_ptr = lexer->input + lexer->i;
	dquote_body(res, lexer);
	if (input_ptr[0] == '(')
		ctx_update_nesting(&lexer->ctx, 1);
	else if (input_ptr[0] == ')')
		ctx_update_nesting(&lexer->ctx, -1);
	else
		return (on_ctx_update_success(res, false));	
}

bool	leave_arith_expansion(t_ctx_update_maybe *res, t_lexer *lexer)
{
	advance(lexer, 2);
	ctx_pop(&lexer->ctx);
	return (on_ctx_update_success(res, true), true);
}

bool	is_arithm_start(t_lexer *lexer)
{
	char	*input_ptr;

	input_ptr = lexer->input + lexer->i;
	if (input_ptr[0] == '$' && input_ptr[1] == '(' && input_ptr[1] == '(')
	{
		while ()
		
	}
}

bool	arith_expansion(t_ctx_update_maybe *res, t_lexer *lexer)
{
	char	*input_ptr;
	int		nesting_depth;

	input_ptr = lexer->input + lexer->i;
	nesting_depth = ctx_view(&lexer->ctx).nesting_depth;
	if (input_ptr[0] == ')' && input_ptr[1] == ')' && nesting_depth == 0)
		return (leave_arith_expansion(res, lexer), true);
	else
		return (arith_expansion_nesting(res, lexer));
}
