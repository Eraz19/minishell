#include "error.h"
#include "walker_priv.h"

static inline t_error	walk_loop_condition(
							t_runner *runner,
							t_ast_list *condition,
							int *exit_status)
{
	bool	old_errexit_ignored;
	t_error	err;

	old_errexit_ignored = runner->errexit_ignored;
	runner->errexit_ignored = true;
	err = walk_list(runner, condition, exit_status);
	runner->errexit_ignored = old_errexit_ignored;
	return (err);
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
		*err = walk_loop_condition(runner, &loop->condition, &status);
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
	return (err);
}
