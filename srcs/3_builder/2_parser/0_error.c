#include "error.h"
#include <stdlib.h>

t_error	parser_internal_error(void)
{
	return (error_print(error_sys(), "parser", "internal error", NULL, NULL));
}

t_error	parser_invalid_syntax(void)
{
	return (error_print(
		error(ERR_INVALID_SYNTAX),
		"parser",
		NULL,
		NULL));
}
