#include "builtins.h"
#include <unistd.h>
#include "cd_.h"
#include "params.h"
#include "utils.h"
#include <signal.h>

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
	*args = (t_cd_args){.mode = 'L', .ensure_pwd = false, .print = false};
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

t_error	cd_from_var(const char *utility, const char *name, t_string *dir)
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

t_error	cd_resolv_operand(int argc, char **argv, t_cd_args *args, t_string *dir)
{
	if ((size_t)argc - args->operand_index > 1)
		return (error_print(error(ERR_INVALID_USAGE), argv[0],
			"too many arguments", NULL, NULL));
	if ((size_t)argc == args->operand_index)
		return (cd_from_var(argv[0], "HOME", dir));
	if (str_cmp(argv[args->operand_index], "-") == 0)
		return (args->print = true, cd_from_var(argv[0], "OLDPWD", dir));
	if (!string_init(dir, 0, argv[args->operand_index], -1))
		return (error_sys());
	return (error(ERR_NO));
}

static t_error	cd_requalify(t_error err, char *builtin_name)
{
	if (err.type)
		err = error_print(err, builtin_name, NULL, NULL);
	else if (
		err.type == ERR_VAR_INVALID_NAME
		|| err.type == ERR_VAR_NOT_FOUND
		|| err.type == ERR_INVALID_USAGE
		|| err.type == ERR_UB
		|| err.type == ERR_POSIX_ASSIGNMENT)
		err.type = ERR_BUILTIN;
	return (err);
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
		err = cd_resolv_operand(argc, argv, &args, &dir);
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
	return (cd_requalify(err, argv[0]));
}
