#include "variables.h"
# include <stdio.h>	// TODO: tmp debug

/*
cf [2.5.3 Shell Variables](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_05_03)
- "The shell shall set IFS to <space><tab><newline> when it is invoked"
*/
t_error	var_set_ifs(t_var_list *variables)
{
	t_error	error;
	char	ifs_value[4];

	ifs_value[0] = ' ';
	ifs_value[1] = '\t';
	ifs_value[2] = '\n';
	ifs_value[3] = '\0';
	error = var_set(variables, "IFS", ifs_value);
	if (error != ERR_NO)
		return (error);
	printf("-> 'IFS' has been set to '%s'\n", ifs_value);
	return (ERR_NO);
}
