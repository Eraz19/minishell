#include "cmd_assignator_priv.h"
#include "cmd_assignator.h"
#include "params.h"
#include "utils.h"

static inline t_error	cmd_assignment_build_envp(
							t_cmd_type cmd_type,
							t_vector *out_envp)
{
	if (cmd_type == CMD_NONE
		|| cmd_type == CMD_SPECIAL_BUILTIN
		|| cmd_type == CMD_FUNCTION)
	{
		(void)vector_init(out_envp, sizeof(char *), 0);
		return (error(ERR_NO));
	}
	return (params_build_envp(out_envp));
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
			t_cmd_type cmd_type,
			const t_tokens *assignments,
			t_vector *out_envp)
{
	size_t		i;
	t_exp_flag	flags;
	t_token		*token;
	t_string	expanded;
	t_error		err;

	flags = cmd_assignment_expansion_flags();
	err = cmd_assignment_build_envp(cmd_type, out_envp);
	i = 0;
	while (err.type == ERR_NO && i < assignments->len)
	{
		err = tokens_get(assignments, i++, &token);
		if (err.type == ERR_NO)
			err = cmd_assignment_check(token);
		if (err.type == ERR_NO)
			err = cmd_assignment_expand(token, flags, &expanded);
		if (err.type == ERR_NO)
			err = cmd_assignment_process(cmd_type, token, &expanded, out_envp);
	}
	if (err.type)
		return (vector_free(out_envp, free_char_ptr_void), err);
	return (cmd_assignment_finalize_envp(out_envp));
}
