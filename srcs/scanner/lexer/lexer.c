/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 16:27:11 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/13 16:20:15 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "_lexer.h"
#include "./token/_token.h"
#include "./escape/_escape.h"
#include "./context/_context.h"
#include "./operator/_operator.h"

static bool	escape_character(t_lexer *lexer, size_t *i)
{
	t_lexer_ctx	current_ctx;
	
	ft_printf("ESCAPE_CHARACTER\n");
	if (lexer->input[*i] == '\\')
	{
		ft_printf("ESCAPE_CHARACTER | BACKSLASH FOUND\n");
		current_ctx = ctx_view(&lexer->ctx);
		if (current_ctx.type == NONE)
			return (escape_char_in_no_ctx(lexer, i));
		else if (current_ctx.type == SQUOTE)
			return (false);
		else if (current_ctx.type == DQUOTE)
			return (escape_char_in_dquote(lexer, i));
		else if (current_ctx.type == BACKTICK)
			return (escape_char_in_backtick(lexer, i));
		else if (current_ctx.type == ARITH)
			return (escape_char_in_arithm(lexer, i));
		else if (current_ctx.type == PARAM)
			return (escape_char_in_param(lexer, i));
	}
	return (false);
}

//0 on failure, -1 on no update and 1 on update
static int	update_ctx(t_lexer *lexer, size_t *i)
{
	char		*input_ptr;
	t_lexer_ctx	current_ctx;

	ft_printf("UPDATE CTX\n");
	input_ptr = lexer->input + *i;
	current_ctx = ctx_view(&lexer->ctx);
	ft_printf("ctx : type = %d | stack_size = %d | stack_len = %d\n", (int)current_ctx.type, (int)lexer->ctx.size, (int)lexer->ctx.len);
	for (size_t j = 0; j < lexer->ctx.len; j++)
		ft_printf("ctx stack %d : type = %d\n", (int)j, (int)lexer->ctx.data[j].type);
	if (current_ctx.type == NONE)
		return (ft_printf("UPDATE_CTX_WHEN_NO_CTX\n"), update_ctx_none(&lexer->ctx, input_ptr, i));
	else if (current_ctx.type == SQUOTE)
		return (ft_printf("UPDATE_CTX_WHEN_SQUOTE\n"), update_ctx_squote(&lexer->ctx, input_ptr, i));
	else if (current_ctx.type == DQUOTE)
		return (ft_printf("UPDATE_CTX_WHEN_DQUOTE\n"), update_ctx_dquote(&lexer->ctx, input_ptr, i));
	else if (current_ctx.type == BACKTICK)
		return (ft_printf("UPDATE_CTX_WHEN_BACKTICK\n"), update_ctx_backtick(&lexer->ctx, input_ptr, i));
	else if (current_ctx.type == ARITH)
		return (ft_printf("UPDATE_CTX_WHEN_ARITHM\n"), update_ctx_arithm(&lexer->ctx, input_ptr, i));
	else if (current_ctx.type == PARAM)
		return (ft_printf("UPDATE_CTX_WHEN_PARAM\n"), update_ctx_param(&lexer->ctx, input_ptr, i));
	return (true);
}

bool	on_input_blank(t_token **res, t_lexer *lexer, size_t *i)
{
	ft_printf("ON INPUT BLANK\n");
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
	ft_printf("ON INPUT OPERATOR\n");
	if (lexer->i == i)
	{
		*res = create_operator_token(lexer, &args);
		lexer->i += (size_t)args.len;
	}
	else
	{
		*res = create_word_token(lexer, i);
		lexer->i = i;
	}
	return (*res != NULL);
}

bool	on_input_comment(t_token **res, t_lexer *lexer, size_t *i)
{
	t_operator_args	args;
	char			*input_ptr;
	char			*newline_match;

	input_ptr = lexer->input + *i;
	newline_match = str_chr(input_ptr, '\n');
	if (newline_match != NULL)
	{
		ft_memmove(input_ptr, newline_match, str_len(newline_match) + 1);
		lexer->total_removed_count += (size_t)(newline_match - input_ptr);
		args = (t_operator_args){.type = NEWLINE, .value = 0, .len = 0};
		*res = create_operator_token(lexer, &args);
		lexer->i++;
		return (*res != NULL);
	}
	else
	{
		if (lexer->i == *i)
			lexer->total_removed_count += str_len(input_ptr);
		else
			lexer->current_removed_count += str_len(input_ptr);
		input_ptr[0] = '\0';
		return (true);
	}
}

bool	on_input_content(t_token **res, t_lexer *lexer, size_t *i)
{
	t_operator_args	args;

	ft_printf("ON INPUT CONTENT\n");
	if (ctx_view(&lexer->ctx).type == NONE)
	{
		if (is_comment(lexer, *i))
			return (on_input_comment(res, lexer, i));
		else if (is_blank(lexer, *i))
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

void	free_lexer(t_lexer *lexer)
{
	if (lexer == NULL)
		return ;
	free_ctx_stack(&lexer->ctx);
	free(lexer->input);
	*lexer = (t_lexer){0};
}

bool	on_input_end(t_token **res, t_lexer *lexer, size_t i)
{
	t_operator_args	args;
	
	ft_printf("ON INPUT END\n");
	if (ctx_view(&lexer->ctx).type == NONE)
	{
		if (lexer->i == i)
		{
			ft_printf("ON INPUT END | EOF\n");
			args = (t_operator_args){.type = EOF, .value = 0, .len = 0};
			*res = create_operator_token(lexer, &args);
			free_lexer(lexer);
			return (*res != NULL);
		}
		else
		{
			ft_printf("ON INPUT END | WORD\n");
			*res = create_word_token(lexer, i);
			return (lexer->i = i, *res != NULL);
		}
	}
	if (ctx_view(&lexer->ctx).type == ESCAPED)
		ctx_pop(&lexer->ctx);
	return (lexer->i = i - 1, true);
}

bool	lex_line(t_token **res, t_lexer *lexer)
{
	size_t	i;
	int		ctx_update_res;

	ft_printf("LEX_LINE\n");
	if (lexer == NULL || lexer->input == NULL)
		return (false);
	*res = NULL;
	i = lexer->i;
	while (lexer->input[i] != '\0')
	{
		ft_printf("INPUT = '%s' | INDEX = %d | CURRENT_REMOVED = %d | TOTAL_REMOVED = %d\n", lexer->input, (int)i, (int)lexer->current_removed_count, (int)lexer->total_removed_count);
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
