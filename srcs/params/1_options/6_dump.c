#include "options.h"
# include <stdio.h>
# include "debug.h"

const char	*option_to_string(t_option option)
{
	if (option == OPT_EXPORT_ALL)
		return ("a");
	else if (option == OPT_NOTIFY)
		return ("b");
	else if (option == OPT_NOCLOBBER)
		return ("C");
	else if (option == OPT_ERREXIT)
		return ("e");
	else if (option == OPT_NOGLOB)
		return ("f");
	else if (option == OPT_HASHALL)
		return ("h");
	else if (option == OPT_INTERACTIVE)
		return ("i");
	else if (option == OPT_MONITOR)
		return ("m");
	else if (option == OPT_NOEXEC)
		return ("n");
	else if (option == OPT_NOUNSET)
		return ("u");
	else if (option == OPT_VERBOSE)
		return ("v");
	else if (option == OPT_XTRACE)
		return ("x");
	else if (option == OPT_CMD_STRING)
		return ("c");
	else if (option == OPT_STDIN_INPUT)
		return ("s");
	else if (option == OPT_IGNOREEOF)
		return ("ignoreeof");
	else if (option == OPT_NOLOG)
		return ("nolog");
	else if (option == OPT_PIPEFAIL)
		return ("pipefail");
	else if (option == OPT_VI)
		return ("vi");
	return ("unknown");
}

void	options_dump_all(void)
{
	unsigned int	option;
	const char		*name;
	const char		*value;

	printf("\nDUMP OPTIONS\n");
	option = 1u << 0;
	while (option <= OPT_VI)
	{
		name = option_to_string(option);
		value = bool_to_string(option_is_active(option));
		printf("OPTION %s=%s\n", name, value);
		option <<= 1;
	}
}
