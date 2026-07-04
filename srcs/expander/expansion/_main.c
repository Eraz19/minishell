#include "expansion_.h"

t_error	expansion_push(t_expansion *expansion, t_string *str)
{
	if (!vector_push(expansion, str))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	expansion_bpop(t_string *out, t_expansion *expansion)
{
	if (expansion->len == 0)
		return (error(ERR_EMPTY_STACK));
	if (!vector_pop(expansion, out))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	expansion_fpop(t_string *out, t_expansion *expansion)
{
	if (expansion->len == 0)
		return (error(ERR_EMPTY_STACK));
	if (!vector_remove(expansion, 0, out))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	expansion_get(t_string *out, const t_expansion *expansion, size_t i)
{
	if (i >= expansion->len)
		return (error(ERR_INDEX_OUT_OF_BOUND));
	*out = ((t_string *)expansion->data)[i];
	return (error(ERR_NO));
}
