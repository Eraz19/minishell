#ifndef PARAMS_H
# define PARAMS_H

# include <stdbool.h>
# include <stdint.h>
# include <stddef.h>
# include <sys/types.h>

# define OPT_EXPORT_ALL		1 << 0	// -a: all variables are exported by default
# define OPT_NOTIFY			1 << 1	// -b: immediate notification of terminated jobs
# define OPT_NOCLOBBER		1 << 2	// -C: prevent file overwrite with '>'
# define OPT_ERREXIT		1 << 3	// -e: exit on command error
# define OPT_NOGLOB			1 << 4	// -f: disable pathname expansion (globbing)
# define OPT_HASHALL		1 << 5	// -h: remember command locations (hashing)
# define OPT_MONITOR		1 << 6	// -m: enable job control
# define OPT_NOEXEC			1 << 7	// -n: read commands but do not execute
# define OPT_NOUNSET		1 << 8	// -u: error on unset variables
# define OPT_VERBOSE		1 << 9	// -v: print input lines as read
# define OPT_XTRACE			1 << 10	// -x: print commands and arguments after expansion
# define OPT_INTERACTIVE	1 << 11	// (i): shell is interactive (not settable via 'set')

typedef struct s_shell_params
{
	bool		is_subshell;
	const char	*shell_name;			// 0
	const char	*script_name;			// 0
	uint32_t	options;				// -
	char		**positional_params;	// @ *
	size_t		positional_count;		// #
	pid_t		pid;					// $
	pid_t		last_bg_pid;			// !
	int			last_status;			// ?
}	t_shell_params;

#endif
