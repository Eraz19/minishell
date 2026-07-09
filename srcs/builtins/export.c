#include "params.h"
#include "ft_getopt.h"
#include "utils.h"
#include <stdlib.h>

#define EXPORT_USAGE	"-p || name[=word] ..."

// @ret ERR_UB
static t_error export_catch_ub(int argc, char **argv, t_getopt_out *out)
{
	size_t	options_count;
	size_t	operand_count;
	t_error	err;

	err = error(ERR_NO);
	options_count = out->options.len;
	operand_count = (size_t)argc - out->first_operand_index;
	if (options_count == 0 && operand_count == 0)
		print_unspecified_behaviour("POSIX: export: DESCRIPTION: When no "
			"arguments are given, the results are unspecified", "no-op");
	if (options_count > 0 && operand_count > 0)
	{
		(void)error_print(error(ERR_INVALID_USAGE), argv[0], EXPORT_USAGE, NULL, NULL);
		err = undefined_behaviour("POSIX: 12.1:8: The use of conflicting "
		"mutually-exclusive arguments produces undefined results.");
	}
	return (err);
}

// @p exit_status ERR_INVALID_USAGE / ERR_UB / ERR_LIBC
// @ret ERR_BUILTIN / ERR_UB / ERR_LIBC
static t_error	export_process_options(
					int argc, char **argv,
					t_getopt_out *out,
					int *exit_status)
{
	t_getopt_in	in;
	t_error		err;

	in.builtin_name = argv[0];
	in.single_delimiter = false;
	in.ub_on_repeated_flags = true;
	in.valid_minus_flags = "p";
	in.valid_plus_flags = NULL;
	in.options_with_arg = NULL;
	in.options_with_arg_count = 0;
	err = ft_getopt(argc, argv, &in, out);
	if (err.type)
	{
		*exit_status = (int)err.type;
		if (err.type == ERR_INVALID_USAGE)
			err.type = ERR_BUILTIN;
		return (err);
	}
	err = export_catch_ub(argc, argv, out);
	if (err.type)
	{
		vector_free(&out->options, NULL);
		return (*exit_status = (int)err.type, err);
	}
	return (err);
}

// @ret ERR_ASSIGNMENT_MISSING_NAME / ERR_VAR_INVALID_NAME / ERR_VAR_READ_ONLY
// 		/ ERR_INTERNAL / ERR_LIBC
static t_error	export_add_one(const char *builtin_name, const char *string)
{
	t_string	name;
	t_string	value;
	t_error		err;

	err = assignment_split(string, &name, &value);
	if (err.type == ERR_ASSIGNMENT_MISSING_NAME)
		err = error_print(err, builtin_name, string, NULL, NULL);
	if (err.type)
		return (err);
	err = params_set_variable(&name, &value, true, false);
	if (err.type == ERR_VAR_INVALID_NAME || err.type == ERR_VAR_READ_ONLY)
		err = error_print(err, builtin_name, string, NULL, NULL);
	else if (err.type == ERR_SHELL_NOT_FOUND)
		err.type = ERR_INTERNAL;
	string_free(&name);
	string_free(&value);
	return (err);
}

// @p exit_status ERR_ASSIGNMENT_MISSING_NAME / ERR_VAR_INVALID_NAME
// 					/ ERR_VAR_READ_ONLY / ERR_INTERNAL / ERR_LIBC
// @ret ERR_BUILTIN / ERR_INTERNAL / ERR_LIBC
static t_error	export_add(
					size_t first_operand_index,
					int argc,
					char **argv,
					int *exit_status)
{
	int		i;
	t_error	last_err;
	t_error	err;

	err = error(ERR_NO);
	i = (int)first_operand_index;
	while (i < argc)
	{
		last_err = export_add_one(argv[0], argv[i++]);
		if (last_err.type != ERR_NO)
			err = last_err;
	}
	*exit_status = (int)err.type;
	if (err.type == ERR_ASSIGNMENT_MISSING_NAME
		|| err.type == ERR_VAR_INVALID_NAME
		|| err.type == ERR_VAR_READ_ONLY)
		err.type = ERR_BUILTIN;
	return (err);
}

t_error	builtin_export(int argc, char **argv, char **envp, int *exit_status)
{
	t_getopt_out	out;
	t_error			err;

	(void)envp;
	err = export_process_options(argc, argv, &out, exit_status);
	if (err.type)
		return (err);
	if (out.options.len > 0)
	{
		err = params_print(PARAMS_PRINT_EXPORT);
		if (err.type != ERR_NO)
			err = error_print(err, argv[0], "variables write failed", NULL, NULL);
		if (err.type == ERR_LIBC)
			err.type = ERR_BUILTIN;
		else if (err.type == ERR_SHELL_NOT_FOUND)
			err.type = ERR_INTERNAL;
		*exit_status = (int)err.type;
	}
	else
		err = export_add(out.first_operand_index, argc, argv, exit_status);
	vector_free(&out.options, NULL);
	return (err);
}
