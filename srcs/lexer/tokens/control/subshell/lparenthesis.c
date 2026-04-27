/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lparenthesis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 12:03:17 by adouieb           #+#    #+#             */
/*   Updated: 2026/04/27 12:03:58 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../../_lexer.h"

t_lexer_token	*lparenthesis(size_t offset)
{
	t_lexer_token	*res;

	res = malloc(sizeof(t_lexer_token));
	if (res == NULL)
		return (NULL);
	res->offset = offset;
	res->type = CONTROL_;
	res->id.control_ = LPARENTHESIS;
	if (buff_init(&res->value, 0) == false)
		return (free(res), NULL);
	return (res);
}

bool	is_lparenthesis(t_raw_string input_ptr)
{
	return (input_ptr[0] == '(');
}
