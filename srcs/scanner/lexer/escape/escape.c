/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 16:19:05 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/13 15:36:17 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../_lexer.h"
#include "../context/_context.h"

bool	escape_char_in_param(t_lexer *lexer, size_t *i)
{
	char	*input_ptr;
	
	input_ptr = lexer->input + *i;
	if (!ctx_push(&lexer->ctx, ESCAPED))
		return (false);
	if (input_ptr[1] == '\n')
	{
		ft_memmove(input_ptr, input_ptr + 2, str_len(input_ptr + 2));
		input_ptr[str_len(input_ptr + 2)] = '\0';
		if (lexer->i == *i)
			lexer->total_removed_count += 2;
		else
			lexer->current_removed_count += 2;
		return (ctx_pop(&lexer->ctx), true);
	}
	else if (lexer->input[*i + 1] == '\0')
		return ((*i)++, true);
	return (ctx_pop(&lexer->ctx), (*i) += 2, true);
}

bool	escape_char_in_arithm(t_lexer *lexer, size_t *i)
{
	char	*input_ptr;
	
	input_ptr = lexer->input + *i;
	if (!ctx_push(&lexer->ctx, ESCAPED))
		return (false);
	if (input_ptr[1] == '\n')
	{
		ft_memmove(input_ptr, input_ptr + 2, str_len(input_ptr + 2));
		input_ptr[str_len(input_ptr + 2)] = '\0';
		if (lexer->i == *i)
			lexer->total_removed_count += 2;
		else
			lexer->current_removed_count += 2;
		return (ctx_pop(&lexer->ctx), true);
	}
	else if (lexer->input[*i + 1] == '\0')
		return ((*i)++, true);
	return (ctx_pop(&lexer->ctx), (*i) += 2, true);
}

bool	escape_char_in_backtick(t_lexer *lexer, size_t *i)
{
	if (!ctx_push(&lexer->ctx, ESCAPED))
		return (false);
	if (lexer->input[*i + 1] == '\0')
		return ((*i)++, true);
	return (ctx_pop(&lexer->ctx), (*i) += 2, true);
}

bool	escape_char_in_dquote(t_lexer *lexer, size_t *i)
{
	char	*input_ptr;
	
	input_ptr = lexer->input + *i;
	if (!ctx_push(&lexer->ctx, ESCAPED))
		return (false);
	ft_printf("ESCAPE_CHAR_IN_DQUOTE\n");
	if (input_ptr[1] == '\n')
	{
		ft_printf("MEMMOVE IN DQUOTE\n");
		ft_memmove(input_ptr, input_ptr + 2, str_len(input_ptr + 2));
		input_ptr[str_len(input_ptr + 2)] = '\0';
		if (lexer->i == *i)
			lexer->total_removed_count += 2;
		else
			lexer->current_removed_count += 2;
		return (ctx_pop(&lexer->ctx), true);
	}
	else if (lexer->input[*i + 1] == '\0')
		return ((*i)++, true);
	return (ctx_pop(&lexer->ctx), (*i) += 2, true);
}

bool	escape_char_in_no_ctx(t_lexer *lexer, size_t *i)
{
	char	*input_ptr;
	
	input_ptr = lexer->input + *i;
	if (!ctx_push(&lexer->ctx, ESCAPED))
		return (false);
	if (input_ptr[1] == '\n')
	{
		ft_printf("MEMMOVE IN NO_CTX\n");
		ft_memmove(input_ptr, input_ptr + 2, str_len(input_ptr + 2));
		input_ptr[str_len(input_ptr + 2)] = '\0';
		if (lexer->i == *i)
			lexer->total_removed_count += 2;
		else
			lexer->current_removed_count += 2;
		return (ctx_pop(&lexer->ctx), true);
	}
	else if (lexer->input[*i + 1] == '\0')
		return ((*i)++, true);
	return (ctx_pop(&lexer->ctx), (*i) += 2, true);
}
