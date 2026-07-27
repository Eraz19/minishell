#include "cmd_assign_priv.h"
#include "env.h"
#include "utils.h"
#include "xtrace.h"
#include <stdlib.h>
# include <assert.h>

#define PATH_TARGET		"PATH="
#define PATH_TARGET_LEN	5

static inline t_error	cmd_assignment_add_to_envp(
							t_string *expanded,
							t_cmd *cmd,
							bool *path_is_temporary)
{
	size_t	i;
	char	**entry;
	t_error	err;

	if (str_ncmp(expanded->data, PATH_TARGET, PATH_TARGET_LEN) == 0)
		*path_is_temporary = true;
	i = 0;
	while (i < cmd->envp.len)
	{
		entry = &((char **)cmd->envp.data)[i];
		if (assignment_is_same_name(expanded->data, *entry))
		{
			free(*entry);
			*entry = expanded->data;
			expanded->cap = 0;
			return (error(ERR_NO));
		}
		i++;
	}
	if (!vector_push(&cmd->envp, &expanded->data))
		return (err = error_sys(), string_free(expanded), err);
	expanded->cap = 0;
	return (error(ERR_NO));
}

static inline t_error	cmd_assignment_split(
							const t_string *expanded,
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
			t_cmd *cmd,
			t_token *token,
			t_string *expanded,
			bool *out_path_is_temporary)
{
	size_t		offset;
	t_string	name;
	t_string	value;
	t_error		err;

	*out_path_is_temporary = false;
	err = xtrace_print_one(expanded);
	if (err.type)
		return (string_free(expanded), err);
	if (cmd->entry.type == CMD_NONE
		|| cmd->entry.type == CMD_SPECIAL_BUILTIN
		|| cmd->entry.type == CMD_FUNCTION)
	{
		assert(token->assignment_offset >= 0);
		offset = (size_t)token->assignment_offset;
		err = cmd_assignment_split(expanded, offset, &name, &value);
		if (err.type)
			return (string_free(expanded), err);
		err = env_set_variable(&name, &value, false, false);
		string_free(expanded);
		return (string_free(&name), string_free(&value), err);
	}
	return (cmd_assignment_add_to_envp(expanded, cmd, out_path_is_temporary));
}
