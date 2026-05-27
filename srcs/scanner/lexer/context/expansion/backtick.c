/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtick.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 18:06:34 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/18 23:45:26 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_context.h"
#include "../stack/_stack.h"

bool	enter_backtick_substitution(t_ctx_update_maybe *res, t_lexer *lexer)
{
	t_error	err;

	advance(lexer, 1);
	err = ctx_push(&lexer->ctx, BACKTICK);
	if (err != ERR_NO)
		return (on_ctx_update_failure(res, err), true);
	return (on_ctx_update_success(res, true), true);
}

bool	backtick_substitution_nesting(t_ctx_update_maybe *res, t_lexer *lexer)
{

}

bool	leave_backtick_substitution(t_ctx_update_maybe *res, t_lexer *lexer)
{
	advance(lexer, 1);
	ctx_pop(&lexer->ctx);
	return (on_ctx_update_success(res, true), true);
}

bool	backtick_substitution(t_ctx_update_maybe *res, t_lexer *lexer)
{
	char	*input_ptr;

	input_ptr = lexer->input + lexer->i;
	if (input_ptr[0] == '`')
		return (leave_backtick_substitution(res, lexer), true);
	else 
	{
		
	}
}
