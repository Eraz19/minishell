#include <dirent.h>
#include "utils.h"
#include "path_comps_.h"
#include "path_matches_.h"

t_error	path_match_append(t_string *cand, const char *pattern)
{
	size_t	i;

	if (pattern == NULL)
		return (error(ERR_NO));
	i = 0;
	while (pattern[i] != '\0')
	{
		if (pattern[i] == '\\' && pattern[i + 1] != '\0')
			i++;
		if (!string_append_n(cand, &pattern[i], 1))
			return (error_sys());
		i++;
	}
	return (error(ERR_NO));
}

static bool	skip_lookup_dir_entry(const char *name, const t_path_comp *comp)
{
	const char	*pattern;

	if (name[0] != '.')
		return (false);
	if (name[1] == '\0')
		return (true);
	if (name[1] == '.' && name[2] == '\0')
		return (true);
	pattern = comp->pattern.data;
	if (pattern[0] == '.' || (pattern[0] == '\\' && pattern[1] == '.'))
		return (false);
	return (true);
}

static bool	is_dir_matches(const char *name, const t_path_comp *comp)
{
	if (skip_lookup_dir_entry(name, comp))
		return (false);
	return (match_pattern(comp->pattern.data, name, str_len(name)));
}

static t_error	add_match(
			t_path_matches *out,
			const t_string *match,
			const char *dir_name,
			bool first)
{
	t_error		err;
	t_string	new_match;

	if (!string_init(&new_match, 0, NULL, 0))
		return (error_sys());
	if (match->len > 0
		&& !string_append_n(&new_match, match->data, (long)match->len))
		return (err = error_sys(), string_free(&new_match), err);
	if (!first && !string_append_n(&new_match, "/", 1))
		return (err = error_sys(), string_free(&new_match), err);
	if (!string_append_n(&new_match, dir_name, -1))
		return (err = error_sys(), string_free(&new_match), err);
	if (!vector_push(out, &new_match))
		return (err = error_sys(), string_free(&new_match), err);
	return (error(ERR_NO));
}

t_error	add_lookup_dir_matching(
			t_path_matches *out,
			t_string *match,
			t_path_comp *comp,
			bool first)
{
	DIR				*dir;
	t_error			err;
	const char		*path;
	struct dirent	*dir_entry;

	path = match->data;
	if (match->len == 0 && first)
		path = ".";
	else if (match->len == 0)
		path = "/";
	dir = opendir(path);
	if (dir == NULL)
		return (error(ERR_NO));
	dir_entry = readdir(dir);
	while (dir_entry != NULL)
	{
		if (is_dir_matches(dir_entry->d_name, comp))
		{
			err = add_match(out, match, dir_entry->d_name, first);
			if (err.type)
				return (closedir(dir), err);
		}
		dir_entry = readdir(dir);
	}
	return (closedir(dir), error(ERR_NO));
}
