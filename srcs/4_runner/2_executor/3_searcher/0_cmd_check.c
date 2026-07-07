#include "cmd_searcher_priv.h"
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>

t_error	cmd_check(
			const t_string *cmd_path,
			bool *out_is_valid,
			bool *ref_found_but_not_executable)
{
	struct stat	st;

	*out_is_valid = false;
	if (stat(cmd_path->data, &st) == -1)
	{
		if (errno == ENOENT || errno == ENOTDIR)
			return (error(ERR_NO));
		else if (errno == EACCES || errno == ELOOP || errno == ENAMETOOLONG)
			return (*ref_found_but_not_executable = true, error(ERR_NO));
		return (error_sys());
	}
	else if (S_ISDIR(st.st_mode))
	{
		*ref_found_but_not_executable = true;
		return (error(ERR_NO));
	}
	else if (access(cmd_path->data, X_OK) != 0)
	{
		*ref_found_but_not_executable = true;
		return (error(ERR_NO));
	}
	*out_is_valid = true;
	return (error(ERR_NO));
}
