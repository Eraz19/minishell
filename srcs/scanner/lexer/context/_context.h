/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _context.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 16:01:20 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/13 13:21:44 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CONTEXT_H
# define _CONTEXT_H

# include <stdbool.h>
# include "../_lexer.h"

t_lexer_ctx	ctx_pop(t_ctx_stack *stack);
t_lexer_ctx	ctx_view(t_ctx_stack *stack);
void		free_ctx_stack(t_ctx_stack *stack);
bool		ctx_update_nesting(t_ctx_stack *stack, int value);
bool		ctx_push(t_ctx_stack *stack, t_lexer_ctx_type ctx);

int			update_ctx_none(t_ctx_stack *ctx, char *input_ptr, size_t *i);
int			update_ctx_param(t_ctx_stack *ctx, char *input_ptr, size_t *i);
int			update_ctx_arithm(t_ctx_stack *ctx, char *input_ptr, size_t *i);
int			update_ctx_dquote(t_ctx_stack *ctx, char *input_ptr, size_t *i);
int			update_ctx_squote(t_ctx_stack *ctx, char *input_ptr, size_t *i);
int			update_ctx_backtick(t_ctx_stack *ctx, char *input_ptr, size_t *i);

char 		*DEBUG_ctx_type_stringify(t_lexer_ctx_type type);

#endif
