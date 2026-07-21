#ifndef CMD_SUB
# define CMD_SUB

# include "error.h"
# include "libft.h"
# include "ast_vector_type.h"
# include <stddef.h>

// @warning ast_vector must have been initialized before calling this function
t_error	cmd_sub_find_end(
			const t_string *cmd,
			ssize_t *out_closing_token_id,
			t_ast_vector *ast_vector);
t_error	cmd_sub_run_string(
			const t_string *cmd_string,
			t_string *out_string,
			int *out_exit_status);
t_error	cmd_sub_run_ast(
			t_ast_vector *ast_vector,
			size_t index,
			t_string *out_string,
			int *out_exit_status);

#endif
