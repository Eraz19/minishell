#include "utils.h"
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>

// @ret ERR_FILE_NOT_EXECUTABLE / ERR_FILE_NOT_READABLE
static inline t_error	select_error(t_search_file_mode mode)
{
	if (mode == SEARCH_FILE_EXEC)
		return (error(ERR_FILE_NOT_EXECUTABLE));
	return (error(ERR_FILE_NOT_READABLE));
}

t_error	check_file(
			const t_string *file_path,
			t_search_file_mode mode,
			bool *ref_found)
{
	struct stat	st;

	if (stat(file_path->data, &st) == -1)
	{
		if (errno == ENOENT || errno == ENOTDIR)
			return (error(ERR_FILE_NOT_FOUND));
		if (errno == EACCES || errno == ELOOP || errno == ENAMETOOLONG)
		{
			*ref_found = true;
			return (select_error(mode));
		}
		return (error_sys());
	}
	*ref_found = true;
	if (S_ISDIR(st.st_mode))
		return (select_error(mode));
	else if (mode == SEARCH_FILE_EXEC && access(file_path->data, X_OK) != 0)
		return (select_error(mode));
	else if (mode == SEARCH_FILE_READ && access(file_path->data, R_OK) != 0)
		return (select_error(mode));
	return (error(ERR_NO));
}
