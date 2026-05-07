/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 16:06:40 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/07 16:38:34 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../_scanner.h"

static bool	is_ctx_opener(t_lexer_ctx_type *ctx, char *input_ptr)
{
	if (input_ptr[0] == '\'')
		return (*ctx = SQUOTE, true);
	if (input_ptr[0] == '"')
		return (*ctx = DQUOTE, true);
	if (input_ptr[0] == '`')
		return (*ctx = BACKTICK, true);
	if (input_ptr[0] == '$')
	{
		if (input_ptr[1] == '{')
			return (*ctx = PARAM, true);
		else if (input_ptr[1] == '(')
		{
			if (input_ptr[2] == '(')
				return (*ctx = ARITH, true);	
			return (*ctx = CMD_SUB, true);
		}
	}
	return (false);
}

bool	update_ctx_in_param(t_ctx_stack *ctx, char *input_ptr, size_t *i)
{
	t_lexer_ctx_type	new_ctx;

	if (input_ptr[0] == '}')
		return ((*i)++, ctx_pop(ctx), true);
	else if (is_ctx_opener(&new_ctx, input_ptr))
	{
		if (new_ctx == PARAM)
			return ((*i) += 2, ctx_push(ctx, new_ctx));
		else if (new_ctx == CMD_SUB)
			return ((*i) += 2, ctx_push(ctx, new_ctx));
		else if (new_ctx == ARITH)
			return ((*i) += 3, ctx_push(ctx, new_ctx));
		else if (new_ctx == BACKTICK)
			return ((*i) += 1, ctx_push(ctx, new_ctx));
	}
	return (true);
}

bool	update_ctx_in_arithm(t_ctx_stack *ctx, char *input_ptr, size_t *i)
{
	t_lexer_ctx_type	new_ctx;
	int					nesting_depth;

	nesting_depth = ctx_view(ctx).nesting_depth;
	if (input_ptr[0] == ')' && input_ptr[1] == ')' && nesting_depth == 0)
		return ((*i) += 2, ctx_pop(ctx), true);
	else if (is_ctx_opener(&new_ctx, input_ptr))
	{
		if (new_ctx == CMD_SUB)
			return ((*i) += 2, ctx_push(ctx, new_ctx));
	}
	return (true);
}

bool	update_ctx_in_dquote(t_ctx_stack *ctx, char *input_ptr, size_t *i)
{
	t_lexer_ctx_type	new_ctx;

	if (input_ptr[0] == '"')
		return ((*i)++, ctx_pop(ctx), true);
	else if (is_ctx_opener(&new_ctx, input_ptr))
	{
		if (new_ctx == PARAM)
			return ((*i) += 2, ctx_push(ctx, new_ctx));
		else if (new_ctx == CMD_SUB)
			return ((*i) += 2, ctx_push(ctx, new_ctx));
		else if (new_ctx == ARITH)
			return ((*i) += 3, ctx_push(ctx, new_ctx));
	}
	return (true);
}

bool	update_ctx_in_no_ctx(t_ctx_stack *ctx, char *input_ptr, size_t *i)
{
	t_lexer_ctx_type	new_ctx;

	if (is_ctx_opener(&new_ctx, input_ptr))
	{
		if (new_ctx == SQUOTE)   
			return ((*i)++, ctx_push(ctx, new_ctx));
		else if (new_ctx == DQUOTE)   
			return ((*i)++, ctx_push(ctx, new_ctx));
		else if (new_ctx == BACKTICK) 
			return ((*i)++, ctx_push(ctx, new_ctx));
		else if (new_ctx == CMD_SUB)  
			return ((*i) += 2, ctx_push(ctx, new_ctx));
		else if (new_ctx == ARITH)    
			return ((*i) += 3, ctx_push(ctx, new_ctx));
		else if (new_ctx == PARAM)    
			return ((*i) += 2, ctx_push(ctx, new_ctx));
	}
	return (true);
}
