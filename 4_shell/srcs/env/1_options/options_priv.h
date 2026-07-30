#ifndef OPTIONS_PRIV_H
# define OPTIONS_PRIV_H

# include "options.h"

/**
 * @brief Apply a single short option flag.
 *
 * @param options Bitset to modify (borrowed).
 * @param flag Short flag character.
 * @param on True to enable, false to disable.
 * @param explicit_plus_m Tracks explicit @c +m usage (borrowed).
 * @return @c ERR_OPT_INVALID on failure.
 */
t_error	options_process_flag(
	t_option *options,
	char flag,
	bool on,
	bool *explicit_plus_m);

/**
 * @brief Apply a long option name.
 *
 * @param options Bitset to modify (borrowed).
 * @param arg Long option name (borrowed, read-only).
 * @param on True to enable, false to disable.
 * @param explicit_plus_m Tracks explicit @c +m usage (borrowed).
 * @return @c ERR_OPT_INVALID_ARG on failure.
 */
t_error	options_process_name(
	t_option *options,
	const char *arg,
	bool on,
	bool *explicit_plus_m);

#endif
