#ifndef SET__H
# define SET__H

# include "error.h"
# include "ft_getopt.h"

/**
 * @brief Applies every parsed @c set option to the live shell state.
 *
 * A @c -o / @c +o without argument prints the current option settings
 * instead (human-readable for @c -o, re-input format for @c +o, POSIX
 * leaves the @c -o format unspecified).
 *
 * @param out Parsed options from @ref ft_getopt (borrowed).
 * @return @c ERR_SHELL_NOT_FOUND if the shell data is unavailable;
 *         @c ERR_INTERRUPTED or @c ERR_POSIX_WRITE from the option
 *         printers; @c ERR_LIBC on system failure; @c ERR_NO on
 *         success.
 */
t_error	set_apply_options(t_getopt_out *out);

#endif
