/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 16:27:11 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/09 17:26:59 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../_scanner.h"

static bool	escape_character(t_lexer *lexer, size_t *i)
{
	char		*input_ptr;
	t_lexer_ctx	current_ctx;
	
	input_ptr = lexer->input + *i;
	if (input_ptr[0] == '\\')
	{
		if (input_ptr[1] != '\0')
			return ((*i)++, true);
		current_ctx = ctx_view(&lexer->ctx);
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

static bool	update_ctx(t_lexer *lexer, size_t *i)
{
	char		*input_ptr;
	t_lexer_ctx	current_ctx;

	input_ptr = lexer->input + *i;
	current_ctx = ctx_view(&lexer->ctx);
	if (current_ctx.type == NONE)
		return (update_ctx_in_no_ctx(&lexer->ctx, input_ptr, i));
	else if (current_ctx.type == SQUOTE)
		return (update_ctx_in_squote(&lexer->ctx, input_ptr, i));
	else if (current_ctx.type == DQUOTE)
		return (update_ctx_in_dquote(&lexer->ctx, input_ptr, i));
	else if (current_ctx.type == BACKTICK)
		return (update_ctx_in_backtick(&lexer->ctx, input_ptr, i));
	else if (current_ctx.type == ARITH)
		return (update_ctx_in_arithm(&lexer->ctx, input_ptr, i));
	else if (current_ctx.type == PARAM)
		return (update_ctx_in_param(&lexer->ctx, input_ptr, i));
	return (true);
}

static bool	eof(t_token **res, t_lexer *lexer, size_t i)
{
	t_lexer_ctx		current_ctx;

	//ft_printf("ENTER EOF\n");	
	current_ctx = ctx_view(&lexer->ctx);
	if (current_ctx.type == NONE)
	{
		//ft_printf("IS IN NONE_CONTEXT\n");
		*res = create_token(NULL, i, EOF);
		if (*res == NULL)
			return (/*ft_printf("LEAVE ERROR EOF\n"),*/ false);
		free(lexer->input);
		lexer->input = NULL;
		lexer->i = 0;
	}
	return (/*ft_printf("LEAVE EOF\n"), */true);
}

static bool	end_token(t_token **res, t_lexer *lexer, size_t *i)
{
	t_token_type	type;
	int				io_number;
	char			*input_ptr;
	t_lexer_ctx		current_ctx;

	input_ptr = lexer->input + *i;
	current_ctx = ctx_view(&lexer->ctx);
	if (current_ctx.type == NONE)
	{
		if (input_ptr[0] == '\0')
			return (eof(res, lexer, *i), true);
		else if (is_operator(&type, &io_number, input_ptr))
		{
			ft_printf("END TOKEN WITH OPERATOR\n");
			*res = end_token_by_operator(type, io_number, lexer->i);
			//ft_printf("BEFORE LEXER INDEX = %d\n", (int)lexer->i);
			lexer->i = *i + 1;
			//ft_printf("AFTER LEXER INDEX = %d\n", (int)lexer->i);
			return (*res != NULL);
		}
		else if (is_operator(&type, &io_number, input_ptr + 1))
		{
			if (is_blank_end_token(input_ptr))
				return (++lexer->i, ++i, true);
			else
			{
				//ft_printf("END TOKEN WITH BLANK\n");
				*res = end_token_by_blank(lexer->input, lexer->i, *i + 1);
				lexer->i = *i + 1;
				return (*res != NULL);
			}
		}
		else if (is_blank_end_token(input_ptr))
		{
			if (*i == lexer->i)
				return (++lexer->i, ++i, true);
			else
			{
				//ft_printf("END TOKEN WITH BLANK\n");
				*res = end_token_by_blank(lexer->input, lexer->i, *i);
				lexer->i = *i + 1;
				return (*res != NULL);
			}
		}
		else if (input_ptr[1] == '\0')
		{
			*res = end_token_by_blank(lexer->input, lexer->i, *i + 1);
			lexer->i = *i + 1;
			return (*res != NULL);
		}
	}
	return (true);
}

bool	lex_line(t_token **res, t_lexer *lexer)
{
	size_t	i;

	//ft_printf("ENTER LEX_LINE\n");
	//ft_printf("LEXER = %p | INPUT = %p\n", lexer, lexer->input);
	if (lexer == NULL || lexer->input == NULL)
		return (/*ft_printf("LEAVE ERROR INPUT LEX_LINE\n"), */false);
	i = lexer->i;
	*res = NULL;
	if ((lexer->input)[i] == '\0')
		return (eof(res, lexer, i), true);
	while ((lexer->input)[i] != '\0')
	{
		if (!escape_character(lexer, &i))
		{
			if (!update_ctx(lexer, &i))
				return (/*ft_printf("LEAVE ERROR UPDATE_CTX LEX_LINE\n"),*/ false);
			if (!end_token(res, lexer, &i))
				return (/*ft_printf("LEAVE ERROR END_TOKEN LEX_LINE\n"),*/ false);
			if (*res != NULL)
				return (/*ft_printf("LEAVE LEX_TOKEN\n"),*/ true);
			++i;
		}
	}
	if (i == lexer->i)
		return (eof(res, lexer, i), true);
	return (/*ft_printf("LEAVE NO_TOKEN LEX_LINE\n"),*/ true);
}
