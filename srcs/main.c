#include "shell.h"

#define DEFAULT_NAME	"minishell"

static t_shell	*shell_singleton(t_shell *addr)
{
	static t_shell *shell = NULL;

	if (addr)
		shell = addr;
	return (shell);
}

void	shell_set(t_shell *addr)
{
	(void)shell_singleton(addr);
}

t_shell	*shell_get(void)
{
	return (shell_singleton(NULL));
}

const char	*shell_get_name(void)
{
	t_shell	*shell;

	shell = shell_get();
	if (!shell)
		return (DEFAULT_NAME);
	if (shell->params.script_name)
		return (shell->params.script_name);
	return (shell->params.shell_name);
}

int	main(int argc, char **argv, char **envp)
{
	return ((int)shell_start(argc, argv, envp, NULL));
}
