/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlessdash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 12:15:21 by adouieb           #+#    #+#             */
/*   Updated: 2026/04/29 18:01:55 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../../_lexer.h"

t_token	*dlessdash(size_t offset)
{
	t_token	*res;

	res = malloc(sizeof(t_token));
	if (res == NULL)
		return (NULL);
	res->offset = offset;
	res->type = DLESSDASH;
	if (buff_init(&res->value, 0) == false)
		return (free(res), NULL);
	return (res);
}

bool	is_dlessdash(char *input_ptr)
{
	return (input_ptr[0] == '<' && input_ptr[1] == '<' && input_ptr[2] == '-');
}
