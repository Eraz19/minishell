#include "shell.h"

bool	option_is_active(t_option option)
{
	t_shell	*shell;

	shell = shell_get();
	return ((shell->params.options & option) != 0);
}

void	option_set(t_option *options, t_option option, bool on)
{
	if (on)
		*options |= option;
	else
		*options &= ~option;
}
