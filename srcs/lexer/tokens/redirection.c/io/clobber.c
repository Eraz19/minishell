/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clobber.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 12:21:44 by adouieb           #+#    #+#             */
/*   Updated: 2026/04/27 12:22:19 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../../_lexer.h"

t_lexer_token	*clobber_token(size_t offset)
{
	t_lexer_token	*res;

	res = malloc(sizeof(t_lexer_token));
	if (res == NULL)
		return (NULL);
	res->offset = offset;
	res->type = REDIRECTION_;
	res->id.redirection_ = CLOBBER;
	if (buff_init(&res->value, 0) == false)
		return (free(res), NULL);
	return (res);
}

bool	is_clobber(t_raw_string input_ptr)
{
	return (input_ptr[0] == '>' && input_ptr[1] == '|');
}
