#include "converter_priv.h"
#include <stdlib.h>

void	ast_list_init(t_ast_list *list)
{
	vector_init(&list->and_ors, sizeof(t_ast_and_or), 0);
	vector_init(&list->asyncs, sizeof(bool), 0);
	list->subshell = false;
}

void	ast_list_free(void *list)
{
	t_ast_list	*list_node;

	list_node = (t_ast_list *)list;
	vector_free(&list_node->and_ors, ast_and_or_free);
	vector_free(&list_node->asyncs, NULL);
	list_node->subshell = false;
}

void	ast_root_init(t_ast_root *root)
{
	ast_list_init(root);
}

void	ast_root_free(t_ast_root *root)
{
	ast_list_free(root);
}

