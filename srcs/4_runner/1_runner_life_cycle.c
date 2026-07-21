#include "runner.h"
#include "params.h"
#include "parser.h"

t_error	runner_init(t_runner *runner, t_scan_mode mode)
{
	t_cmd_cache	*cmd_cache;
	t_error		err;

	err = params_get_cmd_cache(&cmd_cache);
	if (err.type)
		return (err);
	err = parser_init(&runner->parser, mode);
	runner->cmd_cache = cmd_cache;
	runner->loop_depth = 0;
	runner->control_depth = 0;
	return (err);
}

void	runner_clear(t_runner *runner)
{
	parser_clear(&runner->parser);
	runner->loop_depth = 0;
	runner->control_depth = 0;
}

void	runner_free(t_runner *runner)
{
	parser_free(&runner->parser);
	runner->loop_depth = 0;
	runner->control_depth = 0;
}
