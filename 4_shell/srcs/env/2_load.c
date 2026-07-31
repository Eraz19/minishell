#include "env.h"
#include <stdlib.h>
# include <assert.h>	// DEBUG

// TODO: check what POSIX means by "If both '-' and '--' are given as **ARGUMENTS**"
static void	env_catch_undefined_1(int argc, char **argv)
{
	int		i;
	bool	single_found;
	bool	double_found;

	assert(argv != NULL);
	single_found = false;
	double_found = false;
	i = 0;
	while (i < argc)
	{
		if (argv[i][0] == '-' && argv[i][1] == '-' && argv[i][2] == '\0')
			double_found = true;
		else if (argv[i][0] == '-' && argv[i][1] == '\0')
			single_found = true;
		if (single_found && double_found)
			undefined_behaviour("POSIX: sh: OPERANDS: "
				"If both '-' and '--' are given as arguments, "
				"the results are undefined");
		i++;
	}
}

static void	env_catch_undefined_2(int argc, char **argv, int start)
{
	assert(argv != NULL);
	if (argv[start - 1][0] != '-'
		|| argv[start - 1][1] != '-'
		|| argv[start - 1][2] != '\0')
		start++;
	while (start < argc)
	{
		if (argv[start][0] == '-' && argv[start][1] == '\0')
			undefined_behaviour("POSIX: sh: OPERANDS: "
				"If other operands precede the single "
				"<hyphen-minus>, the results are undefined");
		start++;
	}
}

t_error	env_load(t_params *params, int argc, char **argv, char **envp)
{
	t_error	err;
	size_t	start_index;
	
	assert(argv != NULL);
	assert(envp != NULL);
	env_catch_undefined_1(argc, argv);
	params->name = argv[0];
	start_index = 1;
	err = options_load(&params->options, argc, argv, &start_index);
	if (err.type != ERR_NO)
		return (err);
	env_catch_undefined_2(argc, argv, (int)start_index);
	err = specials_load(&params->specials, argc, argv, &start_index);
	if (err.type != ERR_NO)
		return (err);
	err = positionals_load_stack(&params->positionals_stack, argc, argv, start_index);
	if (err.type != ERR_NO)
		return (err);
	err = var_load(&params->variables, envp);
	if (err.type != ERR_NO)
		return (err);
#ifdef DDEBUG_ENV
	/* ---------- DEBUG: START ---------- */
	dump_variables();
	options_dump();
	specials_dump();
	positionals_dump();
	dump_env();
	/* ---------- DEBUG: END ---------- */
#endif
	return (error(ERR_NO));
}
