/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_pipeline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:35:24 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 13:35:25 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "utils.h"
#include <assert.h>	// DEBUG

void	ast_pipeline_init(t_ast_pipeline *pipeline)
{
	assert(pipeline != NULL);
	(void)vector_init(&pipeline->commands, sizeof(t_ast_command), 0);
	pipeline->negated = false;
}

t_error	ast_pipeline_dup(void *dst, const void *src)
{
	t_ast_pipeline			*dst_pipeline;
	const t_ast_pipeline	*src_pipeline;
	t_error					err;

	dst_pipeline = (t_ast_pipeline *)dst;
	src_pipeline = (const t_ast_pipeline *)src;
	ast_pipeline_init(dst_pipeline);
	err = vector_deep_dup(&dst_pipeline->commands, &src_pipeline->commands,
			ast_command_dup, ast_command_free);
	if (err.type)
		return (ast_pipeline_free(dst_pipeline), err);
	dst_pipeline->negated = src_pipeline->negated;
	return (error(ERR_NO));
}

void	ast_pipeline_free(void *pipeline)
{
	t_ast_pipeline	*pipe;

	assert(pipeline != NULL);
	pipe = (t_ast_pipeline *)pipeline;
	vector_free(&pipe->commands, ast_command_free);
	pipe->negated = false;
}
