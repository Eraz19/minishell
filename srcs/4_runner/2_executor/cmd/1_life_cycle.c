#include "cmd_priv.h"
#include "expander.h"
#include <stdlib.h>

void	cmd_resolution_init(t_cmd_resolution *cmd_resolution)
{
	cmd_resolution->type = CMD_NONE;
	(void)vector_init(&cmd_resolution->expansions, sizeof(t_expansion), 0);
	cmd_resolution->path = NULL;
	cmd_resolution->builtin = NULL;
	cmd_resolution->function = NULL;
	cmd_resolution->is_declaration_utility = false;
}

void	cmd_resolution_free(t_cmd_resolution *cmd_resolution)
{
	cmd_resolution->type = CMD_NONE;
	vector_free(&cmd_resolution->expansions, expansion_free_void);
	if (cmd_resolution->path)
		free(cmd_resolution->path);
	cmd_resolution->path = NULL;
	cmd_resolution->builtin = NULL;
	cmd_resolution->function = NULL;
	cmd_resolution->is_declaration_utility = false;
}
