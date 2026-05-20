#include "asm_stubs.h"
#include "variables.h"
#include <stdlib.h>
# include "logs.h"	// TODO: tmp debug

/*
cf [2.5.3 Shell Variables](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_05_03)
	- Set by the shell to the decimal value of its parent process ID during initialization of the shell
*/
t_error	var_set_ppid(void)
{
	char	*ppid;
	t_error	error;

	ppid = ft_pidtoa(ft_getppid());
	if (!ppid)
		return (ERR_LIBC);
	error = var_set("PPID", ppid, false, false);
	print_pass("'PPID' has been set to '%s'\n", ppid);
	free(ppid);
	return (error);
}
