#ifndef LOADER_H
# define LOADER_H

# include "builder.h"
# include "variable.h"
# include <stdint.h>

/* ************************************************************************* */
/*                               SHELL OPTIONS                               */
/* ************************************************************************* */

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

/* ************************************************************************* */
/*                              SHELL VARIABLES                              */
/* ************************************************************************* */

typedef struct s_param
{
	int			last_status;
	pid_t		shell_pid;
	pid_t		last_bg_pid;
	char		**positional_params;
	size_t		positional_count;
}	t_param;

typedef struct s_state
{
	t_var_list	variables;
	uint32_t	options;
	t_param		params;
}	t_state;

/* ************************************************************************* */
/*                               GLOBAL STRUCT                               */
/* ************************************************************************* */

typedef struct s_shell
{
	t_state		state;
	// t_scanner	scanner;
	t_builder	builder;
	// t_runner	runner;
}	t_shell;

/*
1. Load envp variables with valid shell names
	- exported = true
	- readonly = false
	- invalid names: do not initialize shell variables from them

2. Override/init mandatory shell variables:
	- IFS = ` \t\n` (<space><tab><newline>)
	- PPID = <parent process id> ⚠️ getppid() forbidden 😭
	- PWD = initialized according to POSIX PWD rules:
		a) use env PWD if valid absolute current directory without . or ..
		b) otherwise use physical pwd equivalent to pwd -P => getcwd()

3. Init [UP] defaults if you support User Portability Utilities
	- PS1 = "$ " if absent
	- PS2 = "> " if absent
	- PS4 = "+ " if absent

[END OF VARIABLE MODULE RESPONSABILLITY]

4. Initialize shell state parameters
	- $- = current option flags		(state.options)
		- i from isatty()
		- others from argv
	- $? = 0						(state.params.last_status)
	- $$ = pid of invoked shell		(state.params.shell_pid)
	- $0 = shell/script name		(????)

5. If interactive and ENV is set
	- expand ENV
	- read/tokenize/parse/execute that file before interactive commands
*/

#endif
