/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 16:04:00 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/10 14:41:52 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../_scanner.h"

bool	is_operator(t_lexer *lexer, t_operator_args *args, size_t i)
{
	return (is_semi(lexer, args, i) ||
		is_ampersand(lexer, args, i) ||
		is_pipe(lexer, args, i) ||
		is_less(lexer, args, i) ||
		is_great(lexer, args, i) ||
		is_newline(lexer, args, i) ||
		is_parenthesis(lexer, args, i) ||
		is_io_number(lexer, args, i));
}
