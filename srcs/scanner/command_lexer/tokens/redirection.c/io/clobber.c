/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clobber.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 12:21:44 by adouieb           #+#    #+#             */
/*   Updated: 2026/04/29 18:03:28 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../../_lexer.h"

t_token	*clobber(size_t offset)
{
	t_token	*res;

	res = malloc(sizeof(t_token));
	if (res == NULL)
		return (NULL);
	res->offset = offset;
	res->type = CLOBBER;
	if (buff_init(&res->value, 0) == false)
		return (free(res), NULL);
	return (res);
}

bool	is_clobber(char *input_ptr)
{
	return (input_ptr[0] == '>' && input_ptr[1] == '|');
}
