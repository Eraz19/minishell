#include <unistd.h>
#include "cd_.h"
#include "params.h"
#include "ft_getopt.h"
#include "posix_helpers.h"

static t_error	cd_process_options(int argc, char **argv, t_cd_args *args)
{
	size_t			i;
	t_getopt_in		in;
	t_getopt_out	out;
	t_error			err;

	in.builtin_name = argv[0];
	in.single_delimiter = false;
	in.ub_on_repeated_flags = false;
	in.valid_minus_flags = "LPe";
	in.valid_plus_flags = NULL;
	in.options_with_arg = NULL;
	in.options_with_arg_count = 0;
	err = ft_getopt(argc, argv, &in, &out);
	args->mode = 'L';
	args->ensure_pwd = false;
	args->print = false;
	i = 0;
	while (err.type == ERR_NO && i < out.options.len)
	{
		if (((t_getopt_option *)out.options.data)[i].flag == 'e')
			args->ensure_pwd = true;
		else
			args->mode = ((t_getopt_option *)out.options.data)[i].flag;
		i++;
	}
	args->operand_index = out.first_operand_index;
	return (vector_free(&out.options, NULL), err);
}

static t_error	cd_from_var(const char *utility, const char *name,
					t_string *dir)
{
	t_error	err;

	err = params_get_from_const(name, dir);
	if (err.type == ERR_NO && dir->len == 0)
	{
		string_free(dir);
		err = error(ERR_VAR_NOT_FOUND);
	}
	if (err.type == ERR_VAR_NOT_FOUND)
		return (error_print(err, utility, name, NULL, NULL));
	return (err);
}

static t_error	cd_resolve_operand(int argc, char **argv, t_cd_args *args,
					t_string *dir)
{
	if ((size_t)argc - args->operand_index > 1)
		return (error_print(error(ERR_INVALID_USAGE), argv[0],
				"too many arguments", NULL, NULL));
	if ((size_t)argc == args->operand_index)
		return (cd_from_var(argv[0], "HOME", dir));
	if (str_cmp(argv[args->operand_index], "-") == 0)
	{
		args->print = true;
		return (cd_from_var(argv[0], "OLDPWD", dir));
	}
	if (!string_init(dir, 0, argv[args->operand_index], -1))
		return (error_sys());
	return (error(ERR_NO));
}

static t_error	cd_print_new(void)
{
	t_string	pwd;
	t_error		err;

	err = params_get_from_const("PWD", &pwd);
	if (err.type)
		return (err);
	if (!string_append_n(&pwd, "\n", 1))
		return (string_free(&pwd), error_sys());
	err = posix_write(STDOUT_FILENO, pwd.data, pwd.len);
	return (string_free(&pwd), err);
}

t_error	builtin_cd(int argc, char **argv, char **envp, int *exit_status)
{
	t_error		err;
	t_string	dir;
	t_cd_args	args;

	(void)envp;
	string_init(&args.curpath, 0, NULL, 0);
	err = cd_process_options(argc, argv, &args);
	if (err.type == ERR_NO)
		err = cd_resolve_operand(argc, argv, &args, &dir);
	if (err.type == ERR_NO)
	{
		err = cd_build_curpath(&args, &dir);
		string_free(&dir);
		if (err.type == ERR_NO && args.mode == 'L')
			err = cd_canonicalize(&args, argv[0]);
		if (err.type == ERR_NO)
			err = cd_apply(&args, argv[0]);
		if (err.type == ERR_NO && args.print)
			err = cd_print_new();
	}
	string_free(&args.curpath);
	*exit_status = (int)err.type;
	if (err.type)
		err = error_print(err, argv[0], NULL, NULL);
	if (err.type == ERR_SHELL_NOT_FOUND)
		err.type = ERR_INTERNAL;
	else if (err.type != ERR_NO && err.type != ERR_INTERRUPTED)
		err.type = ERR_BUILTIN;
	return (err);
}
