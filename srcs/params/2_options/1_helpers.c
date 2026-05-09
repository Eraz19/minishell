#include "options.h"

void	options_init(t_option *options)
{
	*options = 0u;
}

bool	option_is_active(t_option options, t_option option)
{
	return ((options & option) != 0);
}

void	option_set(t_option *options, t_option option, bool on)
{
	if (on)
		*options |= option;
	else
		*options &= ~option;
}

void	options_free(t_option *options)
{
	(void)options;
	return ;
}
