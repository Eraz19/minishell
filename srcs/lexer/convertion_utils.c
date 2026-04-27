/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convertion_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 23:33:14 by adouieb           #+#    #+#             */
/*   Updated: 2026/04/27 15:11:08 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "_lexer.h"

static void	convert_lexer_token_content(t_token *res, t_lexer_token *token)
{
	res->offset = token->offset;
	res->value = token->value;
	if (token->type == DEFAULT_)
	{
		res->type = DEFAULT;
		res->id.default_ = token->id.default_;
	}
	else if (token->type == CONTROL_)
	{
		res->type = CONTROL;
		res->id.control_ = token->id.control_;
	}
	else if (token->type == REDIRECTION_)
	{
		res->type = REDIRECTION;
		res->id.redirection_ = token->id.redirection_;
	}
}

t_token	*from_lexer_token(t_lexer_token **token_ptr)
{
	t_token			*res;
	t_lexer_token	*token;

	if (token_ptr == NULL || *token_ptr == NULL)
		return (NULL);
	res = malloc(sizeof(t_token));
	if (res == NULL)
		return (NULL);
	token = *token_ptr;
	res->rule = -1;
	convert_lexer_token_content(res, token);
	*token = (t_lexer_token){0};
	free(token);
	return (res);
}
