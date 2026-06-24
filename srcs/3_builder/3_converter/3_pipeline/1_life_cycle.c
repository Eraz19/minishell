#include "converter_priv.h"
#include <stdlib.h>

void	ast_pipeline_init(t_ast_pipeline *pipeline)
{
	(void)vector_init(&pipeline->commands, sizeof(t_ast_command), 0);
	pipeline->negated = false;
}

void	ast_pipeline_free(void *pipeline)
{
	t_ast_pipeline	*pipe;

	pipe = (t_ast_pipeline *)pipeline;
	vector_free(&pipe->commands, ast_command_free);
	pipe->negated = false;
}
