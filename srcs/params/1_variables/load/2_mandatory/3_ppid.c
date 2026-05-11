#include "asm_stubs.h"
#include "variables.h"
#include <stdlib.h>
# include <stdio.h>	// TODO: tmp debug

/*
cf [2.5.3 Shell Variables](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_05_03)
	- Set by the shell to the decimal value of its parent process ID during initialization of the shell
*/
t_error	var_set_ppid(t_var_list *variables, const char *parent_shell_ppid)
{
	char	*ppid;
	t_error	error;

	if (!parent_shell_ppid)
	{
		ppid = ft_ltoa((long)ft_getppid());
		if (!ppid)
			return (ERR_LIBC);
		error = var_set(variables, "PPID", ppid);
	}
	else
		error = var_set(variables, "PPID", parent_shell_ppid);
	if (error == ERR_NO && !parent_shell_ppid)
		printf("-> 'PPID' has been set to '%s'\n", ppid);
	else if (error == ERR_NO)
		printf("-> 'PPID' has been set to '%s'\n", parent_shell_ppid);
	if (!parent_shell_ppid)
		free(ppid);
	return (error);
}
