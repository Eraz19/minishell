#include "token.h"
#include "ast.h"
#include <assert.h>

t_error	token_dup(t_token *dst, const t_token *src)
{
	t_error	err;

	if (!string_dup(&dst->value, &src->value))
		return (error_sys());
	err = context_stack_dup(&dst->contexts, &src->contexts);
	if (err.type)
		return (string_free(&dst->value), err);
	dst->type = src->type;
	dst->index = src->index;
	dst->assignment_offset = src->assignment_offset;
	return (ast_vector_dup(&dst->ast_vector, &src->ast_vector));
}

t_error	token_dup_void(void *dst, const void *src)
{
	return (token_dup(dst, src));
}

void	token_transfer(t_token *dst, t_token *src)
{
	assert(dst != NULL);
	assert(src != NULL);
	*dst = *src;
	token_init(src);
}
