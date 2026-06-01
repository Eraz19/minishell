#include "error.h"
#include "var_load_mandatory_priv.h"

/*
2. Initialize mandatory variables
	- IFS = <space><tab><newline>
	- PWD = current working directory (from env or self initialized)
	- PPID = parent process id
*/
t_error	var_load_mandatory(void)
{
	t_error	error;

	error = var_set_ifs();
	if (error != ERR_NO)
		return (error);
	error = var_set_pwd();
	if (error != ERR_NO)
		return (error);
	return (var_set_ppid());
}
