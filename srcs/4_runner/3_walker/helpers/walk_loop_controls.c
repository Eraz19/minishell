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

bool	walk_loop_must_continue(t_runner *runner, t_error *err)
{
	bool	res;

	if (err->type != ERR_CONTINUE)
		return (false);
	res = walk_loop_control_is_local(runner);
	if (res == true)
		err->type = ERR_NO;
	return (res);
}

bool	walk_loop_must_break(t_runner *runner, t_error *err)
{
	if (err->type != ERR_BREAK)
		return (false);
	if (walk_loop_control_is_local(runner) == true)
		err->type = ERR_NO;
	return (true);
}
