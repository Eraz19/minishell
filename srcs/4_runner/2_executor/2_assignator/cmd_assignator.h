#ifndef CMD_ASSIGNATOR_H
# define CMD_ASSIGNATOR_H

# include "error.h"
# include "cmd_resolution_type.h"
# include "tokens.h"

t_error	cmd_assign(
			t_cmd_type cmd_type,
			const t_tokens *assignments,
			t_vector *envp);

#endif
