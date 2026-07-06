#ifndef CMD_ASSIGNATOR_H
# define CMD_ASSIGNATOR_H

# include "error.h"
# include "cmd_resolver_priv.h"
# include "tokens.h"

t_error	cmd_assign(t_cmd_type cmd_type, t_tokens *assignments, char ***envp);

#endif
