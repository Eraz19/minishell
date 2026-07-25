#include "cmd.h"
#include "cmd_assign_priv.h"
#include "expander.h"
#include "params.h"
#include "utils.h"

static inline t_error	cmd_assignment_build_envp(t_cmd *cmd)
{
	if (cmd->entry.type == CMD_NONE
		|| cmd->entry.type == CMD_SPECIAL_BUILTIN
		|| cmd->entry.type == CMD_FUNCTION)
	{
		(void)vector_init(&cmd->envp, sizeof(char *), 0);
		return (error(ERR_NO));
	}
	return (params_build_envp(&cmd->envp));
}

static inline t_error	cmd_assignment_finalize_envp(t_vector *envp)
{
	char	*null;
	t_error	err;

	null = NULL;
	if (!vector_push(envp, &null))
	{
		err = error_sys();
		vector_free(envp, free_char_ptr_void);
		return (err);
	}
	return (error(ERR_NO));
}

t_error	cmd_assign(
			t_cmd *cmd,
			const t_token_pool *assignments,
			bool *path_is_temporary,
			int *status)
{
	size_t		i;
	t_exp_flag	flags;
	t_token		*token;
	t_string	expanded;
	t_error		err;

	flags = expansion_flags_assignment();
	err = cmd_assignment_build_envp(cmd);
	i = 0;
	while (err.type == ERR_NO && i < assignments->len)
	{
		token = token_pool_get(assignments, i++);
		err = cmd_assignment_check(token);
		if (err.type == ERR_NO)
			err = cmd_assignment_expand(token, flags, &expanded, status);
		if (err.type == ERR_NO)
			err = cmd_assignment_process(cmd, token, &expanded, path_is_temporary);
	}
	if (err.type)
		return (vector_free(&cmd->envp, free_char_ptr_void), err);
	return (cmd_assignment_finalize_envp(&cmd->envp));
}
