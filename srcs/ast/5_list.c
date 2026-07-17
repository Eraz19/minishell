#include "ast.h"
#include "utils.h"
# include <assert.h>	// DEBUG

void	ast_list_init(t_ast_list *list)
{
	assert(list != NULL);
	vector_init(&list->and_ors, sizeof(t_ast_and_or), 0);
	vector_init(&list->asyncs, sizeof(bool), 0);
	list->subshell = false;
}

void	ast_list_free(void *list)
{
	t_ast_list	*list_node;

	assert(list != NULL);
	list_node = (t_ast_list *)list;
	vector_free(&list_node->and_ors, ast_and_or_free);
	vector_free(&list_node->asyncs, NULL);
	list_node->subshell = false;
}

t_error	ast_list_dup(void *dst, const void *src)
{
	t_ast_list			*dst_list;
	const t_ast_list	*src_list;
	t_error				err;

	dst_list = (t_ast_list *)dst;
	src_list = (const t_ast_list *)src;
	ast_list_init(dst_list);
	err = vector_deep_dup(&dst_list->and_ors, &src_list->and_ors,
			ast_and_or_dup, ast_and_or_free);
	if (err.type == ERR_NO &&!vector_dup(&dst_list->asyncs, &src_list->asyncs))
		err = error_sys();
	if (err.type)
		return (ast_list_free(dst_list), err);
	dst_list->subshell = src_list->subshell;
	return (error(ERR_NO));
}

void	ast_root_init(t_ast_root *root)
{
	assert(root != NULL);
	ast_list_init(root);
}

void	ast_root_free(t_ast_root *root)
{
	assert(root != NULL);
	ast_list_free(root);
}

void	ast_root_free_void(void *ast_root)
{
	ast_list_free(ast_root);
}

t_error	ast_root_dup(t_ast_root *dst, const t_ast_root *src)
{
	return (ast_list_dup(dst, src));
}
