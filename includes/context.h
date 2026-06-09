/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 17:01:23 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/07 10:57:28 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTEXT_H
# define CONTEXT_H

# include "error.h"
# include "libft.h"

typedef enum e_context
{
	NONE_,
	SQUOTE,
	DQUOTE,
	DOLLAR_SQUOTE,
	BACKTICK,
	CMD_SUB,
	ARITH,
	PARAM,
}	t_context;

typedef t_vector	t_context_stack;

void	context_stack_init(t_context_stack *stack);
void	context_stack_free(t_context_stack *stack);

t_error	context_stack_pop(t_context_stack *stack);
t_error	context_stack_get(t_context_stack *stack, t_context *item);
t_error	context_stack_push(t_context_stack *stack, t_context item);

bool	is_in_context_none_whitelist(char c);
bool	is_context_none_ending(char c, void *_);

bool	is_context_arith_start(char *str);
bool	is_context_arith_ending(char c, void *nesting_depth);

bool	is_context_backtick_start(char *str);
bool	is_in_context_backtick_whitelist(char c);
bool	is_context_backtick_ending(char c, void *_);
bool	is_in_context_backtick_special_whitelist(char c);

bool	is_context_cmd_sub_start(char *str);

bool	is_context_param_start(char *str);
bool	is_in_context_param_whitelist(char c);
bool	is_context_param_ending(char c, void *_);

bool	is_expansion_context(char *str, t_context *context);

bool	is_context_dollar_squote_start(char *str);
bool	is_in_context_dollar_squote_whitelist(char c);
bool	is_context_dollar_squote_ending(char c, void *_);

bool	is_context_dquote_start(char *str);
bool	is_in_context_dquote_whitelist(char c);
bool	is_context_dquote_ending(char c, void *_);

bool	is_context_squote_start(char *str);
bool	is_in_context_squote_whitelist(char c);
bool	is_context_squote_ending(char c, void *_);

bool	is_quoting_ending(char c, t_context context);
bool	is_quoting_context(char *str, t_context *context);
bool	is_in_quoting_whitelist(char c, t_context context);

#endif
