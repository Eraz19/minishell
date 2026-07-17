#include "ast.h"

void	ast_vector_init(t_ast_vector *ast_vector)
{
	(void)vector_init(ast_vector, sizeof(t_ast_root), 0);
}

t_error	ast_vector_get(
			const t_ast_vector *ast_vector,
			size_t index,
			t_ast_root **out_ast_root)
{
	if (index >= ast_vector->len)
		return (error_print(error(ERR_INTERNAL),
					"ast vector doesn't contain required index", NULL, NULL));
	*out_ast_root = &((t_ast_root *)ast_vector->data)[index];
	return (error(ERR_NO));
}

t_error	ast_vector_push(t_ast_vector *ast_vector, t_ast_root *ast_root)
{
	if (!vector_push(ast_vector, ast_root))
		return (error_sys());
	return (error(ERR_NO));
}

void	ast_vector_free(t_ast_vector *ast_vector)
{
	vector_free(ast_vector, ast_root_free_void);
}

t_error	ast_vector_dup(t_ast_vector *dst, const t_ast_vector *src)
{
	size_t		i;
	t_ast_root	*root_src;
	t_ast_root	*root_dst;
	t_error		err;

	if (!vector_dup(dst, src))
		return (error_sys());
	i = 0;
	while (i < dst->len)
	{
		(void)ast_vector_get(dst, i, &root_dst);
		(void)ast_vector_get(dst, i, &root_src);
		err = ast_root_dup(root_dst, root_src);
		if (err.type)
		{
			// TODO: free already dup items
			vector_free(dst, NULL);
		}
		i++;
	}
	return (error(ERR_NO));
}
