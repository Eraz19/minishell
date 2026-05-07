/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 16:27:11 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/07 16:31:41 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../_scanner.h"

static bool	escape_character(t_ctx_stack *ctx, char *input_ptr, size_t *i)
{
	t_lexer_ctx	current_ctx;
	
	if (input_ptr[0] == '\\')
	{
		if (input_ptr[1] != '\0')
			return ((*i)++, true);
		current_ctx = ctx_view(ctx);
		if (current_ctx.type == NONE)
			return (escape_char_in_no_ctx(input_ptr, i));
		else if (current_ctx.type == SQUOTE)
			return (false);
		else if (current_ctx.type == DQUOTE)
			return (escape_char_in_dquote(input_ptr, i));
		else if (current_ctx.type == BACKTICK)
			return (escape_char_in_backtick(i));
		else if (current_ctx.type == ARITH)
			return (escape_char_in_arithm(input_ptr, i));
		else if (current_ctx.type == PARAM)
			return (escape_char_in_param(input_ptr, i));
	}
	return (false);
}

static bool	update_ctx(t_ctx_stack *ctx, char *input_ptr, size_t *i)
{
	t_lexer_ctx	current_ctx;

	if (input_ptr == NULL || ctx == NULL || i == NULL)
		return (false);
	current_ctx = ctx_view(ctx);
	if (current_ctx.type == NONE)
		return (update_ctx_in_no_ctx(ctx, input_ptr, i));
	else if (current_ctx.type == SQUOTE)
		return (update_ctx_in_squote(ctx, input_ptr, i));
	else if (current_ctx.type == DQUOTE)
		return (update_ctx_in_dquote(ctx, input_ptr, i));
	else if (current_ctx.type == BACKTICK)
		return (update_ctx_in_backtick(ctx, input_ptr, i));
	else if (current_ctx.type == ARITH)
		return (update_ctx_in_arithm(ctx, input_ptr, i));
	else if (current_ctx.type == PARAM)
		return (update_ctx_in_param(ctx, input_ptr, i));
	return (true);
}

static bool	end_token(
	t_token **res,
	t_ctx_stack *ctx,
	char *input_ptr,
	size_t *i)
{
	t_token_type	type;
	int				io_number;
	t_lexer_ctx		current_ctx;

	current_ctx = ctx_view(ctx);
	if (current_ctx.type == NONE)
	{
		if (is_operator(&type, &io_number, input_ptr))
		{
			*res = end_token_by_operator(type, io_number, i);
			return (*res != NULL);
		}
		else if (is_blank_end_token(input_ptr))
		{
			*res = end_token_by_blank(input_ptr, i);
			return (*res != NULL);
		}
	}
	return (true);
}

static bool	eof(
	t_token **res,
	t_ctx_stack *ctx,
	char **input_ptr,
	size_t *start)
{
	t_lexer_ctx		current_ctx;

	current_ctx = ctx_view(ctx);
	if (current_ctx.type == NONE)
	{
		*res = create_token(NULL, *start, EOF);
		if (*res == NULL)
			return (false);
		free(*input_ptr);
		*input_ptr = NULL;
		*start = 0;
	}
	return (true);
}

bool	lex_line(t_token **res, t_ctx_stack *ctx, char **input, size_t *start)
{
	size_t	i;

	if (input == NULL || start == NULL || ctx == NULL)
		return (false);
	i = *start;
	*res = NULL;
	if ((*input)[i] == '\0')
		eof(res, ctx, input, start);
	while ((*input)[i] != '\0')
	{
		if (!escape_character(ctx, (*input) + i, &i))
		{
			if (!update_ctx(ctx, (*input) + i, &i))
				return (false);
			if (!end_token(res, ctx, (*input) + i, &i))
				return (false);
			if (*res != NULL)
				return (*start = i, true);
			++i;
		}
	}
	return (true);
}
