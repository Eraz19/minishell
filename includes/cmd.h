#ifndef CMD_H
# define CMD_H

# include "libft.h"
# include "builtins.h"
# include "error.h"
# include "functions.h"

/* ************************************************************************* */
/*                                   TYPES                                   */
/* ************************************************************************* */

typedef enum e_cmd_type
{
	CMD_NONE,
	CMD_EXTERNAL,
	CMD_BUILTIN,
	CMD_SPECIAL_BUILTIN,
	CMD_FUNCTION
}	t_cmd_type;

typedef union u_cmd_entry_point_data
{
	t_string			cmd_path;
	t_builtin			builtin;
	t_special_builtin	special_builtin;
	t_function			*function;	// borrowed
}	t_cmd_entry_point_data;

typedef struct s_cmd_entry_point
{
	t_cmd_type				type;
	t_cmd_entry_point_data	data;
}	t_cmd_entry_point;

typedef struct s_cmd
{
	t_string			name;
	t_cmd_entry_point	entry;
	int					argc;
	t_vector			argv;
	t_vector			envp;
}	t_cmd;

/* ************************************************************************* */
/*                                LIFE CYCLE                                 */
/* ************************************************************************* */

void	cmd_init(t_cmd *cmd);
void	cmd_free(t_cmd *cmd);

/* ************************************************************************* */
/*                                  CMD OPS                                  */
/* ************************************************************************* */

/*
1. Expand first word.
2. Resolve cmd_type.
3. Expand remaining words (considering declaration utilities).
4. Build argv.
*/
t_error	cmd_resolve(t_cmd *cmd, const t_token_pool *words, int *exit_status);

/*
1. Expand assignments.
2. If needed, assign them to current shell env.
3. Build envp.
*/
t_error	cmd_assign(
			t_cmd *cmd,
			const t_token_pool *assignments,
			bool *path_is_temporary,
			int *status);

/*
1. Search for command in cmd_cache if path_is_temporary == false.
2. Search for command in cmd->envp PATH if binary was not found at step 1.
3. Execve the found binary.
4. Fallback on new shell instance if execve fails.
5. Standardize exit status and err with cmd_finalize().
Do NOT search for special builtins, intrinsic builtins, and functions.
*/
t_error	cmd_execute(t_cmd *cmd, bool path_is_temporary, int *exit_status);

t_error	cmd_finalize(t_cmd *cmd, t_error err, int *exit_status);
t_error	cmd_finalize_and_free(t_cmd *cmd, t_error err, int *exit_status);

#endif
