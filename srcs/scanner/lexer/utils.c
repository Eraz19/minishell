/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 12:23:46 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/18 17:24:18 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "_lexer.h"

void	advance(t_lexer *lexer, size_t offset)
{
	if (lexer->input[lexer->i + 1] == '\0')
		lexer->i += 1;
	else
		lexer->i += offset;
}
