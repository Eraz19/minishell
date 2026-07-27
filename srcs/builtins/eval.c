#include "builtins.h"
#include "scanner.h"
#include "env.h"
#include "runner.h"
#include "shell.h"

// @ret ERR_NO / ERR_LIBC
static inline t_error	eval_merge_fields(
							int argc,
							char **argv,
							t_string *out,
							bool *only_null_args)
{
	int		i;
	char	*arg;
	t_error	err;

	*only_null_args = true;
	if (!string_init(out, 0, "", 0))
		return (error_sys());
	if (str_cmp(argv[1], "--") == 0)
		i = 2;
	else
		i = 1;
	while (i < argc)
	{
		arg = argv[i++];
		if (arg[0] != '\0')
			*only_null_args = false;
		if (!string_append_n(out, arg, -1))
			return (err = error_sys(), string_free(out), err);
		if (i < argc && !string_append_n(out, " ", 1))
			return (err = error_sys(), string_free(out), err);
	}
	return (error(ERR_NO));
}

t_error	builtin_eval(int argc, char **argv, t_runner *runner, int *exit_status)
{
	t_runner	*eval_runner;
	t_string	cmd;
	bool		only_null_args;
	t_error		err;

	(void)runner;
	if (argc == 1)
		return (*exit_status = 0, error(ERR_NO));
	err = eval_merge_fields(argc, argv, &cmd, &only_null_args);
	if (err.type)
		return (err);
	else if (only_null_args == true)
		return (string_free(&cmd), *exit_status = 0, error(ERR_NO));
	err = shell_get_new_runner(&eval_runner, SCAN_MODE_STRING, cmd.data);
	if (err.type)
		return (string_free(&cmd), error_print(err, argv[0], NULL, NULL));
	err = runner_run(eval_runner);
	shell_destroy_last_instance();
	string_free(&cmd);
	if (err.type)
		return (error_print(err, argv[0], NULL, NULL));
	err = env_get_last_status(exit_status);
	if (err.type)
		return (error_print(err, argv[0], NULL, NULL));
	return (err);
}
