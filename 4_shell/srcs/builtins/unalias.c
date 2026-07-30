#include "builtins.h"
#include "env.h"
#include "utils.h"

#define UNALIAS_USAGE	"-a || alias-name..."

static bool	unalias_has_option(t_getopt_out *out, char flag)
{
	t_getopt_option	*option;
	size_t			i;

	i = 0;
	while (i < out->options.len)
	{
		option = &((t_getopt_option *)out->options.data)[i];
		if (option->flag == flag)
			return (true);
		i++;
	}
	return (false);
}

t_error	unalias_process_options(int argc, char **argv, t_getopt_out *out)
{
	t_getopt_in	in;
	t_error		err;
	bool		all;

	in.builtin_name = argv[0];
	in.single_delimiter = false;
	in.ub_on_repeated_flags = true;
	in.valid_minus_flags = "a";
	in.valid_plus_flags = NULL;
	in.options_with_arg = NULL;
	in.options_with_arg_count = 0;
	err = ft_getopt(argc, argv, &in, out);
	if (err.type)
		return (err);
	all = unalias_has_option(out, 'a');
	if (all && out->first_operand_index < (size_t)argc)
		return (error_print(error(ERR_INVALID_USAGE), argv[0], UNALIAS_USAGE,
				NULL, NULL));
	if (!all && out->first_operand_index >= (size_t)argc)
		return (error_print(error(ERR_INVALID_USAGE), argv[0], UNALIAS_USAGE,
				NULL, NULL));
	return (err);
}

static t_error	unalias_remove_operands(
					size_t first_operand_index, int argc, char **argv)
{
	int		i;
	t_error	last_exit_status;
	t_error	exit_status;

	exit_status = error(ERR_NO);
	i = (int)first_operand_index;
	while (i < argc)
	{
		last_exit_status = env_unset_alias(argv[i]);
		if (last_exit_status.type != ERR_NO)
		{
			exit_status = error_print(
					last_exit_status, argv[0], argv[i], NULL, NULL);
		}
		i++;
	}
	return (exit_status);
}

t_error	builtin_unalias(int argc, char **argv, char **envp, int *exit_status)
{
	t_getopt_out	out;
	t_error			err;

	(void)envp;
	err = unalias_process_options(argc, argv, &out);
	if (err.type == ERR_NO && unalias_has_option(&out, 'a'))
		env_unset_all_alias();
	else if (err.type == ERR_NO)
		err = unalias_remove_operands(out.first_operand_index, argc, argv);
	*exit_status = (err.type != ERR_NO);
	if (err.type)
		err = error_print(err, argv[0], NULL, NULL);
	if (err.type == ERR_ALIAS_NOT_FOUND
		|| err.type == ERR_INVALID_USAGE
		|| err.type == ERR_POSIX_WRITE || err.type == ERR_UB)
		err.type = ERR_BUILTIN;
	else if (err.type == ERR_SHELL_NOT_FOUND)
		err.type = ERR_INTERNAL;
	vector_free(&out.options, NULL);
	return (err);
}
