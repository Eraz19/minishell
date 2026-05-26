/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 16:27:11 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/25 17:00:12 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include <stdlib.h>
#include <sys/types.h>
#include "error.h"
#include "_lexer.h"
#include "./token/_token.h"
#include "./escape/_escape.h"
#include "./context/_context.h"
#include "./operator/_operator.h"

t_lexer	init_lexer(void)
{
	t_lexer	lexer =
	{
		.i = -1,
		.input = NULL,
		.ctx.len = 0,
		.ctx.size = 0,
		.ctx.data = NULL,
		.start_token_i = 0,
		.total_removed_count = 0,
		.current_removed_count = 0,
	};
	return (lexer);
}

void	free_lexer(t_lexer *lexer)
{
	if (lexer == NULL)
		return ;
	free_ctx_stack(&lexer->ctx);
	free(lexer->input);
	*lexer = (t_lexer){0};
	lexer->i = -1;
}
*/
//// ------------------ Blank HANDLING ------------------
//
//bool	on_input_blank(t_token **res, t_lexer *lexer, size_t *i)
//{
//	if (lexer->i == *i)
//		return (++lexer->i, ++(*i), true);
//	else
//	{
//		*res = create_word_token(lexer, *i);
//		return (lexer->continuation_i = -1, lexer->i = *i, *res != NULL);
//	}
//}
//
//// ------------------ Operator HANDLING ------------------
//
//bool	on_input_operator(t_token **res, t_lexer *lexer, t_operator_args args, size_t i)
//{
//	if (lexer->i == i)
//	{
//		*res = create_operator_token(lexer, &args);
//		return (lexer->continuation_i = -1, lexer->i += (size_t)args.len, *res != NULL);
//	}
//	else
//	{
//		*res = create_word_token(lexer, i);
//		return (lexer->continuation_i = -1, lexer->i = i, *res != NULL);
//	}
//}
//
//// ------------------ Comment HANDLING ------------------
//
//t_token	*on_input_comment_until_newline(t_lexer *lexer, char *comment_start, char *comment_end)
//{
//	t_token			*res;
//	t_operator_args	args;
//	size_t			comment_len;
//
//	comment_len = (size_t)(comment_end - comment_start);
//	ft_memmove(comment_start, comment_end, comment_len + 1);
//	args = (t_operator_args){.type = NEWLINE, .value = 0, .len = 0};
//	lexer->total_removed_count += comment_len;
//	res = create_operator_token(lexer, &args);
//	return (lexer->continuation_i = -1, lexer->i++, res);
//}
//
//void	on_input_comment_until_end(t_lexer *lexer, char *input_ptr, size_t *i)
//{
//	if (lexer->i == *i)
//		lexer->total_removed_count += str_len(input_ptr);
//	else
//		lexer->current_removed_count += str_len(input_ptr);
//	input_ptr[0] = '\0';
//}
//
//bool	on_input_comment(t_token **res, t_lexer *lexer, size_t *i)
//{
//	char			*input_ptr;
//	char			*newline_match;
//
//	input_ptr = lexer->input + *i;
//	newline_match = str_chr(input_ptr, '\n');
//	if (newline_match != NULL)
//	{
//		*res = on_input_comment_until_newline(lexer, input_ptr, newline_match);
//		return (*res != NULL);	
//	}
//	else
//		return (on_input_comment_until_end(lexer, input_ptr, i), true);
//}
//
//// ------------------ Escape CHARACTER HANDLING ------------------
//


//
//// ------------------ Context HANDLING ------------------
//

