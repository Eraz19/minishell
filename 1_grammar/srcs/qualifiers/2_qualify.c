/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_qualify.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 14:51:19 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 22:42:00 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grammar_qualifiers.h"
#include <stdlib.h>

void	qualify_2(
			char *token_value,
			ssize_t assignment_offset,
			t_symbol *out_symbol)
{
	(void)token_value;
	(void)assignment_offset;
	*out_symbol = SYM_WORD;
}
