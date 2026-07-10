#ifndef FUNCTIONS_PRIV_H
# define FUNCTIONS_PRIV_H

# include "functions.h"

t_error	function_deep_copy(
			const t_ast_command *command,
			const t_ast_redir_list *redirs,
			t_function *out);

#endif
