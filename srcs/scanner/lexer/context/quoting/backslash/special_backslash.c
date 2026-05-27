/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_backslash.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 10:11:54 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/19 10:40:55 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_backslash.h"

bool	backslash_in_none(t_ctx_update_maybe *res, t_lexer *lexer)
{
	char	*input_ptr;
	
	input_ptr = lexer->input + lexer->i;
	if (input_ptr[1] == '\n')
		consume_line_continuation(lexer);
	if (input_ptr[0] == '\0')
	{
		lexer->is_completed = false;
		return (on_ctx_update_success(res, true));
	}
	else
		return (advance(lexer, 2), on_ctx_update_success(res, true));
}

bool	backslash_in_comment(t_ctx_update_maybe *res, t_lexer *lexer)
{
	(void)lexer;
	return (on_ctx_update_success(res, false));
}
