#include "shell.h"

#define NO_SHELL	"shell not found"

t_alias	*shell_get_alias(void)
{
	t_shell *shell;

	shell = shell_get();
	if (!shell)
		return (NULL);
	return (&shell->alias);
}

t_history	*shell_get_history(void)
{
	t_shell *shell;

	shell = shell_get();
	if (!shell)
		return (NULL);
	return (&shell->history);
}

t_params	*shell_get_params(void)
{
	t_shell *shell;

	shell = shell_get();
	if (!shell)
		return (NULL);
	return (&shell->params);
}

t_error	shell_get_lr_machine(const t_lr_machine **out_lr_machine_ptr)
{
	t_shell	*shell;

	*out_lr_machine_ptr = NULL;
	shell = shell_get();
	if (shell == NULL)
		return (error_print(error(ERR_INTERNAL), NO_SHELL, NULL, NULL));
	*out_lr_machine_ptr = &shell->machine;
	return (error(ERR_NO));
}
