#include "builtins.h"
#include "scanner.h"
#include "params.h"
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

t_error	builtin_eval(int argc, char **argv, char **envp, int *exit_status)
{
	t_runner	*runner;
	t_string	cmd;
	bool		only_null_args;
	t_error		err;

	(void)envp;
	if (argc == 1)
		return (*exit_status = 0, error(ERR_NO));
	err = eval_merge_fields(argc, argv, &cmd, &only_null_args);
	if (err.type)
		return (err);
	else if (only_null_args == true)
		return (string_free(&cmd), *exit_status = 0, error(ERR_NO));
	err = shell_get_new_runner(&runner, SCAN_MODE_STRING);
	if (err.type)
		return (string_free(&cmd), error_print(err, argv[0], NULL, NULL));
	scanner_set_input(&runner->parser.scanner, &cmd);
	runner_run(runner);
	shell_destroy_last_instance();
	string_free(&cmd);
	err = params_get_last_status(exit_status);
	if (err.type)
		return (error_print(err, argv[0], NULL, NULL));
	return (err);
}
