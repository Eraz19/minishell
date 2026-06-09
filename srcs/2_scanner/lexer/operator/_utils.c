/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:04:22 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/05 20:17:26 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "__lexer_operator.h"

bool	is_in_middle_of_operator(t_lexer *state)
{
	return (state->token.type != NONE && state->token.type != TOKEN);
}
