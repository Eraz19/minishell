/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lessgreat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 12:22:33 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/04 17:37:45 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../../_lexer.h"

t_token	*lessgreat(char *input_ptr)
{
	t_token	*res;
	
	res = malloc(sizeof(t_token));
	if (res == NULL)
		return (NULL);
	res->type = LESSGREAT;
	res->input = input_ptr;
	if (buff_init(&res->value, 0) == false)
		return (free(res), NULL);
	return (res);
}

bool	is_lessgreat(char *input_ptr)
{
	return (input_ptr[0] == '<' && input_ptr[1] == '>');
}
