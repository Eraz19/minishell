#include "walker.h"
#include "redirector.h"
#include "params.h"
# include "logs.h"

static inline t_error	walk_function_add_positional(
							t_positionals *positionals,
							t_vector *argv,
							size_t i)
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

static inline t_error	walk_function_update_positionals(t_cmd *cmd)
{
	t_positionals	positionals;
	size_t			i;
	t_error			err;

	if (!vector_init(&positionals, sizeof(t_string), (size_t)cmd->argc))
		return (error_sys());
	i = 1;
	err = error(ERR_NO);
	while (i < cmd->argv.len - 1)
	{
		err = walk_function_add_positional(&positionals, &cmd->argv, i);
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

t_error	walk_function(t_cmd *cmd, t_runner *runner, int *status)
{
	t_function	*function;
	t_error		err;

	function = cmd->entry.data.function;
	err = walk_function_update_positionals(cmd);
	if (err.type)
		return (err);
	err = redirect_start(&function->redirs, status);
	if (err.type)
		return (error_priorize(err, params_pop_positionals()));
	fprintf(stderr, YELLOW "############## FUNCTION %s (START) ##############\n" NC, cmd->name.data);
	err = walk_command(runner, &function->body, status);
	fprintf(stderr, YELLOW "############## FUNCTION %s (STOP) ###############\n" NC, cmd->name.data);
	if (err.type == ERR_RETURN)
		err.type = ERR_NO;
	err = error_priorize(err, redirect_stop());
	err = error_priorize(err, params_pop_positionals());
	params_stop_function(&function);
	return (err);
}
