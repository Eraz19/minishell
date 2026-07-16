#include "walker_priv.h"

t_error	walk_normalize_output(t_error err, t_error *opt_err, int *exit_status)
{
	if (opt_err != NULL)
		err = error_priorize(err, *opt_err);
	(void)exit_status;	// TMP (to test if this function is really useful)
	// if (*exit_status < 0)
	// {
	// 	if (err.type)
	// 		*exit_status = (int)err.type;
	// 	else
	// 	{
	// 		err = error_print(error(ERR_INTERNAL), "runner", "walker",
	// 				"returned success but exit status is not set", NULL, NULL);
	// 		*exit_status = (int)err.type;
	// 	}
	// }
	return (err);
}
