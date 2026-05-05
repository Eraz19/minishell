/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lparenthesis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 12:03:17 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/04 15:47:40 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../../_lexer.h"

t_token	*lparenthesis(char *input_ptr)
{
	t_token	*res;

	res = malloc(sizeof(t_token));
	if (res == NULL)
		return (NULL);
	res->input = input_ptr;
	res->type = LPARENTHESIS;
	if (buff_init(&res->value, 0) == false)
		return (free(res), NULL);
	return (res);
}

bool	is_lparenthesis(char *input_ptr)
{
	return (input_ptr[0] == '(');
}
