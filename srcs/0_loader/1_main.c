#include "loader.h"
#include <stdlib.h>
#include <unistd.h>

static t_shell	*shell_get(t_shell *addr)
{
	static t_shell	*shell = NULL;

	if (addr)
		shell = addr;
	return (shell);
}

static void	shell_init(t_shell *shell)
{
	shell->state.params.positional_params = NULL;
	vector_init(&shell->state.variables, sizeof(t_var), 0);
	// scanner_init(shell->scanner);
	// builder_init(shell->builder);
	// runner_init(shell->runner);
}

static void	shell_free(void)
{
	t_shell	*shell;
	size_t	i;

	shell = shell_get(NULL);
	if (!shell)
		return ;
	i = 0;
	while (i < shell->state.params.positional_count)
	{
		free(shell->state.params.positional_params[i]);
		i++;
	}
	if (shell->state.params.positional_params)
		free(shell->state.params.positional_params);
	// TODO: free var.name and var.value for each variable
	vector_free(&shell->state.variables);
	// scanner_free(&shell->scanner);
	// builder_free(&shell->builder);
	// runner_free(&shell->runner);
}

void	panic(const char *error_message, int exit_code)
{
	size_t	len;

	len = 0;
	while (error_message[len])
		len++;
	write(2, "Minishell: ", 11);
	write(2, error_message, len);
	write(2, "\n", 1);
	shell_free();
	exit(exit_code);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	shell = malloc(sizeof(*shell));
	if (!shell)
		panic("not enough memory", EXIT_FAILURE);
	shell_get(shell);
	// Parse envp
	// Init mandatory variables
	// Init [UP] variables
	// Init parameters
	// Process ENV
	// Process input
	return (EXIT_SUCCESS);
}
