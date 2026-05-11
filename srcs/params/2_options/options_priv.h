#ifndef OPTIONS_PRIV_H
# define OPTIONS_PRIV_H

# include "options.h"

bool	options_process_name(
	t_option *options,
	const char *arg,
	bool on,
	bool *explicit_plus_m);

bool	options_process_flags(
	t_option *options,
	const char *arg,
	bool *explicit_plus_m);

#endif
