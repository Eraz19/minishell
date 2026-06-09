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

// @ret ERR_OPT_INVALID / ERR_OPT_MISSING_ARG / ERR_OPT_INVALID_ARG /
// 		ERR_UNDEFINED_BEHAVIOUR / ERR_LIBC
static t_error	unset_process_options(int argc, char **argv, t_getopt_out *out)
{
	t_getopt_in	in;
	t_error		error;

	in.builtin_name = argv[0];
	in.single_delimiter = false;
	in.ub_on_repeated_flags = true;
	in.valid_minus_flags = "fv";
	in.valid_plus_flags = NULL;
	in.options_with_arg = NULL;
	in.options_with_arg_count = 0;
	error = ft_getopt(argc, argv, &in, out);
	if (error != ERR_NO)
		return (error);
	if (out->options.len > 1)
	{
		(void)error_print(argv[0], UNSET_USAGE, ERR_BUILTIN_INVALID_USAGE);
		vector_free(&out->options, NULL);
		return (undefined_behaviour("POSIX: 12.1:8: The use of conflicting "
			"mutually-exclusive arguments produces undefined results."));
	}
	return (ERR_NO);
}

// @ret ERR_VAR_INVALID_NAME / ERR_VAR_READ_ONLY / ERR_SHELL_NOT_FOUND /
// 		ERR_INDEX_OUT_OF_BOUND
static t_error	unset_var(size_t first_operand_index, int argc, char **argv)
{
	int		i;
	t_error	last_exit_code;
	t_error	exit_code;

	exit_code = ERR_NO;
	i = (int)first_operand_index;
	while (i < argc)
	{
		last_exit_code = params_unset_variable(argv[i]);
		if (last_exit_code != ERR_NO)
		{
			(void)error_print(argv[0], argv[i], last_exit_code);
			exit_code = last_exit_code;
		}
		i++;
	}
	return (exit_code);
}

static t_error	unset_fun(size_t first_operand_index, int argc, char **argv)
{
	// TODO
	(void)first_operand_index;
	(void)argc;
	(void)argv;
	return (ERR_NO);
}

int	unset(int argc, char **argv, char **envp)
{
	t_getopt_out	out;
	t_error			exit_code;

	(void)envp;
	exit_code = unset_process_options(argc, argv, &out);
	if (exit_code == ERR_LIBC)
		return ((int)error_print(argv[0], "options parsing failed", exit_code));
	if (exit_code != ERR_NO)
		return ((int)exit_code);
	if (unset_has_option(&out, 'f'))
		exit_code = unset_fun(out.first_operand_index, argc, argv);
	else
		exit_code = unset_var(out.first_operand_index, argc, argv);
	vector_free(&out.options, NULL);
	return ((int)exit_code);
}
