#ifndef CMD_EXECUTE_PRIV_H
# define CMD_EXECUTE_PRIV_H

#include "cmd.h"

t_error	exec_builtin(t_cmd *cmd, int *exit_status);
t_error	exec_external(t_cmd *cmd, int *exit_status);

#endif
