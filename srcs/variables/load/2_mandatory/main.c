#include "variable.h"
#include "var_load_mandatory_priv.h"

/*
2. Initialize mandatory variables
	- IFS = <space><tab><newline>
	- PWD = current working directory (from env or self initialized)
	- PPID = parent process id
*/
t_error	var_load_mandatory(t_var_list *variables)
{
	t_error	error;

	error = var_set_ifs(variables);
	if (error != ERR_NO)
		return (error);
	error = var_set_pwd(variables);
	if (error != ERR_NO)
		return (error);
	return (var_set_ppid(variables));
}
