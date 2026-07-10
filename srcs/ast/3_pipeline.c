#include "ast.h"
# include <assert.h>	// DEBUG

void	ast_pipeline_init(t_ast_pipeline *pipeline)
{
	assert(pipeline != NULL);
	(void)vector_init(&pipeline->commands, sizeof(t_ast_command), 0);
	pipeline->negated = false;
}

void	ast_pipeline_free(void *pipeline)
{
	t_ast_pipeline	*pipe;

	assert(pipeline != NULL);
	pipe = (t_ast_pipeline *)pipeline;
	vector_free(&pipe->commands, ast_command_free);
	pipe->negated = false;
}
