#include "ast.h"
#include "utils.h"
# include <assert.h>	// DEBUG

void	ast_if_init(t_ast_if *if_node)
{
	assert(if_node != NULL);
	vector_init(&if_node->conditions, sizeof(t_ast_list), 0);
	vector_init(&if_node->bodies, sizeof(t_ast_list), 0);
	ast_list_init(&if_node->else_body);
	if_node->has_else = false;
}

t_error	ast_if_dup(void *dst, const void *src)
{
	t_ast_if		*dst_if;
	const t_ast_if	*src_if;
	t_error			err;

	dst_if = (t_ast_if *)dst;
	src_if = (const t_ast_if *)src;
	ast_if_init(dst_if);
	err = vector_deep_dup(&dst_if->conditions, &src_if->conditions,
			ast_list_dup, ast_list_free);
	if (err.type == ERR_NO)
		err = vector_deep_dup(&dst_if->bodies, &src_if->bodies,
			ast_list_dup, ast_list_free);
	if (err.type == ERR_NO)
		err = ast_list_dup(&dst_if->else_body, &src_if->else_body);
	if (err.type)
		return (ast_if_free(dst_if), err);
	dst_if->has_else = src_if->has_else;
	return (error(ERR_NO));
}

void	ast_if_free(t_ast_if *if_node)
{
	assert(if_node != NULL);
	vector_free(&if_node->conditions, ast_list_free);
	vector_free(&if_node->bodies, ast_list_free);
	ast_list_free(&if_node->else_body);
	if_node->has_else = false;
}
