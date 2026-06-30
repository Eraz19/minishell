#include "expander_expansion_.h"

t_error	expansion_push(t_expansion *expansion, t_string *str)
{
	if (!vector_push(expansion, str))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	expansion_pop(t_expansion *expansion, t_string *str)
{
	if (expansion->len == 0)
		return (error(ERR_EMPTY_STACK));
	if (!vector_pop(expansion, str))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	expansion_get(
			const t_expansion *expansion,
			size_t index,
			t_string *str)
{
	if (index >= expansion->len)
		return (error(ERR_INDEX_OUT_OF_BOUND));
	*str = ((t_string *)expansion->data)[index];
	return (error(ERR_NO));
}
