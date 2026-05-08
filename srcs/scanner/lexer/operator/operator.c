/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 16:04:00 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/07 16:36:38 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../_scanner.h"

bool	is_operator(t_token_type *type, int *value, char *input_ptr)
{
	return (is_semi_operator(type, input_ptr) ||
		is_ampersand_operator(type, input_ptr) ||
		is_pipe_operator(type, input_ptr) ||
		is_less_operator(type, input_ptr) ||
		is_great_operator(type, input_ptr) ||
		is_newline_operator(type, input_ptr) ||
		is_parenthesis_operator(type, input_ptr) ||
		is_io_number_operator(type, value, input_ptr));
}
