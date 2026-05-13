/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DEBUG.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 17:41:45 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/13 15:38:13 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"
#include "_lexer.h"
#include "./context/_context.h"

bool	DEBUG_lexer_equal(t_lexer *lexer1, t_lexer_snapshot *lexer2)
{
	size_t	i;

	i = 0;
	if (lexer1->i != lexer2->i)
		return (false);
	if (lexer1->ctx.len != lexer2->ctx.len)
		return (false);
	if (lexer1->ctx.len > 0)
	{
		while (i < lexer1->ctx.len)
		{
			if (lexer1->ctx.data[i].type != lexer2->ctx.data[i].type)
				return (false);
			if (lexer1->ctx.data[i].nesting_depth != lexer2->ctx.data[i].nesting_depth)
				return (false);
			i++;
		}
	}
	if ((lexer1->input == NULL) != (lexer2->input == NULL))
		return (false);
	if (lexer1->input != NULL && strcmp(lexer1->input, lexer2->input) != 0)
		return (false);
	return (true);
}

void	DEBUG_print_lexer_state(t_lexer *lexer)
{
	size_t	i;

	i = 0;
	ft_printf("\n- LEXER_STATE ----------------------\n");
	ft_printf("INDEX = %d\n", (int)lexer->i);
	ft_printf("CTX_STACK_LEN = %d\n", (int)lexer->ctx.len);
	if (lexer->ctx.len > 0)
	{
		while (i < lexer->ctx.len)
		{
			ft_printf("CTX_STACK[%d] = {type = %s, nesting_depth = %d}\n", (int)i, DEBUG_ctx_type_stringify(lexer->ctx.data[i].type), (int)lexer->ctx.data[i].nesting_depth);
			i++;
		}
	}
	else
		ft_printf("CTX_STACK = {type = NONE, nesting_depth = 0}\n");
	ft_printf("INPUT = %s\n", lexer->input);
	ft_printf("SCRIPT_PATH = %s\n", lexer->script_path);
	ft_printf("TOTAL_REMOVED_COUNT = %d\n", (int)lexer->total_removed_count); // to track the count of characters removed from the input for accurate token offsets
	ft_printf("CURRENT_REMOVED_COUNT = %d\n", (int)lexer->current_removed_count);
	ft_printf("------------------------------------\n");
}
