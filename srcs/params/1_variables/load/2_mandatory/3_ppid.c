#include "variables.h"
#include <stdlib.h>
# include <stdio.h>	// TODO: tmp debug

#include "ft_getppid.h"

/*
cf [2.5.3 Shell Variables](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_05_03)
	- Set by the shell to the decimal value of its parent process ID during initialization of the shell
*/
t_error	var_set_ppid(t_var_list *variables, char *parent_shell_ppid)
{
	char	*ppid;
	t_error	error;

	if (!parent_shell_ppid)
	{
		ppid = ft_ltoa((long)ft_getppid());
		if (!ppid)
			return (ERR_LIBC);
	}
	else
		ppid = parent_shell_ppid;
	error = var_set(variables, "PPID", ppid);
	if (error != ERR_NO)
		return (error);
	printf("-> 'PPID' has been set to '%s'\n", ppid);
	free(ppid);
	return (ERR_NO);
}
