/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _ctx_stack.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 15:19:15 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/03 15:15:19 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CTX_STACK_H
# define _CTX_STACK_H

# include "error.h"
# include "libft.h"

typedef enum e_scanner_ctx
{
	NONE_,
	SQUOTE,
	DQUOTE,
	DOLLAR_SQUOTE,
	BACKTICK,
	CMD_SUB,
	ARITH,
	PARAM,
}	t_scanner_ctx;

typedef t_vector	t_scanner_ctx_stack;

void	ctx_stack_init(t_scanner_ctx_stack *stack);
void	ctx_stack_free(t_scanner_ctx_stack *stack);

t_error	ctx_stack_pop(t_scanner_ctx_stack *stack);
t_error	ctx_stack_get(t_scanner_ctx_stack *stack, t_scanner_ctx *item);
t_error	ctx_stack_push(t_scanner_ctx_stack *stack, t_scanner_ctx item);

#endif
