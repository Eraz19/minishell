#include <unistd.h>
#include "env_.h"
#include "ft_getopt.h"
#include "posix_helpers.h"

// POSIX.1-2024 env. Without a utility operand the resulting
// environment is written to standard output, one name=value pair per
// line. -i ignores the inherited environment completely. name=value
// operands modify the result. Utility invocation (first operand
// without '=') is not implemented yet: diagnosed and reported as
// ERR_UB, the project's stub convention.

t_error	env_print_entry(const char *entry)
{
	t_error	err;

	err = posix_write(STDOUT_FILENO, entry, str_len(entry));
	if (err.type)
		return (err);
	return (posix_write(STDOUT_FILENO, "\n", 1));
}

bool	env_same_name(const char *a, const char *b)
{
	size_t	i;

	i = 0;
	while (a[i] != '\0' && a[i] != '=' && a[i] == b[i])
		i++;
	return ((a[i] == '\0' || a[i] == '=')
		&& (b[i] == '\0' || b[i] == '='));
}

static t_error	env_process_options(int argc, char **argv, t_getopt_out *out)
{
	t_getopt_in	in;

	in.builtin_name = argv[0];
	in.single_delimiter = false;
	in.ub_on_repeated_flags = false;
	in.valid_minus_flags = "i";
	in.valid_plus_flags = NULL;
	in.options_with_arg = NULL;
	in.options_with_arg_count = 0;
	return (ft_getopt(argc, argv, &in, out));
}

static size_t	env_find_utility(int argc, char **argv, size_t first)
{
	size_t	i;

	i = first;
	while (i < (size_t)argc && str_chr(argv[i], '=') != NULL)
		i++;
	return (i);
}

t_error	builtin_env(int argc, char **argv, char **envp, int *exit_status)
{
	t_getopt_out	out;
	t_env_args		args;
	size_t			utility;
	t_error			err;

	err = env_process_options(argc, argv, &out);
	if (err.type == ERR_NO)
	{
		utility = env_find_utility(argc, argv, out.first_operand_index);
		args.assigns = argv + out.first_operand_index;
		args.assign_count = utility - out.first_operand_index;
		if (utility < (size_t)argc)
			err = error_print(error(ERR_NOT_IMPLEMENTED), argv[0],
					argv[utility], NULL, NULL);
		else if (out.options.len > 0)
			err = env_print(NULL, &args);
		else
			err = env_print(envp, &args);
	}
	vector_free(&out.options, NULL);
	*exit_status = (int)err.type;
	if (err.type)
		err = error_print(err, argv[0], NULL, NULL);
	if (err.type == ERR_INVALID_USAGE || err.type == ERR_POSIX_WRITE)
		err.type = ERR_BUILTIN;
	else if (err.type == ERR_NOT_IMPLEMENTED)
		err.type = ERR_UB;
	return (err);
}
