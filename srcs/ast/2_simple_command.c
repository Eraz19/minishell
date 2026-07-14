#include "ast.h"
# include <assert.h>	// DEBUG

void	ast_simple_command_init(t_ast_scmd *simple_command)
{
	assert(simple_command != NULL);
	token_pool_init(&simple_command->assignments);
	token_pool_init(&simple_command->words);
	ast_redir_list_init(&simple_command->redirs);
}

void	ast_simple_command_free(void *simple_command)
{
	t_ast_scmd	*cmd;

	assert(simple_command != NULL);
	cmd = (t_ast_scmd *)simple_command;
	token_pool_free(&cmd->assignments);
	token_pool_free(&cmd->words);
	ast_redir_list_free(&cmd->redirs);
}
