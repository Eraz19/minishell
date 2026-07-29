#include "heredoc_body_priv.h"

t_error	error_missing_delimiter(t_body *body)
{
	body->delim.data[body->delim.len - 1] = '\0';
	return (body->err = error_print(error(ERR_NO_DELIM), "heredoc", NULL, "'%s'", body->delim.data));
}
