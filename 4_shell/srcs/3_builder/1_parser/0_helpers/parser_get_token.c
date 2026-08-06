/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:06:38 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 13:06:39 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_type.h"
#include <assert.h>	// DEBUG

t_token	*parser_get_token(const t_parser *parser, size_t index)
{
	assert(parser != NULL);
	return (token_pool_get(&parser->token_pool, index));
}
