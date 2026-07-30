#include <stdlib.h>
#include "error.h"
#include "history_load_env_priv.h"

void	on_history_disabled_error(void)
{
	(void)error_print(
		error(ERR_HISTORY_DISABLED),
		"history",
		"no valid history file path found", NULL, NULL);
}
