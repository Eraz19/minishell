/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:48:20 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/06 22:52:55 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "word_.h"

t_error	word_push(t_word *word, t_word_item item)
{
	if (!vector_push(word, &item))
		return (error_sys());
	return (error(ERR_NO));
}

void	word_fpop(t_word_item *out, t_word *word)
{
	vector_remove(word, 0, out);
}

t_error	word_remove(t_word *word, size_t start, size_t len)
{
	size_t		i;
	t_word_item	item;

	i = 0;
	while (i < len)
	{
		if (word->len <= start)
			return (error(ERR_NO));
		if (!vector_remove(word, start, &item))
			return (error(ERR_NO));
		i++;
	}
	return (error(ERR_NO));
}

t_error	word_dup(t_word *out, t_word *src)
{
	if (!vector_dup(out, src))
		return (error_sys());
	return (error(ERR_NO));
}

void	word_get(t_word_item *out, const t_word *word, size_t index)
{
	*out = ((t_word_item *)word->data)[index];
}
