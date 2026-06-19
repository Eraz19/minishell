/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 10:36:46 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/18 17:37:21 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander_word_.h"

t_error	expander_word_push(t_expander_word *word, t_expander_word_item item)
{
	if (!vector_push(word, &item))
		return (ERR_LIBC);
	return (ERR_NO);
}

t_error	expander_word_pop(t_expander_word *word, t_expander_word_item *item)
{
	if (word->len == 0)
		return (ERR_EMPTY_STACK);
	if (!vector_remove(word, 0, item))
		return (ERR_LIBC);
	return (ERR_NO);
}

t_error	expander_word_dup(t_expander_word *dst, t_expander_word *src)
{
	if (!vector_dup(dst, src))
		return (ERR_LIBC);
	return (ERR_NO);
}

t_error	expander_word_peek(t_expander_word *word, t_expander_word_item *item)
{
	if (word->len == 0)
		return (ERR_EMPTY_STACK);
	return (*item = ((t_expander_word_item *)word->data)[0], ERR_NO);
}
