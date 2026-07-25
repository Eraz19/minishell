#include "builtins.h"
#include "builtin_error.h"
#include "env_priv.h"
#include "cmd.h"
#include "utils.h"

#define POSIX_1		"POSIX: env: DESCRIPTION: If the first argument is '-',"
#define POSIX_2 	" the results are unspecified."
#define POSIX_IMPL	"'-' is the first operand"

static inline void	env_warn_unspecified_arg(int argc, char **argv)
{
	if (argc > 1 && str_cmp(argv[1], "-") == 0)
		print_unspecified_behaviour(argv[0], POSIX_1 POSIX_2, POSIX_IMPL);
}

static inline t_error	env_parse_args(
							int argc,
							char **argv,
							bool *i_is_active,
							int *first_operand_index)
{
	t_getopt_in		in;
	t_getopt_out	out;
	t_error			err;

	env_warn_unspecified_arg(argc, argv);
	in.builtin_name = argv[0];
	in.options_with_arg = NULL;
	in.options_with_arg_count = 0;
	in.single_delimiter = false;
	in.ub_on_repeated_flags = false;
	in.valid_minus_flags = "i";
	in.valid_plus_flags = NULL;
	err = ft_getopt(argc, argv, &in, &out);
	if (err.type)
		return (err);
	*i_is_active = out.options.len > 0
					&& ((t_getopt_option *)out.options.data)[0].flag == 'i';
	*first_operand_index = (int)out.first_operand_index;
	vector_free(&out.options, NULL);
	return (err);
}

static inline t_error	env_exec(int argc, char **argv, t_vector *env, int *status)
{
	t_cmd		cmd;
	t_error		err;

	cmd_init(&cmd);
	cmd.name.data = argv[0];
	cmd.argc = argc;
	cmd.argv.data = argv;
	vector_take(&cmd.envp, env);
	err = cmd_execute(&cmd, true, status);
	return (cmd_finalize_and_free(&cmd, err, status));
}

t_error	builtin_env(int argc, char **argv, char **envp, int *status)
{
	bool		i_is_active;
	int			first_operand_index;
	int			utility_i;
	t_vector	env;
	t_error		err;

	err = env_parse_args(argc, argv, &i_is_active, &first_operand_index);
	if (err.type == ERR_NO)
		err = env_init_envp(envp, i_is_active, &env);
	if (err.type)
		return (builtin_print_and_qualify(argv[0], err, false, status));
	utility_i = (int)first_operand_index;
	while (utility_i < argc && str_chr(argv[utility_i], '=') != NULL)
		utility_i++;
	err = env_update_envp(
			argv + first_operand_index,
			utility_i - first_operand_index,
			&env);
	if (err.type == ERR_NO && utility_i >= argc)
		err = env_print(&env, status);
	else if (err.type == ERR_NO)
		err = env_exec(argc - utility_i, argv + utility_i, &env, status);
	vector_free(&env, free_char_ptr_void);
	return (builtin_print_and_qualify(argv[0], err, false, status));
}
