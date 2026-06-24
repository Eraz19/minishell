#include "converter_priv.h"
#include <stdlib.h>

void	ast_for_init(t_ast_for *for_node)
{
	(void)buff_init(&for_node->var_name, 0, NULL, -1);
	vector_init(&for_node->words, sizeof(t_buff), 0);
	ast_list_init(&for_node->body);
}

void	ast_for_free(t_ast_for *for_node)
{
	buff_free(&for_node->var_name);
	vector_free(&for_node->words, buff_free_void);
	ast_list_free(&for_node->body);
}
