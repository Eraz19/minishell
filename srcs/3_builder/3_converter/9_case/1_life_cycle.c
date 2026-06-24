#include "converter_priv.h"
#include <stdlib.h>

void	ast_case_init(t_ast_case *case_node)
{
	(void)buff_init(&case_node->word, 0, NULL, -1);
	vector_init(&case_node->patterns, sizeof(t_vector), 0);
	vector_init(&case_node->bodies, sizeof(t_ast_list), 0);
	vector_init(&case_node->fallthrough, sizeof(bool), 0);
}

static void	ast_case_free_pattern(void *pattern)
{
	t_vector	*pattern_vec;

	pattern_vec = (t_vector *)pattern;
	vector_free(pattern_vec, buff_free_void);
}

void	ast_case_free(t_ast_case *case_node)
{
	buff_free(&case_node->word);
	vector_free(&case_node->patterns, ast_case_free_pattern);
	vector_free(&case_node->bodies, ast_list_free);
	vector_free(&case_node->fallthrough, NULL);
}
