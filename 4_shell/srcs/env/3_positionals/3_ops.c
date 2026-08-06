/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_ops.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:10:20 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 14:10:21 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "positionals.h"
#include "positionals_priv.h"
#include <stdlib.h>
#include <assert.h>	// DEBUG

t_error	positionals_push(
	t_positionals_stack *stack,
	t_positionals *positionals)
{
	assert(stack != NULL);
	assert(positionals != NULL);
	if (!vector_push(stack, positionals))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	positionals_pop(t_positionals_stack *stack)
{
	t_positionals	removed;

	assert(stack != NULL);
	assert(stack->len > 1);
	if (stack->len <= 1)
		return (error(ERR_NO));
	if (!vector_pop(stack, &removed))
		return (error_sys());
	positionals_free_item(&removed);
	return (error(ERR_NO));
}

t_error	positionals_replace(
			t_positionals_stack *stack,
			t_positionals *positionals)
{
	t_positionals	removed;

	assert(stack != NULL);
	assert(positionals != NULL);
	assert(stack->len > 0);
	if (stack->len == 0)
		return (error(ERR_VAR_NOT_FOUND));
	if (!vector_pop(stack, &removed))
		return (error_sys());
	positionals_free_item(&removed);
	if (!vector_push(stack, positionals))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	positionals_shift(t_positionals_stack *stack, size_t n)
{
	t_positionals	*positionals;
	t_string		removed;

	assert(stack != NULL);
	if (n == 0)
		return (error(ERR_NO));
	if (stack->len == 0)
		return (error(ERR_INTERNAL));
	positionals = &((t_positionals *)stack->data)[stack->len - 1];
	if (n > positionals->len)
		return (error(ERR_SHIFT_INVALID_VALUE));
	while (n > 0)
	{
		if (!vector_remove(positionals, 0, &removed))
			return (error_sys());
		string_free(&removed);
		n--;
	}
	return (error(ERR_NO));
}
