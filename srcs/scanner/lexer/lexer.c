/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 16:27:11 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/11 13:57:50 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../_scanner.h"

static bool	escape_character(t_lexer *lexer, size_t *i)
{
	char		*input_ptr;
	t_lexer_ctx	current_ctx;
	
	//ft_printf("ESCAPE_CHARACTER\n");
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

//0 on failure, -1 on no update and 1 on update
static int	update_ctx(t_lexer *lexer, size_t *i)
{
	char		*input_ptr;
	t_lexer_ctx	current_ctx;

	//ft_printf("UPDATE CTX\n");
	input_ptr = lexer->input + *i;
	current_ctx = ctx_view(&lexer->ctx);
	if (current_ctx.type == NONE)
		return (/*ft_printf("UPDATE_CTX_IN_NO_CTX\n"), */update_ctx_in_no_ctx(&lexer->ctx, input_ptr, i));
	else if (current_ctx.type == SQUOTE)
		return (/*ft_printf("UPDATE_CTX_IN_SQUOTE\n"), */update_ctx_in_squote(&lexer->ctx, input_ptr, i));
	else if (current_ctx.type == DQUOTE)
		return (/*ft_printf("UPDATE_CTX_IN_DQUOTE\n"), */update_ctx_in_dquote(&lexer->ctx, input_ptr, i));
	else if (current_ctx.type == BACKTICK)
		return (/*ft_printf("UPDATE_CTX_IN_BACKTICK\n"), */update_ctx_in_backtick(&lexer->ctx, input_ptr, i));
	else if (current_ctx.type == ARITH)
		return (/*ft_printf("UPDATE_CTX_IN_ARITHM\n"), */update_ctx_in_arithm(&lexer->ctx, input_ptr, i));
	else if (current_ctx.type == PARAM)
		return (/*ft_printf("UPDATE_CTX_IN_PARAM\n"), */update_ctx_in_param(&lexer->ctx, input_ptr, i));
	return (true);
}

bool	on_input_blank(t_token **res, t_lexer *lexer, size_t *i)
{
	//ft_printf("ON INPUT BLANK\n");
	if (lexer->i == *i)
		return (++lexer->i, ++(*i), true);
	else
	{
		*res = create_word_token(lexer, *i);
		lexer->i = *i;
	}
	return (*res != NULL);
}

bool	on_input_operator(t_token **res, t_lexer *lexer, t_operator_args args, size_t i)
{
	//ft_printf("ON INPUT OPERATOR\n");
	if (lexer->i == i)
	{
		*res = create_operator_token(args, lexer->i);
		lexer->i += (size_t)args.len;
	}
	else
	{
		*res = create_word_token(lexer, i);
		lexer->i = i;
	}
	return (*res != NULL);
}

bool	on_input_content(t_token **res, t_lexer *lexer, size_t *i)
{
	t_operator_args	args;

	//ft_printf("ON INPUT CONTENT\n");
	if (ctx_view(&lexer->ctx).type == NONE)
	{
		if (is_blank(lexer, *i))
			return (on_input_blank(res, lexer, i));
		else if (is_operator(lexer, &args, *i))
			return (on_input_operator(res, lexer, args, *i));
		else
		 	++(*i);
	}
	else
		++(*i);
	return (true);
}

bool	on_input_end(t_token **res, t_lexer *lexer, size_t i)
{
	t_operator_args	args;
	
	ft_printf("ON INPUT END\n");
	if (ctx_view(&lexer->ctx).type == NONE)
	{
		if (lexer->i == i)
		{
			args = (t_operator_args){.type = EOF, .value = 0, .len = 0};
			*res = create_operator_token(args, lexer->i);
		}
		else
		{
			*res = create_word_token(lexer, i);
			lexer->i = i;
		}
		if (*res == NULL)
			return (false);
		return (true);
	}
	else
		return (true);	
}

bool	lex_line(t_token **res, t_lexer *lexer)
{
	size_t	i;
	int		ctx_update_res;

	//ft_printf("LEX_LINE\n");
	if (lexer == NULL || lexer->input == NULL)
		return (false);
	*res = NULL;
	i = lexer->i;
	while (lexer->input[i] != '\0')
	{
		if (!escape_character(lexer, &i))
		{
			ctx_update_res = update_ctx(lexer, &i);
			if (ctx_update_res == 0)
				return (false);
			//ft_printf("ctx_update_res %d\n", ctx_update_res);
			if (ctx_update_res == -1)
			{
				if (!on_input_content(res, lexer, &i))
					return (false);
				if (*res != NULL)
					return (true);				
			}
		}
	}
	return (on_input_end(res, lexer, i));
}
