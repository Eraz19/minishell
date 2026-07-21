#ifndef RUNNER_TYPE_H
# define RUNNER_TYPE_H

# include "cmd_cache.h"
# include <stddef.h>

// TODO: doc
typedef struct s_runner
{
	size_t			loop_depth;
	size_t			control_depth;
	t_cmd_cache		*cmd_cache;
}	t_runner;

#endif
