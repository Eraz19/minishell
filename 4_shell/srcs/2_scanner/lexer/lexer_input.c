/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:14:18 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 16:14:19 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_priv.h"

void	bind_lexer_input(t_lexer *lexer)
{
	lexer_input_stack_get_last(&lexer->input_stack, &lexer->input);
}
