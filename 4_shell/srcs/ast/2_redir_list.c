/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_redir_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:35:15 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 22:48:09 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "utils.h"

void	ast_redir_list_init(t_ast_redir_list *redir_list)
{
	vector_init(redir_list, sizeof(t_ast_redirection), 0);
}

t_error	ast_redir_list_dup(void *dst, const void *src)
{
	return (vector_deep_dup(dst, src, ast_redirection_dup,
			ast_redirection_free));
}

void	ast_redir_list_free(t_ast_redir_list *redir_list)
{
	vector_free(redir_list, ast_redirection_free);
}
