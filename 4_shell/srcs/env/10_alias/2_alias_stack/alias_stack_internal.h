/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_stack_internal.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:14:26 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 14:14:27 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALIAS_STACK_INTERNAL_H
# define ALIAS_STACK_INTERNAL_H

# include "libft.h"
# include "error.h"

// vector of t_string;
typedef t_vector	t_alias_stack;

// life cycle

void	alias_stack_init(t_alias_stack *stack);
void	alias_stack_clear(t_alias_stack *stack);
void	alias_stack_free(t_alias_stack *stack);

// ops

t_error	alias_stack_push(t_alias_stack *stack, const t_string *name);
bool	alias_stack_contains(const t_alias_stack *stack, const t_string *name);
void	alias_stack_pop(t_alias_stack *stack);

#endif
