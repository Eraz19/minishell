#include "params.h"
#include "ft_getopt.h"
#include <stdbool.h>

#define UNSET_USAGE	"[-f|-v] name..."

static bool	unset_has_option(t_getopt_out *out, char flag)
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

// @ret ERR_INVALID_USAGE / ERR_UB / ERR_LIBC
static t_error	unset_process_options(int argc, char **argv, t_getopt_out *out)
{
	t_getopt_in	in;
	t_error		err;

	in.builtin_name = argv[0];
	in.single_delimiter = false;
	in.ub_on_repeated_flags = true;
	in.valid_minus_flags = "fv";
	in.valid_plus_flags = NULL;
	in.options_with_arg = NULL;
	in.options_with_arg_count = 0;
	err = ft_getopt(argc, argv, &in, out);
	if (err.type)
		return (err);
	if (out->options.len > 1)
	{
		(void)error_print(error(ERR_INVALID_USAGE), argv[0], UNSET_USAGE,
				NULL, NULL);
		err = undefined_behaviour("POSIX: 12.1:8: The use of conflicting "
			"mutually-exclusive arguments produces undefined results.");
	}
	else if (out->first_operand_index >= (size_t)argc)
		return (error_print(error(ERR_INVALID_USAGE), argv[0], UNSET_USAGE,
					NULL, NULL));
	return (err);
}

// @ret ERR_VAR_INVALID_NAME / ERR_VAR_READ_ONLY / ERR_SHELL_NOT_FOUND /
// 		ERR_INDEX_OUT_OF_BOUND
static t_error	unset_var(size_t first_operand_index, int argc, char **argv)
{
	int			i;
	t_string	tmp;
	t_error		last_exit_status;
	t_error		exit_status;

	exit_status = error(ERR_NO);
	i = (int)first_operand_index;
	while (i < argc)
	{
		tmp.data = argv[i];
		tmp.len = (str_len(tmp.data));
		tmp.cap = 0;
		last_exit_status = params_unset_variable(&tmp);
		if (last_exit_status.type != ERR_NO)
		{
			exit_status = error_print(
				last_exit_status, argv[0], argv[i], NULL, NULL);
		}
		i++;
	}
	return (exit_status);
}

// TODO
static t_error	unset_fun(size_t first_operand_index, int argc, char **argv)
{
	// TODO
	(void)first_operand_index;
	(void)argc;
	(void)argv;
	return (error(ERR_NO));
}

t_error	builtin_unset(int argc, char **argv, char **envp, int *exit_status)
{
	t_getopt_out	out;
	t_error			err;

	(void)envp;
	err = unset_process_options(argc, argv, &out);
	if (err.type == ERR_NO && unset_has_option(&out, 'f'))
		err = unset_fun(out.first_operand_index, argc, argv);
	else if (err.type == ERR_NO)
		err = unset_var(out.first_operand_index, argc, argv);
	*exit_status = (int)err.type;
	if (err.type)
		err = error_print(err, argv[0], NULL, NULL);
	if (err.type == ERR_INVALID_USAGE
		|| err.type == ERR_VAR_INVALID_NAME
		|| err.type == ERR_VAR_READ_ONLY
		|| err.type == ERR_POSIX_WRITE || err.type == ERR_UB)
		err.type = ERR_BUILTIN;
	else if (err.type == ERR_SHELL_NOT_FOUND
		|| err.type == ERR_INDEX_OUT_OF_BOUND)
		err.type = ERR_INTERNAL;
	vector_free(&out.options, NULL);
	return (err);
}
