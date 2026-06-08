#ifndef OPTIONS_PRIV_H
# define OPTIONS_PRIV_H

# include "options.h"

// @ret ERR_OPT_INVALID
t_error	options_process_flag(
	t_option *options,
	char flag,
	bool on,
	bool *explicit_plus_m);

// @ret ERR_OPT_INVALID_ARG
t_error	options_process_name(
	t_option *options,
	const char *arg,
	bool on,
	bool *explicit_plus_m);

#endif
