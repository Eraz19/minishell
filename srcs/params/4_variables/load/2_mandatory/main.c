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
	t_error	err;

	err = var_set_ifs();
	if (err.type != ERR_NO)
		return (err);
	err = var_set_pwd();
	if (err.type != ERR_NO)
		return (err);
	return (var_set_ppid());
}
