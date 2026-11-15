/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_word.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 14:51:14 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 22:41:50 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grammar_qualifiers.h"
#include <stdlib.h>

void	qualify_word(
			char *token_value,
			ssize_t assignment_offset,
			t_symbol *out_symbol)
{
	(void)token_value;
	(void)assignment_offset;
	*out_symbol = SYM_WORD;
}
