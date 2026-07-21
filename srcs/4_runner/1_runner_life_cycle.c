#include "runner.h"
#include "params.h"
#include "parser.h"

t_error	runner_init(
			t_runner *runner,
			t_runner *parent_runner,
			t_scanner *parent_scanner,
			t_scan_mode mode)
{
	t_error	err;

	err = params_get_cmd_cache(&runner->cmd_cache);
	if (err.type)
		return (err);
	runner->loop_depth = 0;
	runner->control_depth = 0;
	parent_runner->child = runner;
	return (parser_init(&runner->parser, parent_scanner, mode));
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

void	runner_free_void(void *runner)
{
	runner_free(runner);
}
