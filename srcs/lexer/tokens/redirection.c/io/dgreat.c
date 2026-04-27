/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dgreat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 12:23:20 by adouieb           #+#    #+#             */
/*   Updated: 2026/04/27 12:23:48 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../../_lexer.h"

t_lexer_token	*dgreat_token(size_t offset)
{
	t_lexer_token	*res;

	res = malloc(sizeof(t_lexer_token));
	if (res == NULL)
		return (NULL);
	res->offset = offset;
	res->type = REDIRECTION_;
	res->id.redirection_ = DGREAT;
	if (buff_init(&res->value, 0) == false)
		return (free(res), NULL);
	return (res);
}

bool	is_dgreat(t_raw_string input_ptr)
{
	return (input_ptr[0] == '>' && input_ptr[1] == '>');
}
