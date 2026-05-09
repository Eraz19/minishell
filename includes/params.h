#ifndef PARAMS_H
# define PARAMS_H

# include "variables.h"
# include "options.h"
# include <stdbool.h>
# include <stdint.h>
# include <stddef.h>
# include <sys/types.h>

typedef struct s_params
{
	bool		is_subshell;			// (internal)
	const char	*name;					// (internal)
	t_var_list	variables;				// $<var_name>
	t_option	options;				// $-
	const char	*zero;					// $0
	char		**positional_params;	// $@ / $*
	size_t		positional_count;		// $#
	pid_t		pid;					// $$
	pid_t		last_bg_pid;			// $!
	int			last_status;			// $?
}	t_params;

/*
INIT FLOW:
1. [VARIABLES MODULE]	Parse variables from envp
2. [VARIABLES MODULE]	Init variables:
	- IFS
	- PWD
	- PPID
	- PS1
	- PS2
	- PS4
3. [OPTIONS MUDLE]		Parse options from argv
4. [OPTIONS MUDLE]		Init options:
	- `-s`
	- `-i`
	- `-m`
5. [PARAMS MODULE]		Init special parameters:
	- `0`
	- `@` / `*`
	- `#`
	- `$`
	- `!`
	- `?`
6. [LOADER MODULE]		If `-i` is active => process ENV
*/

#endif
