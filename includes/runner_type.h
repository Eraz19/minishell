#ifndef RUNNER_TYPE_H
# define RUNNER_TYPE_H

# include "redirector_type.h"
# include "functions.h"
# include "cmd_cache.h"

// TODO: doc

typedef struct s_runner
{
	t_redirector	redirector;
	t_functions		functions;
	t_cmd_cache		cmd_cache;
	size_t			loop_depth;
	size_t			control_depth;
}	t_runner;

#endif
