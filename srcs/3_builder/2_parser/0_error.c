#include "error.h"
#include "parser_priv.h"
#include <stdlib.h>

t_error	parser_internal_error(t_error err)
{
	return (error_print(err, "parser", "internal error", NULL, NULL));
}

t_error	parser_invalid_syntax(void)
{
	return (error_print(error(ERR_SYNTAX_INVALID), "parser", NULL, NULL));
}
