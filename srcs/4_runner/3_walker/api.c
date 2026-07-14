#include "error.h"
#include "walker.h"
#include "walker_priv.h"

t_error	walk(t_runner *runner, t_ast_root *ast_root, int *exit_status)
{
	return (walk_list(runner, ast_root, exit_status));
}
