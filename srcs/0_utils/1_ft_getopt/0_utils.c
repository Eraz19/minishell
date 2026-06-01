#include "ft_getopt_priv.h"

#define GETOPT_FMESSAGE_CAP	32

t_error	getopt_add_option(t_getopt_state *state, t_getopt_option *src)
{
	if (!vector_push(&state->out->options, src))
		return (ERR_LIBC);
	return (ERR_NO);
}

t_error	getopt_err(
	t_getopt_state *state,
	char flag,
	const char *arg, t_error error)
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
	return (error_print(state->in->builtin_name, fmessage, error));
}
