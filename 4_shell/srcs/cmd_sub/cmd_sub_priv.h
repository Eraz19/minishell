#ifndef CMD_SUB_PRIV_H
# define CMD_SUB_PRIV_H

# include "libft.h"
# include "ast.h"
# include "error.h"

void	cmd_sub_child_string(const t_string *cmd_string, int pipe_fds[2]);
void	cmd_sub_child_ast(t_ast_root *ast_root, int pipe_fds[2]);
t_error	cmd_sub_parent(
			int pipe_fds[2],
			pid_t child_pid,
			t_string *out_string,
			int *out_exit_status);

#endif
