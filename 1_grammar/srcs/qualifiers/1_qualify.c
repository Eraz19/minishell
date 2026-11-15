/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_qualify.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 14:51:17 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 22:41:55 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grammar_qualifiers.h"
#include "grammar_qualifiers_priv.h"
#include <stdlib.h>

void	qualify_1(
			char *token_value,
			ssize_t assignment_offset,
			t_symbol *out_symbol)
{
	if (!qualify_try_reserved_word(token_value, assignment_offset, out_symbol))
		*out_symbol = SYM_WORD;
}
