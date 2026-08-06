/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6a_qualify.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 14:51:25 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 22:42:14 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grammar_qualifiers.h"
#include "libft.h"
#include <stdlib.h>

void	qualify_6a(
			char *token_value,
			ssize_t assignment_offset,
			t_symbol *out_symbol)
{
	(void)assignment_offset;
	if (str_cmp("in", token_value) == 0)
		*out_symbol = SYM_In;
	else
		*out_symbol = SYM_WORD;
}
