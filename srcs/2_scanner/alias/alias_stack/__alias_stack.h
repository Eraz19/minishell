/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __alias_stack.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 14:31:35 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/08 14:39:35 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ALIAS_STACK_H
# define __ALIAS_STACK_H

# include "error.h"
# include "libft.h"

typedef t_vector	t_alias_stack;

void	alias_stack_init(t_alias_stack *stack);
void	alias_stack_free(t_alias_stack *stack);

t_error	alias_stack_push(t_alias_stack *stack, char *item);
bool	alias_stack_contains(t_alias_stack *stack, char *word);

#endif
