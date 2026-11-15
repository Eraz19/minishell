/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_command_priv.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 17:17:31 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 17:17:32 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONVERT_COMMAND_PRIV_H
# define CONVERT_COMMAND_PRIV_H

# include "error.h"
# include "parser_type.h"
# include "ast.h"

t_error	convert_to_list(
			t_parser *parser,
			const t_cst_node *node,
			t_ast_command *out);
t_error	convert_compound_command_priv(
			t_parser *parser,
			const t_cst_node *compound_command,
			t_ast_command *out);
t_error	convert_to_simple(
			t_parser *parser,
			const t_cst_node *simple,
			t_ast_command *out);
t_error	convert_to_function(
			t_parser *parser,
			const t_cst_node *func,
			t_ast_command *out);

#endif
