#ifndef CMD_RESOLVER_H
# define CMD_RESOLVER_H

# include "error.h"
# include "cmd_resolution_type.h"
# include "tokens.h"

t_error	cmd_resolve(
			t_functions *functions,
			t_tokens *words,
			t_cmd_resolution *out_resolution);

#endif
