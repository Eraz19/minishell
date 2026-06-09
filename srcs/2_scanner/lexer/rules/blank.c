/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blank.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 15:38:40 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/05 20:19:47 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "__lexer_rules.h"

bool	is_blank(t_lexer *state)
{
	return (state->input[state->i] == ' ' || state->input[state->i] == '\t');
}

t_error	lexer_rule_blank(t_lexer *state, t_token *token)
{
	if (state->token.type != NONE)
		return (lexer_delimit_token(state, token));
	while (is_blank(state) && state->input[state->i] != '\0')
		state->i++;
	return (state->err);
}
