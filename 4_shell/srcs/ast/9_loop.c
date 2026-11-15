/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_loop.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:35:33 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 22:48:56 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void	ast_loop_init(t_ast_loop *loop)
{
	ast_list_init(&loop->condition);
	ast_list_init(&loop->body);
	loop->condition_must_be_true = false;
}

t_error	ast_loop_dup(void *dst, const void *src)
{
	t_ast_loop			*dst_loop;
	const t_ast_loop	*src_loop;
	t_error				err;

	dst_loop = (t_ast_loop *)dst;
	src_loop = (const t_ast_loop *)src;
	ast_loop_init(dst_loop);
	err = ast_list_dup(&dst_loop->condition, &src_loop->condition);
	if (err.type == ERR_NO)
		err = ast_list_dup(&dst_loop->body, &src_loop->body);
	if (err.type)
		return (ast_loop_free(dst_loop), err);
	dst_loop->condition_must_be_true = src_loop->condition_must_be_true;
	return (error(ERR_NO));
}

void	ast_loop_free(t_ast_loop *loop)
{
	ast_list_free(&loop->condition);
	ast_list_free(&loop->body);
	loop->condition_must_be_true = false;
}
