/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 15:24:48 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/04 15:50:49 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "scanner.h"

t_token	*token_(char *input_ptr, size_t len)
{
	char	*str;
	t_token	*res;

	res = malloc(sizeof(t_token));
	if (res == NULL)
		return (NULL);
	res->type = TOKEN;
	res->input = input_ptr;
	if (buff_init(&res->value, 0) == false)
		return (free(res), NULL);
	str = str_sub(input_ptr, 0, len);
	if (str == NULL)
		return (free(res), NULL);
	if (buff_append(&res->value, str, (long)len) == false)
		return (free(res), NULL);
	return (res);
}
