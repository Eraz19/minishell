/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_word.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 14:51:14 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/04 15:20:43 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grammar_qualifiers.h"
#include <stdlib.h>
#include <assert.h>

void	qualify_word(
			char *token_value,
			ssize_t assignment_offset,
			t_symbol *out_symbol)
{
	assert(out_symbol != NULL);
	(void)token_value;
	(void)assignment_offset;
	*out_symbol = SYM_WORD;
}
