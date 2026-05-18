#include "shell.h"
#include <stdlib.h>
# include <stdio.h>

static void	params_dump_scalar(const char *name)
{
	char		*value;
	t_error		error;

	error = params_get(name, &value);
	if (error != ERR_NO)
	{
		printf("PARAMS '%s'=[ERROR: '%s']\n", name, error_to_string(error));
		return ;
	}
	if (value)
	{
		printf("PARAMS '%s'='%s'\n", name, value);
		free(value);
	}
	else
		printf("PARAMS '%s'=NULL\n", name);
}

static void	params_dump_variables(void)
{
	t_shell 	*shell;
	t_var_list	*var_list;
	t_var		*var;
	size_t		i;

	shell = shell_get();
	if (!shell)
		error_print(NULL, "params_dump_variables()", ERR_SHELL_NOT_FOUND);
	var_list = &shell->params.variables;
	i = 0;
	while (i < var_list->len)
	{
		var = &((t_var *)var_list->data)[i];
		params_dump_scalar(var->name);
		i++;
	}
}

static void	params_dump_options(void)
{
	params_dump_scalar("-");
}

static void	params_dump_specials(void)
{
	params_dump_scalar("0");
	params_dump_scalar("$");
	params_dump_scalar("!");
	params_dump_scalar("?");
}

static void	params_dump_positionals(void)
{
	t_shell	*shell;
	t_error	error;
	char	*count_s;
	size_t	count;
	size_t	i;
	char	*name;

	shell = shell_get();
	if (!shell)
	{
		error_print(NULL, "params_dump_positionals()", ERR_SHELL_NOT_FOUND);
		return ;
	}
	error = positionals_get_one(&shell->params.positionals, "#", &count_s);
	if (error != ERR_NO)
	{
		error_print(NULL, "params_dump_positionals()", error);
		return ;
	}
	count = ft_atozu(count_s);
	free(count_s);
	i = 1;
	while (i < count)
	{
		name = ft_zutoa(i);
		if (!name)
		{
			error_print(NULL, "params_dump_positionals()", ERR_LIBC);
			break ;
		}
		params_dump_scalar(name);
		free(name);
		i++;
	}
	params_dump_scalar("#");
}

void	params_dump_all(void)
{
	printf("\nDUMP PARAMS\n");
	params_dump_variables();
	params_dump_options();
	params_dump_specials();
	params_dump_positionals();
}
