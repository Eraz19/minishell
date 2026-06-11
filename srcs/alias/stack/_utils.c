/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 15:20:42 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/11 17:51:04 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "alias_stack_.h"

t_error	alias_stack_push(t_alias_stack *stack, char *item)
{
	if (!vector_push(stack, &item))
		return (ERR_LIBC);
	return (ERR_NO);
}

void	alias_stack_pop(t_alias_stack *stack)
{
	char	*item;

	if (stack->len == 0)
		return ;
	vector_pop(stack, &item);
	if (item != NULL)
		free(item);
}

bool	alias_stack_contains(t_alias_stack *stack, char *word)
{
	size_t	i;

	i = 0;
	while (i < stack->len)
	{
		if (str_ncmp(((char **)stack->data)[i], word, str_len(word) + 1) == 0)
			return (true);
		i++;
	}
	return (false);
}
