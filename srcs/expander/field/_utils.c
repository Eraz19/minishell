#include "expander_field_.h"

t_error	expander_fields_push(t_expander_fields *fields, t_expander_word item)
{
	if (!vector_push(fields, &item))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	expander_fields_pop(t_expander_fields *fields, t_expander_word *item)
{
	if (fields->len == 0)
		return (error(ERR_EMPTY_STACK));
	if (!vector_remove(fields, 0, item))
		return (error_sys());
	return (error(ERR_NO));
}
