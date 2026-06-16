/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 15:20:42 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/16 12:59:10 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "__alias_stack.h"

t_error	alias_stack_push(t_alias_stack *stack, char *item)
{
	if (!vector_push(stack, &item))
		return (error_sys());
	return (error(ERR_NO));
}

bool	alias_stack_contains(t_alias_stack *stack, char *word)
{
	size_t	i;

	i = 0;
	while (i < stack->len)
	{
		if (str_ncmp(((char **)stack->data)[i], word, str_len(word)) == 0)
			return (true);
		i++;
	}
	return (false);
}
