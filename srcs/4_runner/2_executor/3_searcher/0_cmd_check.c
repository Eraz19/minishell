#include "cmd_searcher_priv.h"
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>

t_error	cmd_check(const t_string *cmd_path, bool *ref_found)
{
	struct stat	st;

	if (stat(cmd_path->data, &st) == -1)
	{
		if (errno == ENOENT || errno == ENOTDIR)
			return (error(ERR_POSIX_CMD_NOT_FOUND));
		else if (errno == EACCES || errno == ELOOP || errno == ENAMETOOLONG)
			return (*ref_found = true, error(ERR_POSIX_CMD_NOT_EXECUTABLE));
		return (error_sys());
	}
	else if (S_ISDIR(st.st_mode))
		return (*ref_found = true, error(ERR_POSIX_CMD_NOT_EXECUTABLE));
	else if (access(cmd_path->data, X_OK) != 0)
		return (*ref_found = true, error(ERR_POSIX_CMD_NOT_EXECUTABLE));
	return (error(ERR_NO));
}
