/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convertion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:48:23 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/05 23:28:38 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <assert.h> // DEBUG
#include "word_.h"

t_error	to_str(t_string *out, const t_word *src, size_t start, size_t len)
{
	size_t		i;
	t_error		err;
	t_word_item	item;

	i = 0;
	string_init(out, 0, NULL, 0);
	if (len == 0)
		if (!string_append_n(out, "", 0))
			return (err = error_sys(), string_free(out), err);
	while (i < len)
	{
		assert(src->len > start + i);
		word_get(&item, src, start + i);
		if (!string_append_n(out, &item.c, 1))
			return (err = error_sys(), string_free(out), err);
		i++;
	}
	return (error(ERR_NO));
}

t_error	from_str(t_word *out, const t_string *src, t_word_item_opt opt)
{
	size_t		i;
	t_error		err;
	t_word_item	item;

	i = 0;
	word_init(out);
	if (!src || src->len == 0)
		return (error(ERR_NO));
	while (i < src->len)
	{
		item = word_item_init(src->data[i], opt);
		err = word_push(out, item);
		if (err.type)
			return (word_free(out), err);
		i++;
	}
	return (error(ERR_NO));
}
