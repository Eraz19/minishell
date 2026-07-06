#include "shell.h"
#include "variables_priv.h"
#include <stdlib.h>
# include <stdio.h>
# include <assert.h>	// DEBUG

static void	params_dump_scalar(const t_string *name)
{
	t_string	value;
	t_error		err;

	assert(name != NULL);
	assert(name->len > 0);
	err = params_get(name, &value);
	if (err.type != ERR_NO)
	{
		fprintf(stderr, "PARAMS '%s'=[ERROR: '%s']\n", name->data, error_to_string(err));
		return ;
	}
	if (value.data)
	{
		fprintf(stderr, "PARAMS '%s'='%s'\n", name->data, value.data);
		string_free(&value);
	}
	else
		fprintf(stderr, "PARAMS '%s'=NULL\n", name->data);
}

static void	params_dump_scalar_cst(const char *name_cst)
{
	t_string	value;
	t_error		err;

	assert(name_cst != NULL);
	assert(name_cst[0] != '\0');
	err = params_get_from_const(name_cst, &value);
	if (err.type != ERR_NO)
	{
		fprintf(stderr, "PARAMS '%s'=[ERROR: '%s']\n", name_cst, error_to_string(err));
		return ;
	}
	if (value.data)
	{
		fprintf(stderr, "PARAMS '%s'='%s'\n", name_cst, value.data);
		string_free(&value);
	}
	else
		fprintf(stderr, "PARAMS '%s'=NULL\n", name_cst);
}

static void	params_dump_variables(void)
{
	t_shell 	*shell;
	t_var_list	*var_list;
	t_var		*var;
	size_t		i;

	shell = shell_get();
	if (!shell)
		error_print(error(ERR_SHELL_NOT_FOUND), "params_dump_variables()", NULL, NULL);
	var_list = &shell->params.variables;
	i = 0;
	while (i < var_list->len)
	{
		var = &((t_var *)var_list->data)[i];
		params_dump_scalar(&var->name);
		i++;
	}
}

static void	params_dump_options(void)
{
	params_dump_scalar_cst("-");
}

static void	params_dump_specials(void)
{
	params_dump_scalar_cst("0");
	params_dump_scalar_cst("$");
	params_dump_scalar_cst("!");
	params_dump_scalar_cst("?");
}

static void	params_dump_positionals(void)
{
	t_shell		*shell;
	t_error		err;
	t_string	name_string;
	t_string	count_s;
	size_t		count;
	size_t		i;
	char		*name;

	shell = shell_get();
	if (!shell)
	{
		error_print(error(ERR_SHELL_NOT_FOUND), "params_dump_positionals()", NULL, NULL);
		return ;
	}
	string_init(&name_string, 0, "#", -1);
	err = positionals_get_one(&shell->params.positionals_stack, &name_string, &count_s);
	string_free(&name_string);
	if (err.type != ERR_NO)
	{
		error_print(err, "params_dump_positionals()", NULL, NULL);
		return ;
	}
	count = ft_atozu(count_s.data);
	string_free(&count_s);
	i = 1;
	while (i <= count)
	{
		name = ft_zutoa(i);
		if (!name)
		{
			error_print(error_sys(), "params_dump_positionals()", NULL, NULL);
			break ;
		}
		params_dump_scalar_cst(name);
		free(name);
		i++;
	}
	params_dump_scalar_cst("#");
}

void	params_dump(void)
{
	fprintf(stderr, "\nDUMP PARAMS\n");
	params_dump_variables();
	params_dump_options();
	params_dump_specials();
	params_dump_positionals();
}
