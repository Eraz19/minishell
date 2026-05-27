/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 17:17:52 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/19 10:41:11 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "_backslash.h"

void	consume_line_continuation(t_lexer *lexer)
{
	char	*input_ptr;

	input_ptr = lexer->input + lexer->i;
	ft_memmove(input_ptr, input_ptr + 2, str_len(input_ptr + 2));
	input_ptr[str_len(input_ptr + 2)] = '\0';
	if ((size_t)lexer->i == lexer->start_token_i)
		lexer->total_removed_count += 2;
	else
		lexer->current_removed_count += 2;
}
