#include "cmd_resolver_priv.h"
#include "cmd_expansion.h"
#include <stdlib.h>

void	cmd_resolution_init(t_cmd_resolution *cmd_resolution)
{
	cmd_resolution->type = CMD_NONE;
	cmd_expansions_init(&cmd_resolution->expansions);
	cmd_resolution->path = NULL;
	cmd_resolution->builtin = NULL;
	cmd_resolution->function = NULL;
	cmd_resolution->is_declaration_utility = false;
}

void	cmd_resolution_free(t_cmd_resolution *cmd_resolution)
{
	cmd_resolution->type = CMD_NONE;
	cmd_expansions_free(&cmd_resolution->expansions);
	if (cmd_resolution->path)
		free(cmd_resolution->path);
	cmd_resolution->path = NULL;
	cmd_resolution->builtin = NULL;
	cmd_resolution->function = NULL;
	cmd_resolution->is_declaration_utility = false;
}
