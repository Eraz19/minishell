/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_take_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:06:43 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 13:06:44 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_type.h"
#include <assert.h>	// DEBUG

void	parser_take_token(t_parser *parser, size_t index, t_token *dst)
{
	assert(parser != NULL);
	assert(dst != NULL);
	token_pool_take(&parser->token_pool, index, dst);
}
