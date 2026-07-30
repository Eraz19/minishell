#include "posix_helpers.h"
#include "history_file_priv.h"

t_error	open_history_file(int *out, const char *path, int flags)
{
	t_error	err;

	err = posix_open_with_mode(path, flags, 0600, out);
	if (err.type)
		return (on_history_file_open_error(err, path));
	return (error(ERR_NO));
}
