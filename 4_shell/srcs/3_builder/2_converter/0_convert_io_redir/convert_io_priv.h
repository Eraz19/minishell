/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_io_priv.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:07:30 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 13:07:31 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONVERT_IO_PRIV_H
# define CONVERT_IO_PRIV_H

# include "parser_type.h"
# include "ast.h"

t_error	convert_io_file_or_here(
			t_parser *parser,
			t_cst_node *io_file_node,
			t_ast_redirection *out);

#endif
