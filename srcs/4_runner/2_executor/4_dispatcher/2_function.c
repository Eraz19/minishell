#include "cmd_dispatcher_priv.h"
#include "redirector.h"
#include "walker.h"
#include "params.h"

static inline t_error	cmd_add_positional(t_positionals *positionals, t_vector *argv, size_t i)
{
	const char	*arg;
	t_string	param;

	arg = ((const char **)argv->data)[i];
	if (!string_init(&param, 0, arg, -1))
		return (error_sys());
	if (!vector_push(positionals, &param))
		return (error_sys());
	return (error(ERR_NO));
}

static inline t_error	cmd_update_positionals(t_cmd *cmd)
{
	size_t			argc;
	t_positionals	positionals;
	size_t			i;
	t_error			err;

	argc = cmd->argv.len - 2;
	if (!vector_init(&positionals, sizeof(t_string), argc))
		return (error_sys());
	i = 1;
	err = error(ERR_NO);
	while (i < cmd->argv.len - 1)
	{
		err = cmd_add_positional(&positionals, &cmd->argv, i);
		if (err.type)
			break ;
		i++;
	}
	if (err.type == ERR_NO)
		err = params_push_positionals(&positionals);
	if (err.type)
		vector_free(&positionals, string_free_void);
	return (err);
}

t_error	cmd_exec_function(t_cmd *cmd, t_runner *runner)
{
	t_error	err;

	err = cmd_update_positionals(cmd);
	if (err.type)
		return (err);
	err = redirect_start(&runner->redirector, &cmd->function->redirs,
			&cmd->exit_status);
	if (err.type)
	{
		if (err.type == ERR_REDIRECTION)
			err.type = ERR_REDIRECTION_OTHER;
		err = error_priorize(err, params_pop_positionals());
		return (err);
	}
	err = walk_command(runner, &cmd->function->body, &cmd->exit_status);
	if (err.type == ERR_RETURN)
		err.type = ERR_NO;
	err = error_priorize(err, redirect_stop(&runner->redirector));
	err = error_priorize(err, params_pop_positionals());
	return (err);
}
