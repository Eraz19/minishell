#ifndef OPTIONS_H
# define OPTIONS_H

# include "error.h"
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>

# define OPT_EXPORT_ALL		(1u << 0)	// -a: all variables are exported by default
# define OPT_NOTIFY			(1u << 1)	// -b: immediate notification of terminated jobs
# define OPT_NOCLOBBER		(1u << 2)	// -C: prevent file overwrite with '>'
# define OPT_ERREXIT		(1u << 3)	// -e: exit on command error
# define OPT_NOGLOB			(1u << 4)	// -f: disable pathname expansion (globbing)
# define OPT_HASHALL		(1u << 5)	// -h: remember command locations (hashing)
# define OPT_INTERACTIVE	(1u << 6)	// -i: shell is interactive (not settable via 'set')
# define OPT_MONITOR		(1u << 7)	// -m: enable job control
# define OPT_NOEXEC			(1u << 8)	// -n: read commands but do not execute
# define OPT_NOUNSET		(1u << 9)	// -u: error on unset variables
# define OPT_VERBOSE		(1u << 10)	// -v: print input lines as read
# define OPT_XTRACE			(1u << 11)	// -x: print commands and arguments after expansion
# define OPT_CMD_STRING		(1u << 12)	// -c: read commands from command_string instead of stdin/file
# define OPT_STDIN_INPUT	(1u << 13)	// -s: read commands from standard input
# define OPT_IGNOREEOF		(1u << 14)	// -o ignoreeof: prevent an interactive shell from exiting on end-of-file
# define OPT_NOLOG			(1u << 15)	// -o nolog: prevent function definitions from being entered in command history (may have no effect)
# define OPT_PIPEFAIL		(1u << 16)	// -o pipefail: derive pipeline exit status from all commands, not just the last one
# define OPT_VI				(1u << 17)	// -o vi: enable shell command line editing using the built-in vi editor
# define OPT_SINGLE_COUNT	14

typedef uint32_t	t_option;

void	options_init(t_option *options);
t_error	options_load(t_option *options, int argc, char **argv, size_t *count);
void	options_free(t_option *options);

void	option_set(t_option *options, t_option option, bool on);
bool	option_is_active(t_option option);
bool	option_is_active_in(t_option options, t_option option);
t_error	options_to_string(t_option options, char **dst);

#endif
