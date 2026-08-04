/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:43:47 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 17:43:48 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "field_splitting_.h"

t_error	consume_word_item(t_expander *expander, t_word_item item)
{
	expander->err = word_push(&expander->word_exp, item);
	if (expander->err.type)
		return (expander->err);
	expander->err = word_fpop(&item, &expander->word);
	return (expander->err);
}
