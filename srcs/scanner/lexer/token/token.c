/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 15:59:23 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/07 16:37:41 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../_scanner.h"

void	free_token(t_token **token_ptr)
{
	if (token_ptr == NULL)
		return ;
	buff_free(&(*token_ptr)->value);
	**token_ptr = (t_token){0};
	free(*token_ptr);
	*token_ptr = NULL;
}

t_token	*create_token(char *content, size_t offset, t_token_type type)
{
	t_token	*res;

	res = malloc(sizeof(t_token));
	if (res == NULL)
		return (NULL);
	res->type = type;
	res->offset = offset;
	if (buff_init(&res->value, 0) == false)
		return (free(res), NULL);
	if (content != NULL)
		buff_append(&res->value, content, (long)str_len(content));
	return (res);
}
