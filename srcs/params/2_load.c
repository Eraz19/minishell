#include "params.h"
#include <stdlib.h>

// TODO: check what POSIX means by "If both '-' and '--' are given as **ARGUMENTS**"
static void	params_catch_undefined_1(int argc, char **argv)
{
	int		i;
	bool	single_found;
	bool	double_found;

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

static void	params_catch_undefined_2(int argc, char **argv, int start)
{
	if (argv[start - 1][0] != '-' || argv[start - 1][1] != '-' || argv[start - 1][2] != '\0')
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

t_error	params_load(t_params *params, int argc, char **argv, char **envp)
{
	t_error	error;
	size_t	start_index;
	
	params_catch_undefined_1(argc, argv);
	params->name = argv[0];
	start_index = 1;
	error = options_load(&params->options, argc, argv, &start_index);
	if (error != ERR_NO)
		return (error);
	params_catch_undefined_2(argc, argv, (int)start_index);
	error = specials_load(&params->specials, argc, argv, &start_index);
	if (error != ERR_NO)
		return (error);
	error = positionals_load(&params->positionals, argc, argv, start_index);
	if (error != ERR_NO)
		return (error);
	error = var_load(&params->variables, envp);
	if (error != ERR_NO)
		return (error);
	/* ---------- TODO: tmp debug: START ---------- */
	var_dump();
	options_dump();
	specials_dump();
	positionals_dump();
	params_dump();
	/* ---------- TODO: tmp debug: END ---------- */
	return (ERR_NO);
}
