/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_read_ps2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:15:24 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/05 18:51:20 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"
#include "scanner.h"

t_error	read_and_propagate_ps2(t_scanner *scanner)
{
	char		*continuation;
	t_scanner	*parent_scanner;

	if (scanner->mode != SCAN_MODE_CMD_SUB && scanner->mode != SCAN_MODE_STDIN)
		return (scanner->err = error(ERR_POSIX_SYNTAX));
	scanner->err = reader_read_ps2(&scanner->lexer.input->str);
	if (scanner->err.type)
		return (scanner->err);
	parent_scanner = scanner->parent_scanner;
	while (parent_scanner != NULL)
	{
		continuation = scanner->lexer.input->str.data + scanner->lexer.input->i;
		if (!string_append_n(
				&parent_scanner->lexer.input->str, continuation, -1))
			return (scanner->err = error_sys());
		parent_scanner = parent_scanner->parent_scanner;
	}
	return (scanner->err);
}
