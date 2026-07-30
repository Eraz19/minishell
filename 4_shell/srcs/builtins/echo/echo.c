#include "builtins.h"
#include <unistd.h>
#include "echo_.h"
#include "error.h"
#include "posix_helpers.h"

static bool	echo_arg_is_flag(const char *arg)
{
	size_t	i;

	if (arg[0] != '-' || arg[1] == '\0')
		return (false);
	i = 1;
	while (arg[i] != '\0')
	{
		if (str_chr("neE", arg[i]) == NULL)
			return (false);
		i++;
	}
	return (true);
}

static int	echo_parse_flags(
				int argc,
				char **argv,
				bool *newline,
				bool *escapes)
{
	int		i;
	size_t	j;

	*newline = true;
	*escapes = false;
	i = 1;
	while (i < argc && echo_arg_is_flag(argv[i]))
	{
		j = 1;
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] == 'n')
				*newline = false;
			else
				*escapes = (argv[i][j] == 'e');
			j++;
		}
		i++;
	}
	return (i);
}

static t_error	echo_build(t_string *out, int argc, char **argv)
{
	int		i;
	bool	stop;
	bool	newline;
	bool	escapes;

	i = echo_parse_flags(argc, argv, &newline, &escapes);
	stop = false;
	string_init(out, 0, NULL, 0);
	while (i < argc && !stop)
	{
		if (!echo_append_arg(out, argv[i], escapes, &stop))
			return (error_sys());
		if (!stop && i + 1 < argc && !string_append_n(out, " ", 1))
			return (error_sys());
		i++;
	}
	if (newline && !stop && !string_append_n(out, "\n", 1))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	builtin_echo(int argc, char **argv, char **envp, int *exit_status)
{
	t_string	out;
	t_error		err;

	(void)envp;
	err = echo_build(&out, argc, argv);
	if (err.type == ERR_NO)
		err = posix_write(STDOUT_FILENO, out.data, out.len);
	string_free(&out);
	*exit_status = (int)err.type;
	if (err.type)
		err = error_print(err, argv[0], NULL, NULL);
	if (err.type == ERR_POSIX_WRITE)
		err.type = ERR_BUILTIN;
	return (err);
}
