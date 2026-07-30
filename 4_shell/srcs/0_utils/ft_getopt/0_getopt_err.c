#include "ft_getopt_priv.h"

#define GETOPT_FMESSAGE_CAP	32

t_error	getopt_err(
			const t_getopt_state *state,
			char flag,
			const char *arg, t_error_type err_type)
{
	char	fmessage[GETOPT_FMESSAGE_CAP];

	fmessage[0] = flag;
	if (arg)
	{
		fmessage[1] = ':';
		fmessage[2] = ' ';
		str_lcpy(fmessage + 3, arg, GETOPT_FMESSAGE_CAP - 3);
		fmessage[GETOPT_FMESSAGE_CAP - 6] = '[';
		fmessage[GETOPT_FMESSAGE_CAP - 5] = '.';
		fmessage[GETOPT_FMESSAGE_CAP - 4] = '.';
		fmessage[GETOPT_FMESSAGE_CAP - 3] = '.';
		fmessage[GETOPT_FMESSAGE_CAP - 2] = ']';
		fmessage[GETOPT_FMESSAGE_CAP - 1] = '\0';
	}
	else
		fmessage[1] = '\0';
	return (error_print(error(err_type), state->in->builtin_name, fmessage, NULL, NULL));
}
