#include "ast.h"
# include <assert.h>	// DEBUG

void	ast_loop_init(t_ast_loop *loop)
{
	assert(loop != NULL);
	ast_list_init(&loop->condition);
	ast_list_init(&loop->body);
	loop->condition_must_be_true = false;
}

void	ast_loop_free(t_ast_loop *loop)
{
	assert(loop != NULL);
	ast_list_free(&loop->condition);
	ast_list_free(&loop->body);
	loop->condition_must_be_true = false;
}
