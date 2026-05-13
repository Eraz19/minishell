/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 17:26:00 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/12 17:26:36 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_lexer.h"

bool	is_comment(t_lexer *lexer, size_t i)
{
	char	*input_ptr;

	input_ptr = lexer->input + i;
	return (lexer->i == i && input_ptr[0] == '#');
}

bool	is_blank(t_lexer *lexer, size_t i)
{
	char	*input_ptr;

	input_ptr = lexer->input + i;
	return (input_ptr[0] == ' ' || input_ptr[0] == '\t');
}
