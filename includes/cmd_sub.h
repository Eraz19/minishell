#ifndef CMD_SUB
# define CMD_SUB

# include "error.h"
# include "libft.h"
# include "ast.h"
# include <stddef.h>

t_error	cmd_sub_find_end(ssize_t *out_token_id);
t_error	cmd_sub_run_string(
			const t_string *cmd_string,
			t_string *out_string,
			int *out_exit_status);
t_error	cmd_sub_run_ast(
			t_ast_root *ast_root,
			t_string *out_string,
			int *out_exit_status);

#endif
