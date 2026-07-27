#include "cmd_assign_priv.h"
#include "env.h"

t_error	cmd_assignment_check(const t_token *token)
{
	char		c;
	bool		is_readonly;
	t_error		err;

	c = token->value.data[token->assignment_offset];
	token->value.data[token->assignment_offset] = '\0';
	err = env_is_readonly(token->value.data, &is_readonly);
	if (err.type == ERR_NO && is_readonly == true)
	{
		err = error(ERR_VAR_READ_ONLY);
		err = error_print(err, NULL, "%s", token->value.data, NULL, NULL);
	}
	token->value.data[token->assignment_offset] = c;
	return (err);
}
