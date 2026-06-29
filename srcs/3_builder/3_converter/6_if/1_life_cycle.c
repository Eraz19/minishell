#include "converter_priv.h"
#include <stdlib.h>
# include <assert.h>	// DEBUG

void	ast_if_init(t_ast_if *if_node)
{
	assert(if_node != NULL);
	vector_init(&if_node->conditions, sizeof(t_ast_list), 0);
	vector_init(&if_node->bodies, sizeof(t_ast_list), 0);
	ast_list_init(&if_node->else_body);
	if_node->has_else = false;
}

void	ast_if_free(t_ast_if *if_node)
{
	assert(if_node != NULL);
	vector_free(&if_node->conditions, ast_list_free);
	vector_free(&if_node->bodies, ast_list_free);
	ast_list_free(&if_node->else_body);
	if_node->has_else = false;
}
