/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_convert_redirect_list.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:07:28 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 22:47:30 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "converter_priv.h"

/*
redirect_list    :               io_redirect
                 | redirect_list io_redirect
                 ;
*/
t_error	convert_redirection_add_list(
			t_parser *parser,
			const t_cst_node *redirect_list,
			t_ast_redir_list *out)
{
	size_t				i;
	t_cst_node			*child;
	t_error				err;

	err = error(ERR_NO);
	i = 0;
	while (i < redirect_list->child_count && err.type == ERR_NO)
	{
		child = redirect_list->children[i];
		if (child->symbol == SYM_redirect_list)
			err = convert_redirection_add_list(parser, child, out);
		else if (child->symbol == SYM_io_redirect)
			err = convert_redirection_add(parser, child, out);
		i++;
	}
	return (err);
}
