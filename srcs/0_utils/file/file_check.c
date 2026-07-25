#include "utils.h"
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>

// @ret ERR_FILE_NOT_EXECUTABLE / ERR_FILE_NOT_READABLE
static inline t_error	select_error(t_file_type mode)
{
	if (mode == READABLE)
		return (error(ERR_FILE_NOT_READABLE));
	return (error(ERR_FILE_NOT_EXECUTABLE));
}

// @ret ERR_FILE_NOT_FOUND / ERR_FILE_NOT_EXECUTABLE
// 		/ ERR_FILE_NOT_READABLE / ERR_LIBC
static inline t_error	file_check_if_exists(
							const t_string *file_path,
							t_file_type mode,
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
	return (error(ERR_NO));
}

t_error	file_check(const t_string *file_path, t_file_type mode, bool *ref_found)
{
	t_error	err;

	err = file_check_if_exists(file_path, mode, ref_found);
	if (err.type)
		return (err);
	else if (mode == READABLE)
	{
		if (access(file_path->data, R_OK) != 0)
			return (error(ERR_FILE_NOT_READABLE));
	}
	else if (access(file_path->data, X_OK) != 0)
		return (error(ERR_FILE_NOT_EXECUTABLE));
	return (error(ERR_NO));
}
