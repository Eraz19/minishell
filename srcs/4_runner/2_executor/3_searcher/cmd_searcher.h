#ifndef CMD_SEARCHER_H
# define CMD_SEARCHER_H

# include "error.h"
# include "libft.h"

t_error	cmd_search(
			const t_string *cmd_name,
			const t_vector *envp,
			t_string *out_cmd_path);

#endif
