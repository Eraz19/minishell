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
		return (err = error_sys(), cmd->exit_status = (int)err.type, err);
	i = 1;
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
	{
		cmd->exit_status = (int)err.type;
		vector_free(&positionals, string_free_void);
	}
	return (err);
}

static inline t_error	cmd_process_body(t_cmd *cmd, t_runner *runner)
{
	t_error	err;

	err = walk_command(runner, &cmd->function->body);
	if (err.type == ERR_NOT_IMPLEMENTED)
	{
		cmd->exit_status = (int)err.type;
		err.type = ERR_NO;
		return (err);
	}
	// TODO: handle controls (e.g. ERR_RETURN)
	if (err.type == ERR_NO)
		err = params_get_last_status(&cmd->exit_status);
	if (err.type == ERR_NO)
		return (err);
	cmd->exit_status = (int)err.type;
	return (err);
}
static inline t_error	cmd_cleanup(t_cmd *cmd, t_runner *runner, t_error err)
{
	t_error	cleanup_err;

	cleanup_err = redirect_stop(&runner->redirector);
	if (cleanup_err.type)
		(void)params_pop_positionals();
	else
		cleanup_err = params_pop_positionals();
	if (cleanup_err.type && cmd->exit_status == (int)ERR_NO)
		return (cmd->exit_status = (int)cleanup_err.type, cleanup_err);
	return (err);
}

t_error	cmd_exec_function(t_cmd *cmd, t_runner *runner)
{
	t_error	err;

	err = cmd_update_positionals(cmd);
	if (err.type)
		return (cmd->exit_status = (int)err.type, err);
	err = redirect_start(&runner->redirector, &cmd->function->redirs);
	if (err.type)
	{
		cmd->exit_status = (int)ERR_REDIRECTION_OTHER;
		(void)params_pop_positionals();
		return (err);
	}
	err = cmd_process_body(cmd, runner);
	return (cmd_cleanup(cmd, runner, err));
}
