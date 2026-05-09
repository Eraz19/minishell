#include "error.h"
#include "options.h"
#include <stddef.h>

static inline bool	options_process_flag1(t_option *options, char flag, bool on)
{
	if (flag == 'a')
		option_set(options, OPT_EXPORT_ALL, on);
	else if (flag == 'b')
		option_set(options, OPT_NOTIFY, on);
	else if (flag == 'C')
		option_set(options, OPT_NOCLOBBER, on);
	else if (flag == 'e')
		option_set(options, OPT_ERREXIT, on);
	else if (flag == 'f')
		option_set(options, OPT_NOGLOB, on);
	else if (flag == 'h')
		option_set(options, OPT_HASHALL, on);
	else if (flag == 'i')
		option_set(options, OPT_INTERACTIVE, on);
	else
		return (false);
	return (true);
}

static inline bool	options_process_flag2(
	t_option *options,
	char flag,
	bool on,
	bool *explicit_plus_m)
{
	if (flag == 'm')
	{
		option_set(options, OPT_MONITOR, on);
		*explicit_plus_m = !on;
	}
	else if (flag == 'n')
		option_set(options, OPT_NOEXEC, on);
	else if (flag == 'u')
		option_set(options, OPT_NOUNSET, on);
	else if (flag == 'v')
		option_set(options, OPT_VERBOSE, on);
	else if (flag == 'x')
		option_set(options, OPT_XTRACE, on);
	else if (flag == 'c')
		option_set(options, OPT_CMD_STRING, on);
	else if (flag == 's')
		option_set(options, OPT_STDIN_INPUT, on);
	else
		return (false);
	return (true);
}

bool	options_process_flags(
	t_option *options,
	const char *arg,
	bool *explicit_plus_m)
{
	size_t	i;
	bool	on;

	if ((arg[0] != '-' && arg[0] != '+') || arg[1] == '\0')
		return (false);
	on = arg[0] == '-';
	i = 1;
	while (arg[i])
	{
		if (options_process_flag1(options, arg[i], on))
			i++;
		else if (options_process_flag2(options, arg[i], on, explicit_plus_m))
			i++;
		else
		{
			error_print(NULL, &arg[i], ERR_OPTION_INVALID);
			return (false);
		}
	}
	return (true);
}
