/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_stack_.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 14:31:35 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/11 17:51:18 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALIAS_STACK__H
# define ALIAS_STACK__H

# include "error.h"
# include "libft.h"
# include "alias.h"

void	alias_stack_init(t_alias_stack *stack);
void	alias_stack_free(t_alias_stack *stack);

void	alias_stack_pop(t_alias_stack *stack);
t_error	alias_stack_push(t_alias_stack *stack, char *item);
bool	alias_stack_contains(t_alias_stack *stack, char *word);

#endif
