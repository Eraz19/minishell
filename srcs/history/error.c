#include "history_.h"

t_error	history_error_qualify(t_error err)
{
	if (err.type == ERR_NO)
		return (err);
	if (err.type == ERR_LIBC)
		return (error_print(err, "history", NULL, NULL));
	if (err.type >= ERR_INTERRUPTED)
		return (err);
	err = error_print(err, "history", NULL, NULL);
	return (err.type = ERR_INTERNAL, err);
}
