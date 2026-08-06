/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_root.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:36:17 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 13:36:33 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include <assert.h>	// DEBUG

void	ast_root_init(t_ast_root *root)
{
	assert(root != NULL);
	ast_list_init(root);
}

void	ast_root_free(t_ast_root *root)
{
	assert(root != NULL);
	ast_list_free(root);
}

void	ast_root_free_void(void *ast_root)
{
	ast_list_free(ast_root);
}

t_error	ast_root_dup(void *dst, const void *src)
{
	return (ast_list_dup(dst, src));
}
