/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clobber.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 12:21:44 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/04 17:37:24 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../../_lexer.h"

t_token	*clobber(char *input_ptr)
{
	t_token	*res;

	res = malloc(sizeof(t_token));
	if (res == NULL)
		return (NULL);
	res->type = CLOBBER;
	res->input = input_ptr;
	if (buff_init(&res->value, 0) == false)
		return (free(res), NULL);
	return (res);
}

bool	is_clobber(char *input_ptr)
{
	return (input_ptr[0] == '>' && input_ptr[1] == '|');
}
