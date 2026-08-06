/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_case.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:35:35 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 13:35:36 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "utils.h"
#include <assert.h>	// DEBUG

void	ast_case_init(t_ast_case *case_node)
{
	assert(case_node != NULL);
	token_init(&case_node->word);
	vector_init(&case_node->patterns, sizeof(t_token_pool), 0);
	vector_init(&case_node->bodies, sizeof(t_ast_list), 0);
	vector_init(&case_node->fallthrough, sizeof(bool), 0);
}

t_error	ast_case_dup(void *dst, const void *src)
{
	t_ast_case			*dst_case;
	const t_ast_case	*src_case;
	t_error				err;

	dst_case = (t_ast_case *)dst;
	src_case = (const t_ast_case *)src;
	ast_case_init(dst_case);
	err = token_dup(&dst_case->word, &src_case->word);
	if (err.type == ERR_NO)
		err = vector_deep_dup(&dst_case->patterns, &src_case->patterns,
				token_pool_deep_dup, token_pool_free_void);
	if (err.type == ERR_NO)
		err = vector_deep_dup(&dst_case->bodies, &src_case->bodies,
				ast_list_dup, ast_list_free);
	if (err.type == ERR_NO
		&& !vector_dup(&dst_case->fallthrough, &src_case->fallthrough))
		err = error_sys();
	if (err.type)
		return (ast_case_free(dst_case), err);
	return (error(ERR_NO));
}

void	ast_case_free(t_ast_case *case_node)
{
	assert(case_node != NULL);
	token_free(&case_node->word);
	vector_free(&case_node->patterns, token_pool_free_void);
	vector_free(&case_node->bodies, ast_list_free);
	vector_free(&case_node->fallthrough, NULL);
}
