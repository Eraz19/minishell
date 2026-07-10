#include "functions_priv.h"
// #include "ast.h"

t_error	function_deep_copy(
			const t_ast_command *command,
			const t_ast_redir_list *redirs,
			t_function *out)
{
	// TODO
	(void)command;
	(void)redirs;
	(void)out;
	// ast_command_deep_copy(&out->body, command);
	// ast_redir_list_deep_copy(&out->redirs, redirs);
	return (error(ERR_NOT_IMPLEMENTED));
}
