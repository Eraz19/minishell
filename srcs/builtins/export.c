#include "params.h"
#include "ft_getopt.h"
#include "utils.h"
#include <stdlib.h>

#define EXPORT_USAGE	"-p || name[=word] ..."

// @ret ERR_UNDEFINED_BEHAVIOUR
static t_error export_catch_ub(int argc, char **argv, t_getopt_out *out)
{
	size_t	options_count;
	size_t	operand_count;

	options_count = out->options.len;
	operand_count = (size_t)argc - out->first_operand_index;
	if (options_count == 0 && operand_count == 0)
		return (undefined_behaviour("POSIX: export: DESCRIPTION: When no "
			"arguments are given, the results are unspecified."));
	if (options_count > 0 && operand_count > 0)
	{
		(void)error_print(argv[0], EXPORT_USAGE, ERR_BUILTIN_INVALID_USAGE);
		return (undefined_behaviour("POSIX: 12.1:8: The use of conflicting "
		"mutually-exclusive arguments produces undefined results."));
	}
	return (ERR_NO);
}

// @ret ERR_OPT_INVALID / ERR_OPT_MISSING_ARG / ERR_OPT_INVALID_ARG /
// 		ERR_UNDEFINED_BEHAVIOUR / ERR_LIBC
static t_error	export_process_options(int argc, char **argv, t_getopt_out *out)
{
	t_getopt_in	in;
	t_error		error;

	in.builtin_name = argv[0];
	in.single_delimiter = false;
	in.ub_on_repeated_flags = true;
	in.valid_minus_flags = "p";
	in.valid_plus_flags = NULL;
	in.options_with_arg = NULL;
	in.options_with_arg_count = 0;
	error = ft_getopt(argc, argv, &in, out);
	if (error != ERR_NO)
		return (error);
	error = export_catch_ub(argc, argv, out);
	if (error != ERR_NO)
	{
		vector_free(&out->options, NULL);
		return (error);
	}
	return (ERR_NO);
}

// @ret ERR_ASSIGNMENT_MISSING_NAME / ERR_SHELL_NOT_FOUND /
// 		ERR_VAR_INVALID_NAME / ERR_VAR_READ_ONLY / ERR_LIBC
static t_error	export_add_one(const char *builtin_name, const char *string)
{
	char	*name;
	char	*value;
	t_error	error;

	error = assignment_split(string, &name, &value);
	if (error != ERR_NO)
		return (error_print(builtin_name, string, error));
	error = params_set_variable(name, value, true, false);
	if (error != ERR_NO)
		(void)error_print(builtin_name, string, error);
	free(name);
	if (value)
		free(value);
	return (error);
}

// @ret ERR_ASSIGNMENT_MISSING_NAME / ERR_SHELL_NOT_FOUND /
// 		ERR_VAR_INVALID_NAME / ERR_VAR_READ_ONLY / ERR_LIBC
static t_error	export_add(size_t first_operand_index, int argc, char **argv)
{
	int		i;
	t_error	last_exit_code;
	t_error	exit_code;

	exit_code = ERR_NO;
	i = (int)first_operand_index;
	while (i < argc)
	{
		last_exit_code = export_add_one(argv[0], argv[i++]);
		if (last_exit_code != ERR_NO)
			exit_code = last_exit_code;
	}
	return (exit_code);
}

int	export(int argc, char **argv, char **envp)
{
	t_getopt_out	out;
	t_error			exit_code;

	(void)envp;
	exit_code = export_process_options(argc, argv, &out);
	if (exit_code == ERR_LIBC)
		return ((int)error_print(argv[0], "options parsing failed", exit_code));
	if (exit_code != ERR_NO)
		return ((int)exit_code);
	if (out.options.len > 0)
	{
		exit_code = params_print(PARAMS_PRINT_EXPORT);
		if (exit_code != ERR_NO)
			(void)error_print(argv[0], "variables write failed", exit_code);
	}
	else
		exit_code = export_add(out.first_operand_index, argc, argv);
	vector_free(&out.options, NULL);
	return ((int)exit_code);
}
