#ifndef CMD_SEARCH_PRIV_H
# define CMD_SEARCH_PRIV_H

# include "cmd.h"

t_error	cmd_convert_file_error(t_error err);

// @ret ERR_POSIX_CMD_NOT_FOUND / ERR_LIBC
t_error	cmd_search_try_absolute_path(
			const t_string *cmd_name,
			t_cmd_entry_point *out_entry_point);

// @ret ERR_POSIX_CMD_NOT_FOUND / ERR_POSIX_CMD_NOT_EXECUTABLE / ERR_LIBC
t_error	cmd_search_try_cache(
			const t_string *cmd_name,
			t_cmd_entry_point *out_entry_point);

// @ret ERR_POSIX_CMD_NOT_FOUND / ERR_POSIX_CMD_NOT_EXECUTABLE / ERR_LIBC
t_error	cmd_search_try_envp_path(
			const t_string *cmd_name,
			const t_vector *envp,
			bool path_is_temporary,
			t_cmd_entry_point *out_entry_point);

void	cmd_search_try_regular_builtin(t_cmd_entry_point *out_entry_point);

#endif
