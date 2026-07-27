#include <sys/stat.h>
#include "cd_.h"
#include "env.h"

bool	cd_is_directory(const char *path)
{
	struct stat	info;

	if (stat(path, &info) != 0)
		return (false);
	return (S_ISDIR(info.st_mode));
}

static bool	cd_starts_with_dot(const char *dir)
{
	if (dir[0] == '.' && (dir[1] == '\0' || dir[1] == '/'))
		return (true);
	return (dir[0] == '.' && dir[1] == '.'
		&& (dir[2] == '\0' || dir[2] == '/'));
}

static t_error	cd_try_entry(
					t_cd_args *args,
					const t_string *dir,
					const t_string *entry,
					bool *found)
{
	t_string	candidate;

	if (entry->len == 0)
	{
		if (!string_init(&candidate, 0, dir->data, (long)dir->len))
			return (error_sys());
	}
	else
	{
		if (!string_init(&candidate, 0, entry->data, (long)entry->len))
			return (error_sys());
		if ((candidate.data[candidate.len - 1] != '/'
				&& !string_append_n(&candidate, "/", 1))
			|| !string_append_n(&candidate, dir->data, (long)dir->len))
			return (string_free(&candidate), error_sys());
	}
	if (!cd_is_directory(candidate.data))
		return (string_free(&candidate), error(ERR_NO));
	*found = true;
	if (entry->len > 0)
		args->print = true;
	string_free(&args->curpath);
	args->curpath = candidate;
	return (error(ERR_NO));
}

static t_error	cd_search_cdpath(t_cd_args *args, const t_string *dir,
					bool *found)
{
	t_string	cdpath;
	t_string	entry;
	t_error		err;
	size_t		start;

	*found = false;
	err = env_get_from_const("CDPATH", &cdpath);
	if (err.type == ERR_VAR_NOT_FOUND)
		return (error(ERR_NO));
	if (err.type)
		return (err);
	start = 0;
	while (err.type == ERR_NO && !*found && start <= cdpath.len)
	{
		entry.data = cdpath.data + start;
		entry.len = 0;
		while (start + entry.len < cdpath.len
			&& cdpath.data[start + entry.len] != ':')
			entry.len++;
		err = cd_try_entry(args, dir, &entry, found);
		start += entry.len + 1;
	}
	return (string_free(&cdpath), err);
}

t_error	cd_build_curpath(t_cd_args *args, const t_string *dir)
{
	t_error	err;
	bool	found;

	if (dir->len > 0 && dir->data[0] != '/'
		&& !cd_starts_with_dot(dir->data))
	{
		err = cd_search_cdpath(args, dir, &found);
		if (err.type || found)
			return (err);
	}
	string_free(&args->curpath);
	if (!string_init(&args->curpath, 0, dir->data, (long)dir->len))
		return (error_sys());
	return (error(ERR_NO));
}
