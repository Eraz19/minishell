#include "shell.h"
#include <stdlib.h>
# include "logs.h"		// DEBUG
# include <assert.h>	// DEBUG

t_error	option_is_active(t_option option, bool *out)
{
	t_params	*params;

	params = shell_get_params();
	if (!params)
		return (error(ERR_SHELL_NOT_FOUND));
	*out = (params->options & option) != 0;
	return (error(ERR_NO));
}

bool	option_is_active_in(t_option options, t_option option)
{
	return ((options & option) != 0);
}

void	option_set(t_option *options, t_option option, bool on)
{
	if (on)
	{
		print_pass("option activated                       %s\n", option_to_string(option));
		*options |= option;
	}
	else
	{
		print_pass("option disabled                        %s\n", option_to_string(option));
		*options &= ~option;
	}
}

static void	options_add_to_string(t_option options, char *buff, size_t *len)
{
	if (option_is_active_in(options, OPT_NOCLOBBER))
		buff[(*len)++] = 'C';
	if (option_is_active_in(options, OPT_ERREXIT))
		buff[(*len)++] = 'e';
	if (option_is_active_in(options, OPT_NOGLOB))
		buff[(*len)++] = 'f';
	if (option_is_active_in(options, OPT_HASHALL))
		buff[(*len)++] = 'h';
	if (option_is_active_in(options, OPT_INTERACTIVE))
		buff[(*len)++] = 'i';
	if (option_is_active_in(options, OPT_MONITOR))
		buff[(*len)++] = 'm';
	if (option_is_active_in(options, OPT_NOEXEC))
		buff[(*len)++] = 'n';
	if (option_is_active_in(options, OPT_NOUNSET))
		buff[(*len)++] = 'u';
	if (option_is_active_in(options, OPT_VERBOSE))
		buff[(*len)++] = 'v';
	if (option_is_active_in(options, OPT_XTRACE))
		buff[(*len)++] = 'x';
	if (option_is_active_in(options, OPT_CMD_STRING))
		buff[(*len)++] = 'c';
	if (option_is_active_in(options, OPT_STDIN_INPUT))
		buff[(*len)++] = 's';
}

t_error	options_get(t_option options, t_string *dst)
{
	char	*buff;
	size_t	cap;
	size_t	len;

	assert(dst != NULL);
	cap = OPT_SINGLE_COUNT + 1;
	buff = malloc (cap);
	if (!buff)
		return (error_sys());
	len = 0;
	if (option_is_active_in(options, OPT_EXPORT_ALL))
		buff[len++] = 'a';
	if (option_is_active_in(options, OPT_NOTIFY))
		buff[len++] = 'b';
	options_add_to_string(options, buff, &len);
	assert(len <= cap);
	buff[len] = '\0';
	string_take(dst, buff, cap, (ssize_t)len);
	return (error(ERR_NO));
}
