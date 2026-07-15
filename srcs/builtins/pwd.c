#include <sys/stat.h>
#include <unistd.h>
#include "error.h"
#include "libft.h"
#include "params.h"
#include "ft_getopt.h"
#include "posix_helpers.h"

static t_error	pwd_process_options(int argc, char **argv, char *mode)
{
	t_getopt_in		in;
	t_getopt_out	out;
	t_error			err;
	size_t			i;

	in.builtin_name = argv[0];
	in.single_delimiter = false;
	in.ub_on_repeated_flags = false;
	in.valid_minus_flags = "LP";
	in.valid_plus_flags = NULL;
	in.options_with_arg = NULL;
	in.options_with_arg_count = 0;
	err = ft_getopt(argc, argv, &in, &out);
	if (err.type == ERR_NO && out.first_operand_index < (size_t)argc)
		print_unspecified_behaviour(NULL, "POSIX: pwd: OPERANDS: None",
			"operands ignored");
	*mode = 'L';
	i = 0;
	while (err.type == ERR_NO && i < out.options.len)
		*mode = ((t_getopt_option *)out.options.data)[i++].flag;
	return (vector_free(&out.options, NULL), err);
}

static bool	pwd_has_dot_component(const char *path)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (path[i] != '\0')
	{
		while (path[i] == '/')
			i++;
		len = 0;
		while (path[i + len] != '\0' && path[i + len] != '/')
			len++;
		if (len == 1 && path[i] == '.')
			return (true);
		if (len == 2 && path[i] == '.' && path[i + 1] == '.')
			return (true);
		i += len;
	}
	return (false);
}

static bool	pwd_names_cwd(const char *path)
{
	struct stat	pwd_info;
	struct stat	cwd_info;

	if (stat(path, &pwd_info) != 0 || stat(".", &cwd_info) != 0)
		return (false);
	return (pwd_info.st_dev == cwd_info.st_dev
		&& pwd_info.st_ino == cwd_info.st_ino);
}

static t_error	pwd_resolve(char mode, t_string *path)
{
	t_error	err;

	if (mode == 'L')
	{
		err = params_get_from_const("PWD", path);
		if (err.type == ERR_NO && path->len > 0 && path->data[0] == '/'
			&& !pwd_has_dot_component(path->data)
			&& pwd_names_cwd(path->data))
			return (err);
		if (err.type == ERR_NO)
			string_free(path);
	}
	return (posix_getcwd(path));
}

t_error	builtin_pwd(int argc, char **argv, char **envp, int *exit_status)
{
	t_error		err;
	t_string	path;
	char		mode;

	(void)envp;
	err = pwd_process_options(argc, argv, &mode);
	if (err.type == ERR_NO)
	{
		err = pwd_resolve(mode, &path);
		if (err.type == ERR_NO)
		{
			if (!string_append_n(&path, "\n", 1))
				err = error_sys();
			if (err.type == ERR_NO)
				err = posix_write(STDOUT_FILENO, path.data, path.len);
			string_free(&path);
		}
	}
	*exit_status = (int)err.type;
	if (err.type)
		err = error_print(err, argv[0], NULL, NULL);
	if (err.type == ERR_INVALID_USAGE || err.type == ERR_POSIX_WRITE
		|| err.type == ERR_UB)
		err.type = ERR_BUILTIN;
	else if (err.type == ERR_SHELL_NOT_FOUND)
		err.type = ERR_INTERNAL;
	return (err);
}
