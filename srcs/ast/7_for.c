#include "ast.h"
# include <assert.h>	// DEBUG

void	ast_for_init(t_ast_for *for_node)
{
	assert(for_node != NULL);
	token_init(&for_node->var_name);
	token_pool_init(&for_node->words);
	ast_list_init(&for_node->body);
}

void	ast_for_free(t_ast_for *for_node)
{
	assert(for_node != NULL);
	token_free(&for_node->var_name);
	token_pool_free(&for_node->words);
	ast_list_free(&for_node->body);
}
