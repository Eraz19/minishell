#include "converter_priv.h"
#include <stdlib.h>

void	ast_case_init(t_ast_case *case_node)
{
	case_node->word = NULL;
	vector_init(&case_node->patterns, sizeof(t_vector), 0);
	vector_init(&case_node->bodies, sizeof(t_ast_list), 0);
	vector_init(&case_node->fallthrough, sizeof(bool), 0);
}

static void	ast_case_free_pattern(void *pattern)
{
	vector_free(pattern, NULL);
}

void	ast_case_free(t_ast_case *case_node)
{
	case_node->word = NULL;
	vector_free(&case_node->patterns, ast_case_free_pattern);
	vector_free(&case_node->bodies, ast_list_free);
	vector_free(&case_node->fallthrough, NULL);
}
