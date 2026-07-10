#include "token.h"

t_error	token_dup(t_token *const dst, const t_token *src)
{
	dst->type = src->type;
	if (!string_dup(&dst->value, &src->value))
		return (error_sys());
	dst->index = src->index;
	dst->assignment_offset = src->assignment_offset;
	return (context_stack_dup(&dst->contexts, &src->contexts));
}

t_error	token_deep_copy(t_token *dst, const t_token *src)
{
	t_error	err;

	err = token_dup(dst, src);
	if (err.type)
		return (err);
	dst->index.start = -1;
	dst->index.end = -1;
	dst->index.error = -1;
	return (err);
}
