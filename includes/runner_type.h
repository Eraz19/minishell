#ifndef RUNNER_TYPE_H
# define RUNNER_TYPE_H

# include "cmd_cache.h"
# include "parser_type.h"
# include <stddef.h>

// TODO: doc
typedef struct s_runner
{
	t_parser		parser;
	t_cmd_cache		*cmd_cache;		// borrowed
	size_t			loop_depth;
	size_t			control_depth;
}	t_runner;

#endif
