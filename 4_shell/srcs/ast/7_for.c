#include "ast.h"
#include "utils.h"
# include <assert.h>	// DEBUG

void	ast_for_init(t_ast_for *for_node)
{
	assert(for_node != NULL);
	token_init(&for_node->var_name);
	token_pool_init(&for_node->words);
	ast_list_init(&for_node->body);
	for_node->has_in = false;
}

t_error	ast_for_dup(void *dst, const void *src)
{
	t_ast_for		*dst_for;
	const t_ast_for	*src_for;
	t_error			err;

	dst_for = (t_ast_for *)dst;
	src_for = (const t_ast_for *)src;
	ast_for_init(dst_for);
	dst_for->has_in = src_for->has_in;
	err = token_dup(&dst_for->var_name, &src_for->var_name);
	if (err.type == ERR_NO)
		err = vector_deep_dup(&dst_for->words, &src_for->words,
				token_dup_void, token_free_void);
	if (err.type == ERR_NO)
		err = ast_list_dup(&dst_for->body, &src_for->body);
	if (err.type)
		return (ast_for_free(dst_for), err);
	return (error(ERR_NO));
}

void	ast_for_free(t_ast_for *for_node)
{
	assert(for_node != NULL);
	token_free(&for_node->var_name);
	token_pool_free(&for_node->words);
	ast_list_free(&for_node->body);
	for_node->has_in = false;
}
