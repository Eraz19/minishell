/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 16:06:40 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/12 18:40:32 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "_context.h"

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

int	update_ctx_param(t_ctx_stack *ctx, char *input_ptr, size_t *i)
{
	t_lexer_ctx_type	new_ctx;

	if (input_ptr[0] == '}')
		return ((*i)++, ctx_pop(ctx), 1);
	else if (is_ctx_opener(&new_ctx, input_ptr))
	{
		if (new_ctx == PARAM)
			return (ft_printf("UPDATE_CTX_IN_PARAM\n"), (*i) += 2, ctx_push(ctx, new_ctx));
		else if (new_ctx == CMD_SUB)
			return (ft_printf("UPDATE_CTX_IN_CMD_SUB\n"), (*i) += 2, ctx_push(ctx, new_ctx));
		else if (new_ctx == ARITH)
			return (ft_printf("UPDATE_CTX_IN_ARITH\n"), (*i) += 3, ctx_push(ctx, new_ctx));
		else if (new_ctx == BACKTICK)
			return (ft_printf("UPDATE_CTX_IN_BACKTICK\n"), (*i) += 1, ctx_push(ctx, new_ctx));
	}
	return (-1);
}

int	update_ctx_arithm(t_ctx_stack *ctx, char *input_ptr, size_t *i)
{
	t_lexer_ctx_type	new_ctx;
	int					nesting_depth;

	nesting_depth = ctx_view(ctx).nesting_depth;
	if (input_ptr[0] == ')' && input_ptr[1] == ')' && nesting_depth == 0)
		return ((*i) += 2, ctx_pop(ctx), 1);
	else if (input_ptr[0] == '(')
		ctx_update_nesting(ctx, 1);
	else if (input_ptr[0] == ')')
		ctx_update_nesting(ctx, -1);
	else if (is_ctx_opener(&new_ctx, input_ptr))
	{
		if (new_ctx == CMD_SUB)
			return (ft_printf("UPDATE_CTX_IN_CMD_SUB\n"), (*i) += 2, ctx_push(ctx, new_ctx));
	}
	return (-1);
}

int	update_ctx_dquote(t_ctx_stack *ctx, char *input_ptr, size_t *i)
{
	t_lexer_ctx_type	new_ctx;

	if (input_ptr[0] == '"')
		return (ft_printf("LEAVE DQUOTE CTX\n"), (*i)++, ctx_pop(ctx), 1);
	else if (is_ctx_opener(&new_ctx, input_ptr))
	{
		if (new_ctx == PARAM)
			return (ft_printf("UPDATE_CTX_IN_PARAM\n"), (*i) += 2, ctx_push(ctx, new_ctx));
		else if (new_ctx == CMD_SUB)
			return (ft_printf("UPDATE_CTX_IN_CMD_SUB\n"), (*i) += 2, ctx_push(ctx, new_ctx));
		else if (new_ctx == ARITH)
			return (ft_printf("UPDATE_CTX_IN_ARITH\n"), (*i) += 3, ctx_push(ctx, new_ctx));
	}
	return (-1);
}

int	update_ctx_none(t_ctx_stack *ctx, char *input_ptr, size_t *i)
{
	t_lexer_ctx_type	new_ctx;

	if (is_ctx_opener(&new_ctx, input_ptr))
	{
		if (new_ctx == SQUOTE)
			return (ft_printf("UPDATE_CTX_IN_SQUOTE\n"), (*i)++, ctx_push(ctx, new_ctx));
		else if (new_ctx == DQUOTE)   
			return (ft_printf("UPDATE_CTX_IN_DQUOTE\n"), (*i)++, ctx_push(ctx, new_ctx));
		else if (new_ctx == BACKTICK) 
			return (ft_printf("UPDATE_CTX_IN_BACKTICK\n"), (*i)++, ctx_push(ctx, new_ctx));
		else if (new_ctx == CMD_SUB)  
			return (ft_printf("UPDATE_CTX_IN_CMD_SUB\n"), (*i) += 2, ctx_push(ctx, new_ctx));
		else if (new_ctx == ARITH)    
			return (ft_printf("UPDATE_CTX_IN_ARITH\n"), (*i) += 3, ctx_push(ctx, new_ctx));
		else if (new_ctx == PARAM)    
			return (ft_printf("UPDATE_CTX_IN_PARAM\n"), (*i) += 2, ctx_push(ctx, new_ctx));
	}
	return (-1);
}
