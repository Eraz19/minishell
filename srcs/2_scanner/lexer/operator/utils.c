/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 10:12:52 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/01 09:51:33 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_operator.h"

bool	is_in_middle_of_operator(t_lexer *state)
{
	return (state->token.type != NONE && state->token.type != TOKEN);
}
