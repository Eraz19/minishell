#include "runner.h"
#include "env.h"
#include "parser.h"

void	runner_init(t_runner *runner)
{
	parser_init(&runner->parser);
	runner->cmd_cache = NULL;
	runner->loop_depth = 0;
	runner->control_depth = 0;
	runner->errexit_ignored = false;
	runner->child = NULL;
	runner->parent = NULL;
}

t_error	runner_load(
			t_runner *runner,
			t_runner *parent_runner,
			t_scan_mode mode,
			const char *input)
{
	t_scanner	*parent_scanner;
	t_error		err;

	runner->loop_depth = 0;
	runner->control_depth = 0;
	if (parent_runner != NULL)
	{
		parent_runner->child = runner;
		runner->parent = parent_runner;
	}
	err = env_get_cmd_cache(&runner->cmd_cache);
	if (err.type)
		return (err);
	if (parent_runner == NULL)
		parent_scanner = NULL;
	else
		parent_scanner = &parent_runner->parser.scanner;
	err = parser_load(&runner->parser, parent_scanner, mode, input);
	if (err.type)
		runner_free(runner);
	return (err);
}

void	runner_clear(t_runner *runner)
{
	parser_clear(&runner->parser);
	runner->loop_depth = 0;
	runner->control_depth = 0;
	runner->errexit_ignored = false;
}

void	runner_free(t_runner *runner)
{
	if (runner->child != NULL)
		runner_free(runner->child);
	runner->child = NULL;
	parser_free(&runner->parser);
	runner->loop_depth = 0;
	runner->control_depth = 0;
	runner->errexit_ignored = false;
}

void	runner_free_void(void *runner)
{
	runner_free(runner);
}
