/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _stack.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 17:42:49 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/18 17:47:06 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _STACK_H
# define _STACK_H

# include "../../_lexer.h"

t_lexer_ctx	ctx_pop(t_ctx_stack *stack);
t_lexer_ctx	ctx_view(t_ctx_stack *stack);
void		free_ctx_stack(t_ctx_stack *stack);
t_error		ctx_update_nesting(t_ctx_stack *stack, int value);
t_error		ctx_push(t_ctx_stack *stack, t_lexer_ctx_type ctx);

#endif
