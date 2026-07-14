#include "ast.h"
# include <assert.h>	// DEBUG

void	ast_and_or_init(t_ast_and_or *and_or)
{
	assert(and_or != NULL);
	vector_init(&and_or->pipelines, sizeof(t_ast_pipeline), 0);
	vector_init(&and_or->next_on_success, sizeof(bool), 0);
}

void	ast_and_or_free(void *and_or)
{
	t_ast_and_or	*and_or_node;

	assert(and_or != NULL);
	and_or_node = (t_ast_and_or *)and_or;
	vector_free(&and_or_node->pipelines, ast_pipeline_free);
	vector_free(&and_or_node->next_on_success, NULL);
}
