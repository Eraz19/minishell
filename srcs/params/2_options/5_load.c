#include "options_priv.h"
#include <unistd.h>
# include <stdio.h>	// TODO: tmp debug

static inline bool	options_is_delimiter(const char *arg)
{
	if (arg[0] == '-' && arg[1] == '\0')
		return (true);
	if (arg[0] == '-' && arg[1] == '-' && arg[2] == '\0')
		return (true);
	return (false);
}

static inline bool	options_load_one(
	size_t *i,
	char **argv,
	t_option *options,
	bool *explicit_plus_m)
{
	if (argv[*i][1] == 'o' && argv[*i][2] == '\0')
	{
		(*i)++;
		if (!options_process_name(
			options,
			argv[*i],
			argv[*i - 1][0] == '-',
			explicit_plus_m))
			return (false);
	}
	else if (!options_process_flags(options, argv[*i], explicit_plus_m))
		return (false);
	(*i)++;
	return (true);
}

static void	options_finalize(
	t_option *options,
	size_t remaining_args,
	bool explicit_plus_m)
{
	if (!option_is_active_in(*options, OPT_CMD_STRING) && remaining_args == 0)
		option_set(options, OPT_STDIN_INPUT, true);
	if (option_is_active_in(*options, OPT_STDIN_INPUT)
		&& isatty(STDIN_FILENO) && isatty(STDERR_FILENO))
		option_set(options, OPT_INTERACTIVE, true);
	if (option_is_active_in(*options, OPT_INTERACTIVE) && !explicit_plus_m)
		option_set(options, OPT_MONITOR, true);
}

t_error	options_load(
	t_option *options,
	int argc,
	char **argv,
	size_t *start_index)
{
	bool	explicit_plus_m;
	size_t	remaining_args;

	printf("-------------------------------------\n");
	printf("===> [options_load]\n");
	*options = 0u;
	explicit_plus_m = false;
	while (*start_index < (size_t)argc)
	{
		if (argv[*start_index][0] != '-' && argv[*start_index][0] != '+')
			break ;
		if (options_is_delimiter(argv[*start_index]))
		{
			(*start_index)++;
			break ;
		}
		if (!options_load_one(start_index, argv, options, &explicit_plus_m))
			return (ERR_OPTION_INVALID);
	}
	printf("===> [options_load]\n");
	printf("-------------------------------------\n");
	printf("===> [options_finalize]\n");
	if (*start_index >= (size_t)argc)
		remaining_args = 0;
	else
		remaining_args = (size_t)argc - *start_index;
	options_finalize(options, remaining_args, explicit_plus_m);
	printf("===> [options_finalize]\n");
	printf("-------------------------------------\n\n");
	return (ERR_NO);
}
