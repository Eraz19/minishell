/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:47:22 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 17:47:23 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "param_braced_.h"

t_error	braced_build_pattern(
			t_expander *expander,
			t_word *operand,
			t_string *out)
{
	t_word	expanded;

	expander->err = expand_operand(expander, operand, &expanded);
	if (expander->err.type)
		return (word_free(&expanded), expander->err);
	expander->err = pattern_from_word(out, &expanded, false);
	return (word_free(&expanded), expander->err);
}
