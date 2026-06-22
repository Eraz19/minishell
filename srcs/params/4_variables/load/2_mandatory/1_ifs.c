#include "variables.h"
# include "logs.h"	// DEBUG

/*
cf [2.5.3 Shell Variables](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_05_03)
- "The shell shall set IFS to <space><tab><newline> when it is invoked"
*/
t_error	var_set_ifs(void)
{
	t_error	err;
	char	ifs_value[4];

	ifs_value[0] = ' ';
	ifs_value[1] = '\t';
	ifs_value[2] = '\n';
	ifs_value[3] = '\0';
	err = var_set("IFS", ifs_value, false, false);
	if (err.type != ERR_NO)
		return (err);
	print_pass("'IFS' has been set to '%s'\n", ifs_value);
	return (error(ERR_NO));
}
