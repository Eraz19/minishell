/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_sub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 18:08:49 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/19 09:38:47 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_context.h"
#include "../stack/_stack.h"

bool	enter_cmd_substitution(t_ctx_update_maybe *res, t_lexer *lexer)
{
	t_error	err;

	advance(lexer, 2);
	err = ctx_push(&lexer->ctx, CMD_SUB);
	if (err != ERR_NO)
		return (on_ctx_update_failure(res, err), true);
	return (on_ctx_update_success(res, true), true);
}

bool	cmd_substitution_nesting(t_ctx_update_maybe *res, t_lexer *lexer)
{
	// parse_compound_list(lexer, until_token=')')
}

bool	leave_cmd_substitution(t_ctx_update_maybe *res, t_lexer *lexer)
{
	advance(lexer, 1);
	ctx_pop(&lexer->ctx);
	return (on_ctx_update_success(res, true), true);
}

bool	is_param_expansion(t_lexer *lexer)
{
	char	*input_ptr;

	input_ptr = lexer->input + lexer->i;
	return (input_ptr[0] == '$' && input_ptr[1] == '(');
}

bool	cmd_substitution(t_ctx_update_maybe *res, t_lexer *lexer)
{
	char	*input_ptr;
	int		nesting_depth;

	input_ptr = lexer->input + lexer->i;
	nesting_depth = ctx_view(&lexer->ctx).nesting_depth;
	if (input_ptr[0] == ')' && nesting_depth == 0)
		return (leave_cmd_substitution(res, lexer));
	else
		return (cmd_substitution_nesting(res, lexer));
}
