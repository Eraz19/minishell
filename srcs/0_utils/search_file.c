#include "utils.h"
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>

// @ret ERR_LIBC
static inline t_error	build_file_path(
							const t_string *path_entry,
							const t_string *filename,
							t_string *out_file_path)
{
	out_file_path->len = 0;
	if (path_entry->len == 0)
	{
		if (!string_append_n(out_file_path, "./", 2))
			return (error_sys());
	}
	else
	{
		if (!string_append(out_file_path, path_entry))
			return (error_sys());
		if (path_entry->data[path_entry->len - 1] != '/'
			&& !string_append_n(out_file_path, "/", 1))
				return (error_sys());
	}
	if (!string_append(out_file_path, filename))
		return (error_sys());
	return (error(ERR_NO));
}

// @ret ERR_FILE_NOT_EXECUTABLE / ERR_FILE_NOT_READABLE
static inline t_error	select_error(t_search_file_mode mode)
{
	if (mode == SEARCH_FILE_EXEC)
		return (error(ERR_FILE_NOT_EXECUTABLE));
	return (error(ERR_FILE_NOT_READABLE));
}

// @ret ERR_FILE_NOT_FOUND / ERR_FILE_NOT_EXECUTABLE / ERR_FILE_NOT_READABLE
// 		/ ERR_LIBC
static inline t_error	search_file_in_path_entries(
							const t_vector *path_entries,
							const t_string *filename,
							t_search_file_mode mode,
							t_string *out_file_path)
{
	size_t			i;
	bool			found;
	const t_string	*entry;
	t_error			err;

	(void)string_init(out_file_path, 0, NULL, 0);
	found = false;
	i = 0;
	while (i < path_entries->len)
	{
		entry = &((t_string *)path_entries->data)[i++];
		err = build_file_path(entry, filename, out_file_path);
		if (err.type)
			return (string_free(out_file_path), err);
		err = check_file(out_file_path, mode, &found);
		if (err.type == ERR_NO)
			return (err);
		string_free(out_file_path);
		if (err.type == ERR_LIBC)
			return (err);
	}
	if (found == true)
		return (select_error(mode));
	return (error(ERR_FILE_NOT_FOUND));
}

t_error	search_file(
			const t_string *raw_path,
			const t_string *filename,
			t_search_file_mode mode,
			t_string *out_file_path)
{
	t_vector	path_entries;
	t_error		err;

	if (raw_path->data == NULL)
		return (error(ERR_FILE_NOT_FOUND));
	if (!string_split_on_char(raw_path, ':', true, &path_entries))
		return (error_sys());
	err = search_file_in_path_entries(
			&path_entries, filename, mode, out_file_path);
	vector_free(&path_entries, string_free_void);
	return (err);
}
