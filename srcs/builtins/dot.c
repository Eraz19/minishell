#include "builtins.h"
#include "builtin_error.h"
#include "shell.h"
#include "runner.h"
#include "utils.h"
#include "utils.h"

static inline t_error	dot_parse_args(
							int argc,
							char **argv,
							size_t *first_operand_index)
{
	t_getopt_in		in;
	t_getopt_out	out;
	t_error			err;

	in.builtin_name = argv[0];
	in.options_with_arg = NULL;
	in.options_with_arg_count = 0;
	in.single_delimiter = false;
	in.ub_on_repeated_flags = false;
	in.valid_minus_flags = NULL;
	in.valid_plus_flags = NULL;
	err = ft_getopt(argc, argv, &in, &out);
	*first_operand_index = out.first_operand_index;
	vector_free(&out.options, NULL);
	return (err);
}

static inline t_error	dot_search_readable_file(
							t_string *filename,
							t_string *out_file_path)
{
	t_string	path;
	bool		found;
	t_error		err;

	if (str_chr(filename->data, '/') != NULL)
	{
		string_take_string(out_file_path, filename);
		err = file_check(out_file_path, READABLE, &found);
		if (err.type)
			string_free(out_file_path);
		return (err);
	}
	err = params_get_from_const("PATH", &path);
	if (err.type == ERR_VAR_NOT_FOUND)
		err.type = ERR_POSIX_CMD_NOT_FOUND;
	if (err.type)
		return (err);
	return (file_search(&path, filename, READABLE, out_file_path));
}

static inline t_error	dot_execute(t_string *file_path, int *status)
{
	t_runner	*runner;
	t_error		err;

	err = shell_get_new_runner(&runner, SCAN_MODE_FILE, file_path->data);
	if (err.type)
		return (string_free(file_path), err);
	err = runner_run(runner);
	shell_destroy_last_instance();
	string_free(file_path);
	if (err.type)
		return (err);
	return (params_get_last_status(status));
}

t_error	builtin_dot(int argc, char **argv, t_runner *runner, int *status)
{
	size_t		first_operand_index;
	t_string	filename;
	t_string	file_path;
	t_error		err;

	(void)runner;
	err = dot_parse_args(argc, argv, &first_operand_index);
	if (err.type)
		return (builtin_print_and_qualify(argv[0], err, true, status));
	if ((size_t)argc - first_operand_index != 1)
	{
		err = error(ERR_INVALID_USAGE);
		return (builtin_print_and_qualify(argv[0], err, true, status));
	}
	if (!string_init(&filename, 0, argv[first_operand_index], -1))
		return (builtin_print_and_qualify(argv[0], error_sys(), true, status));
	err = dot_search_readable_file(&filename, &file_path);
	string_free(&filename);
	if (err.type)
		return (builtin_print_and_qualify(argv[0], err, true, status));
	err = dot_execute(&file_path, status);
	return (builtin_print_and_qualify(argv[0], err, true, status));
}
