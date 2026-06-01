/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 15:39:53 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/01 09:53:18 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_token.h"

bool	lexer_comment(t_lexer *state)  // Rule 9
{
	if (state->input[state->i] == '#')
	{
		while (state->input[state->i] != '\0' && state->input[state->i] != '\n')
			state->i++;
		return (true);
	}
	return (false);
}
