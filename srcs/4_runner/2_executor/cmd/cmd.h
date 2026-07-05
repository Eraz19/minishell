#ifndef CMD_H
# define CMD_H

# include "error.h"
# include "cmd_priv.h"
# include "tokens.h"

t_error	cmd_resolve(
			t_functions *functions,
			t_tokens *words,
			t_cmd_resolution *out_resolution);

#endif
