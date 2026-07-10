#include "ast_type.h"
#include "converter_priv.h"
#include <stdlib.h>
# include <assert.h>	// DEBUG

void	ast_simple_command_init(t_ast_simple_command *simple_command)
{
	assert(simple_command != NULL);
	vector_init(&simple_command->assignments, sizeof(t_token *), 0);
	vector_init(&simple_command->words, sizeof(t_token *), 0);
	ast_redir_list_init(&simple_command->redirs);
}

void	ast_simple_command_free(void *simple_command)
{
	t_ast_simple_command	*cmd;

	assert(simple_command != NULL);
	cmd = (t_ast_simple_command *)simple_command;
	vector_free(&cmd->assignments, NULL);
	vector_free(&cmd->words, NULL);
	ast_redir_list_free(&cmd->redirs);
}
