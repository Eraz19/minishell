#include "cmd.h"
#include "utils.h"
#include "params.h"

void	cmd_init(t_cmd *cmd)
{
	(void)string_init(&cmd->name, 0, NULL, 0);
	cmd->type = CMD_NONE;
	cmd->is_declaration_utility = false;
	(void)vector_init(&cmd->argv, sizeof(char *), 0);
	(void)vector_init(&cmd->envp, sizeof(char *), 0);
	(void)string_init(&cmd->path, 0, NULL, 0);
	cmd->builtin = NULL;
	cmd->function = NULL;
	cmd->path_is_temporary = false;
	cmd->exit_status = -1;
}

void	cmd_free(t_cmd *cmd)
{
	if (cmd->type == CMD_FUNCTION)
		params_stop_function(&cmd->function);
	string_free(&cmd->name);
	cmd->type = CMD_NONE;
	cmd->is_declaration_utility = false;
	vector_free(&cmd->argv, free_char_ptr_void);
	vector_free(&cmd->envp, free_char_ptr_void);
	string_free(&cmd->path);
	cmd->builtin = NULL;
	cmd->path_is_temporary = false;
	cmd->exit_status = -1;
}
