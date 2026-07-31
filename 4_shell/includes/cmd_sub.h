#ifndef CMD_SUB_H
# define CMD_SUB_H

# include "libft.h"
# include "ast_vector_type.h"
# include "error.h"

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

// @warning ast_vector must have been initialized before calling this function
t_error	cmd_sub_find_end(
			ssize_t *out_closing_token_id,
			t_ast_vector *ast_vector);

// @note: only child free's the cmd_string, parent leaves it unchanged.
t_error	cmd_sub_run_string(
			t_string *cmd_string,
			t_string *out_string,
			int *out_exit_status);

t_error	cmd_sub_run_ast(
			t_ast_vector *ast_vector,
			size_t index,
			t_string *out_string,
			int *out_exit_status);

#endif
