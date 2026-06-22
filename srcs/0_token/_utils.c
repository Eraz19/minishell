#include "token.h"

t_error	token_dup(t_token *dst, t_token *src)
{
	dst->type = src->type;
	if (!buff_dup_n(&dst->value, &src->value, src->value.len))
		return (error_sys());
	return (context_stack_dup(&dst->contexts, &src->contexts));
}
