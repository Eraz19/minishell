/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 15:39:53 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/10 16:53:09 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_rules_.h"

bool	is_comment(t_lexer *state)
{
	return (state->input[state->i] == '#');
}

void	lexer_rule_comment(t_lexer *state)
{
	while (state->input[state->i] != '\0' && state->input[state->i] != '\n')
		state->i++;
}
