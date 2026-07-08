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
	t_error		err;

	in.builtin_name = argv[0];
	in.single_delimiter = false;
	in.ub_on_repeated_flags = true;
	in.valid_minus_flags = "fv";
	in.valid_plus_flags = NULL;
	in.options_with_arg = NULL;
	in.options_with_arg_count = 0;
	err = ft_getopt(argc, argv, &in, out);
	if (err.type != ERR_NO)
		return (err);
	if (out->options.len > 1)
	{
		(void)error_print(error(ERR_BUILTIN_INVALID_USAGE), argv[0], UNSET_USAGE, NULL, NULL);
		vector_free(&out->options, NULL);
		err = undefined_behaviour("POSIX: 12.1:8: The use of conflicting "
			"mutually-exclusive arguments produces undefined results.");
	}
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

static t_error	unset_fun(size_t first_operand_index, int argc, char **argv)
{
	// TODO
	(void)first_operand_index;
	(void)argc;
	(void)argv;
	return (error(ERR_NO));
}

int	builtin_unset(int argc, char **argv, char **envp)
{
	t_getopt_out	out;
	t_error			exit_status;

	(void)envp;
	exit_status = unset_process_options(argc, argv, &out);
	if (exit_status.type == ERR_LIBC)
		return ((int)error_print(exit_status, argv[0], "options parsing failed", NULL, NULL).type);
	if (exit_status.type != ERR_NO)
		return ((int)exit_status.type);
	if (unset_has_option(&out, 'f'))
		exit_status = unset_fun(out.first_operand_index, argc, argv);
	else
		exit_status = unset_var(out.first_operand_index, argc, argv);
	vector_free(&out.options, NULL);
	return ((int)exit_status.type);
}
