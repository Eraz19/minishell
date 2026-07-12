#include "error.h"
#include "walker_priv.h"

static inline bool	walk_loop_control_is_local(t_runner *runner)
{
	if (runner->control_depth <= 1 || runner->loop_depth <= 1)
	{
		runner->control_depth = 0;
		return (true);
	}
	runner->control_depth--;
	return (false);
}

static inline bool	walk_loop_must_continue(t_runner *runner, t_error *err)
{
	bool	res;

	if (err->type != ERR_CONTINUE)
		return (false);
	res = walk_loop_control_is_local(runner);
	if (res == true)
		err->type = ERR_NO;
	return (res);
}

static inline bool	walk_loop_must_break(t_runner *runner, t_error *err)
{
	if (err->type != ERR_BREAK)
		return (false);
	if (walk_loop_control_is_local(runner) == true)
		err->type = ERR_NO;
	return (true);
}

static inline bool	walk_loop_must_execute(
						t_runner *runner,
						t_ast_loop *loop,
						t_error *err)
{
	int	status;

	if (err->type)
		return (false);
	while (true)
	{
		*err = walk_list(runner, &loop->condition, &status);
		if (walk_loop_must_continue(runner, err) == false)
			break ;
	}
	if (walk_loop_must_break(runner, err) == true)
		return (false);
	else if (err->type)
		return (false);
	if (loop->condition_must_be_true == true)
		return (status == 0);
	return (status != 0);
}

t_error	walk_loop(t_runner *runner, t_ast_loop *loop, int *exit_status)
{
	t_error	err;

	runner->loop_depth++;
	*exit_status = 0;
	err = error(ERR_NO);
	while (walk_loop_must_execute(runner, loop, &err) == true)
	{
		err = walk_list(runner, &loop->body, exit_status);
		if (walk_loop_must_continue(runner, &err) == true)
			continue ;
		if (walk_loop_must_break(runner, &err) == true)
			break ;
	}
	runner->loop_depth--;
	return (walk_normalize_output(err, NULL, exit_status));
}
