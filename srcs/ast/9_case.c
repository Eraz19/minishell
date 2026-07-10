#include "ast.h"
# include <assert.h>	// DEBUG

void	ast_case_init(t_ast_case *case_node)
{
	assert(case_node != NULL);
	token_init(&case_node->word);
	vector_init(&case_node->patterns, sizeof(t_token_pool), 0);
	vector_init(&case_node->bodies, sizeof(t_ast_list), 0);
	vector_init(&case_node->fallthrough, sizeof(bool), 0);
}

void	ast_case_free(t_ast_case *case_node)
{
	assert(case_node != NULL);
	token_free(&case_node->word);
	vector_free(&case_node->patterns, token_pool_free_void);
	vector_free(&case_node->bodies, ast_list_free);
	vector_free(&case_node->fallthrough, NULL);
}
