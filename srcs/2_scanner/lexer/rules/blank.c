/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blank.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 15:38:40 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/11 18:56:21 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_rules_.h"

t_error	lexer_rule_blank(t_lexer *state, t_token *token)
{
	if (state->token.type != NONE)
		return (lexer_delimit_token(state, token));
	while (is_blank(state->input.str[state->input.i]) &&
		state->input.str[state->input.i] != '\0')
		state->input.i++;
	return (state->err);
}
