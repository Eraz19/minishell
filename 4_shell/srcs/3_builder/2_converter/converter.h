/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:07:56 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 13:08:07 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONVERTER_H
# define CONVERTER_H

# include "error.h"
# include "cst_type.h"
# include "ast.h"
# include "parser_type.h"

t_error	convert_cst_to_ast(
			t_parser *parser,
			t_cst_node *cst_root,
			t_ast_root *ast_root);

#endif
