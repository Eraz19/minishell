#include "field_.h"

t_error	fields_push(t_fields *fields, t_word item)
{
	if (!vector_push(fields, &item))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	fields_fpop(t_word *out, t_fields *fields)
{
	if (fields->len == 0)
		return (error(ERR_EMPTY_STACK));
	if (!vector_remove(fields, 0, out))
		return (error_sys());
	return (error(ERR_NO));
}
