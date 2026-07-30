#include "ast.h"
#include "utils.h"
# include <assert.h>	// DEBUG

void	ast_and_or_init(t_ast_and_or *and_or)
{
	assert(and_or != NULL);
	vector_init(&and_or->pipelines, sizeof(t_ast_pipeline), 0);
	vector_init(&and_or->next_on_success, sizeof(bool), 0);
}

t_error	ast_and_or_dup(void *dst, const void *src)
{
	t_ast_and_or		*dst_and_or;
	const t_ast_and_or	*src_and_or;
	t_error				err;

	dst_and_or = (t_ast_and_or *)dst;
	src_and_or = (const t_ast_and_or *)src;
	ast_and_or_init(dst_and_or);
	err = vector_deep_dup(&dst_and_or->pipelines, &src_and_or->pipelines,
			ast_pipeline_dup, ast_pipeline_free);
	if (err.type)
		return (ast_and_or_free(dst_and_or), err);
	if (!vector_dup(&dst_and_or->next_on_success, &src_and_or->next_on_success))
	{
		err = error_sys();
		vector_free(&dst_and_or->pipelines, ast_pipeline_free);
		return (ast_and_or_free(dst_and_or), err);
	}
	return (error(ERR_NO));
}

void	ast_and_or_free(void *and_or)
{
	t_ast_and_or	*and_or_node;

	assert(and_or != NULL);
	and_or_node = (t_ast_and_or *)and_or;
	vector_free(&and_or_node->pipelines, ast_pipeline_free);
	vector_free(&and_or_node->next_on_success, NULL);
}
