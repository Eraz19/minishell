#include "cmd_assignator_priv.h"
#include "params.h"
#include <stdlib.h>

static inline bool	cmd_assignment_is_target(
							const char *target,
							const char *entry)
{
	size_t	i;

	i = 0;
	while (target[i] == entry[i] && target[i] != '=')
		i++;
	return (target[i] == entry[i]);
}

static inline t_error	cmd_assignment_add_to_envp(
							t_string *expanded,
							t_vector *out_envp)
{
	size_t	i;
	char	**entry;
	t_error	err;

	i = 0;
	while (i < out_envp->len)
	{
		entry = &((char **)out_envp->data)[i];
		if (cmd_assignment_is_target(expanded->data, *entry))
		{
			free(*entry);
			*entry = expanded->data;
			return (error(ERR_NO));
		}
		i++;
	}
	if (!vector_push(out_envp, &expanded->data))
		return (err = error_sys(), string_free(expanded), err);
	return (error(ERR_NO));
}

static inline t_error	cmd_assignment_split(
							t_string *expanded,
							size_t assignment_offset,
							t_string *name,
							t_string *value)
{
	size_t		name_len;
	const char	*value_start;
	size_t		value_len;
	t_error		err;

	name_len = assignment_offset;
	if (!string_init(name, name_len + 1, expanded->data, (long)name_len))
		return (error_sys());
	value_len = expanded->len - assignment_offset - 1;
	value_start = expanded->data + assignment_offset + 1;
	if (!string_init(value, value_len + 1, value_start, (long)value_len))
	{
		err = error_sys();
		string_free(name);
		return (err);
	}
	return (error(ERR_NO));
}

t_error	cmd_assignment_process(
			t_cmd_type cmd_type,
			const t_token *token,
			t_string *expanded,
			t_vector *out_envp)
{
	t_string	name;
	t_string	value;
	t_error		err;

	if (cmd_type == CMD_NONE
		|| cmd_type == CMD_SPECIAL_BUILTIN
		|| cmd_type == CMD_FUNCTION)
	{
		err = cmd_assignment_split(
				expanded,
				(size_t)token->assignment_offset,
				&name,
				&value);
		if (err.type)
			return (string_free(expanded), err);
		err = params_set_variable(&name, &value, false, false);
		string_free(expanded);
		string_free(&name);
		string_free(&value);
		return (err);
	}
	return (cmd_assignment_add_to_envp(expanded, out_envp));
}
