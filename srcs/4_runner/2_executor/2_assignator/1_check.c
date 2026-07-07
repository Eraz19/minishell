#include "cmd_assignator_priv.h"
#include "params.h"

t_error	cmd_assignment_check(const t_token *token)
{
	char		c;
	bool		is_readonly;
	t_error		err;

	c = token->value.data[token->assignment_offset];
	token->value.data[token->assignment_offset] = '\0';
	err = params_is_readonly(token->value.data, &is_readonly);
	if (err.type == ERR_NO && is_readonly == true)
		err = error_print(error(ERR_VAR_READ_ONLY), "executor", NULL,
				"%s", token->value.data);
	token->value.data[token->assignment_offset] = c;
	return (err);
}