/*
int	update_ctx_none(t_ctx_update_maybe *res, t_lexer *lexer)
{
	t_lexer_ctx_type	new_ctx;
	char				*input_ptr;

	input_ptr = lexer->input + *i;
	if (is_ctx_opener(&new_ctx, input_ptr))
	{
		if (new_ctx == SQUOTE)
			return ((*i)++, ctx_push(&lexer->ctx, new_ctx));
		else if (new_ctx == DQUOTE)   
			return ((*i)++, ctx_push(&lexer->ctx, new_ctx));
		else if (new_ctx == BACKTICK) 
			return ((*i)++, ctx_push(&lexer->ctx, new_ctx));
		else if (new_ctx == CMD_SUB)  
			return ((*i) += 2, ctx_push(&lexer->ctx, new_ctx));
		else if (new_ctx == ARITH)    
			return ((*i) += 3, ctx_push(&lexer->ctx, new_ctx));
		else if (new_ctx == PARAM)    
			return ((*i) += 2, ctx_push(&lexer->ctx, new_ctx));
	}
	return (-1);
}

int	update_ctx_backtick(t_ctx_update_maybe *res, t_lexer *lexer)
{

}



static bool	update_ctx(t_ctx_update_maybe *res, t_lexer *lexer)
{
	t_lexer_ctx	current_ctx;

	current_ctx = ctx_view(&lexer->ctx);
	if (current_ctx.type == NONE)
		return (update_ctx_none(res, lexer), true);
	else if (current_ctx.type == SQUOTE)
		return (update_ctx_squote(res, lexer), true);
	else if (current_ctx.type == DQUOTE)
		return (update_ctx_dquote(res, lexer), true);
	else if (current_ctx.type == ARITH)
		return (update_ctx_arithm(res, lexer), true);
	else if (current_ctx.type == PARAM)
		return (update_ctx_param(res, lexer), true);
	else if (current_ctx.type == BACKTICK)
		return (update_ctx_backtick(res, lexer), true);
	return (on_ctx_update_success(res, false), true);
}
//
//// ------------------ Input HANDLING ------------------
//
static bool	lex_content(t_lex_line_maybe *res, t_lexer *lexer)
{
//	t_operator_args	args;
//
//	if (ctx_view(&lexer->ctx).type == NONE)
//	{
//		if (is_comment(lexer, *i))
//			return (on_input_comment(res, lexer, i));
//		else if (is_blank(lexer, *i))
//			return (on_input_blank(res, lexer, i));
//		else if (is_operator(lexer, &args, *i))
//			return (on_input_operator(res, lexer, args, *i));
//		else
//			++(*i);
//	}
//	else
//		++(*i);
//	return (true);
}
//
static void	on_reached_end(t_lex_line_maybe *res, t_lexer *lexer)
{
//	t_operator_args	args;
//	
//	if (ctx_view(&lexer->ctx).type == NONE)
//	{
//		if (lexer->i == i)
//		{
//			args = (t_operator_args){.type = EOF, .value = 0, .len = 0};
//			*res = create_operator_token(lexer, &args);
//			return (free_lexer(lexer), *res != NULL);
//		}
//		else
//		{
//			if (lexer->is_completed == false)
//				return (true);
//			*res = create_word_token(lexer, i);
//			return (lexer->continuation_i = -1, lexer->i = i, *res != NULL);
//		}
//	}
//	if (lexer->continuation_i < 0)
//	{
//		lexer->continuation_i = (ssize_t)i;
//	}
//	return (lexer->is_completed = false, true);
//	//if (ctx_view(&lexer->ctx).type == ESCAPED)
//	//	return (lexer->continuation_i = i - 1, ctx_pop(&lexer->ctx), true);
//	//return (lexer->continuation_i = i, true);
}

void	lex_line(t_lex_line_maybe *res, t_lexer *lexer)
{
	t_escape_maybe		escape_res;
	t_ctx_update_maybe	ctx_update_res;

	if (lexer == NULL || lexer->input == NULL)
		return (on_lex_failure(res, ERR_NULL_ARGS));
	if (lexer->i < 0)
		lexer->i = (ssize_t)lexer->start_token_i;
	lexer->is_completed = true;
	while (lexer->input[lexer->i] != '\0')
	{
		if (escape_character(&escape_res, lexer) && escape_res.err != ERR_NO)
			return (on_lex_failure(res, escape_res.err));
		else if (escape_res.res == true)
			continue ;
		if (update_ctx(&ctx_update_res, lexer) && ctx_update_res.err != ERR_NO)
			return (on_lex_failure(res, ctx_update_res.err));
		else if (ctx_update_res.res == true)
			continue ;
		if (lex_content(res, lexer) && res->err != ERR_NO)
			return (on_lex_failure(res, res->err));
		else if (res->res != NULL)
			return ;
	}
	return (on_reached_end(res, lexer));
}







bool	is_quoting_start(t_lex_maybe *res, t_lexer *lexer)
{
	t_error	err;
	char	*input_ptr;

	input_ptr = lexer->input + lexer->i;
	if (input_ptr[0] == '\'')
		err = ctx_push(&lexer->ctx, SQUOTE);
	else if (input_ptr[0] == '"')
		err = ctx_push(&lexer->ctx, DQUOTE);
	else if (!is_quoted(lexer) && input_ptr[0] == '\\')
		err = ctx_push(&lexer->ctx, ESCAPE);
	else if (!is_quoted(lexer) && input_ptr[0] == '$' && input_ptr[1] == '\'')
		err = ctx_push(&lexer->ctx, DOLLAR_SQUOTE);
	else
		return (false);
	if (err != ERR_NO)
		return (on_lex_failure(res, err));
	return (on_lex_success(res, true), true);
}

bool	is_quoted(t_lexer *lexer)
{
	t_lexer_ctx	current_ctx;

	current_ctx = ctx_view(&lexer->ctx);
	return (current_ctx.type == SQUOTE ||
			current_ctx.type == DQUOTE ||
			current_ctx.type == ESCAPE ||
			current_ctx.type == DOLLAR_SQUOTE);
}

bool	is_blank(t_lexer *lexer)
{
	char	*input_ptr;

	input_ptr = lexer->input + lexer->i;
	return (input_ptr[0] == ' ' || input_ptr[0] == '\t');
}

*/
/*
NEWLINE,		// `\n` - command separator
SCOLON,			// `;`- command separator
AMPERSAND,		// `&` - background command separator
DSEMI,			// `;;` - case separator
SEMI_AND,		// `;&` - case fallthrough
AND_IF,			// `&&` - logical AND operator
OR_IF,			// `||` - logical OR operator
PIPE,			// `|` - pipeline operator
LPARENTHESIS,	// `(` - subshell start
RPARENTHESIS,	// `)` - subshell end
IO_NUMBER,		// `[0-9]+` - file descriptor for redirection
LESSAND,		// `<&` - duplicate input file descriptor
GREATAND,		// `>&` - duplicate output file descriptor
LESS,			// `<` - input redirection
GREAT,			// `>` - output redirection
CLOBBER,		// `>|` - output redirection with clobbering (force overwrite)
LESSGREAT,		// `<>` - input/output redirection
DGREAT,			// `>>` - append redirection
DLESS,			// `<<` - here document
DLESSDASH		// `<<-` - here document with tab stripping
*/
















