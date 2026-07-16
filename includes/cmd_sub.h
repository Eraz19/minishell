#ifndef CMD_SUB
# define CMD_SUB

# include "error.h"
# include "libft.h"
# include <stddef.h>

t_error	cmd_sub_find_end(size_t *out_token_id, bool *found);
t_error	cmd_sub_run(
			const t_string *cmd_string,
			t_string *out_string,
			int *out_exit_status);

#endif
