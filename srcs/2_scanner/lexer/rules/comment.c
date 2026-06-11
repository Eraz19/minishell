/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 15:39:53 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/10 17:57:16 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_rules_.h"

bool	is_comment(t_lexer *state)
{
	return (state->input.str[state->input.i] == '#');
}

void	lexer_rule_comment(t_lexer *state)
{
	while (state->input.str[state->input.i] != '\0' &&
		state->input.str[state->input.i] != '\n')
		state->input.i++;
}
