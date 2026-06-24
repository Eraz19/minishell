#include "converter_priv.h"
#include <stdlib.h>

void	ast_loop_init(t_ast_loop *loop)
{
	ast_list_init(&loop->condition);
	ast_list_init(&loop->body);
	loop->condition_must_be_true = false;
}

void	ast_loop_free(t_ast_loop *loop)
{
	ast_list_free(&loop->condition);
	ast_list_free(&loop->body);
	loop->condition_must_be_true = false;
}
