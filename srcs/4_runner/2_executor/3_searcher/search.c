#include "cmd_searcher.h"
#include "entry_is_target.h"
#include "cmd_error.h"
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>

// TODO: bool use_cache

/*
ENOENT / ENOTDIR:
    ce candidat n’existe pas
    continuer

EACCES:
    candidat trouvé mais non executable
    mémoriser found_but_not_executable
    continuer

ENOEXEC:
    candidat trouvé
    POSIX impose de lancer un shell avec ce pathname comme script,
    sauf si vous appliquez une heuristic de rejet
    ne pas continuer PATH normalement

ELOOP / ENAMETOOLONG:
    candidat non utilisable
    mémoriser found_but_not_executable
    continuer ou échouer 126 selon votre politique

E2BIG / ENOMEM:
    vraie erreur d’exécution / système
    pas un simple "not found"

autre erreur:
    plutôt 126 si le candidat existe mais ne peut pas être invoqué,
    ou erreur système selon votre modèle d’erreurs interne
*/

#define PATH_NAME				"PATH"
#define PATH_VALUE_START_INDEX	5

// @ret ERR_CMD_NOT_FOUND
static inline t_error	cmd_find_path_in_envp(
							const t_string *cmd_name,
							const t_vector *envp,
							t_string *out_path)
{
	char	*entry;
	size_t	i;

	i = 0;
	while (i < envp->len)
	{
		entry = ((char **)envp->data)[i];
		if (entry == NULL)
			break ;
		if (cmd_entry_is_target(PATH_NAME, entry))
		{
			if (entry[PATH_VALUE_START_INDEX] == '\0')
				return (cmd_not_found(cmd_name));
			out_path->data = entry + PATH_VALUE_START_INDEX;
			out_path->cap = 0;
			out_path->len = str_len(out_path->data);
			return (error(ERR_NO));
		}
		i++;
	}
	return (cmd_not_found(cmd_name));
}

// @ret ERR_LIBC
static inline t_error	cmd_build_path(
							const t_string *cmd_name,
							const t_string *path_entry,
							t_string *out_cmd_path)
{
	out_cmd_path->len = 0;
	if (path_entry->len == 0)
	{
		if (!string_append_n(out_cmd_path, "./", 2))
			return (error_sys());
	}
	else
	{
		if (!string_append(out_cmd_path, path_entry))
			return (error_sys());
		if (path_entry->data[path_entry->len - 1] != '/'
			&& !string_append_n(out_cmd_path, "/", 1))
				return (error_sys());
	}
	if (!string_append(out_cmd_path, cmd_name))
		return (error_sys());
	return (error(ERR_NO));
}

static inline t_error	cmd_check(
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

// @ret ERR_CMD_NOT_FOUND / ERR_LIBC
static inline t_error	cmd_find(
							const t_string *cmd_name,
							t_vector *path_entries,
							t_string *out_cmd_path)
{
	bool			found_but_not_executable;
	const t_string	*entry;
	size_t			i;
	t_error			err;

	found_but_not_executable = false;
	(void)string_init(out_cmd_path, 0, NULL, 0);
	i = 0;
	while (i < path_entries->len)
	{
		entry = &((t_string *)path_entries->data)[i++];
		err = cmd_build_path(cmd_name, entry, out_cmd_path);
		if (err.type)
			return (string_free(out_cmd_path), err);
		if (access(out_cmd_path->data, F_OK) == 0)
		{
			if (access(out_cmd_path->data, X_OK) == 0)
				return (error(ERR_NO));
			found_but_not_executable = true;
		}
	}
	string_free(out_cmd_path);
	if (found_but_not_executable == true)
		return (cmd_not_executable(cmd_name));
	return (cmd_not_found(cmd_name));
}

t_error	cmd_search(
			const t_string *cmd_name,
			const t_vector *envp,
			t_string *out_cmd_path)
{
	t_string	path;
	t_vector	path_entries;
	t_error		err;

	if (string_get_index_c(cmd_name, '/') >= 0)
	{
		if (!string_dup(out_cmd_path, cmd_name))
			return (error_sys());
		return (error(ERR_NO));
	}
	err = cmd_find_path_in_envp(cmd_name, envp, &path);
	if (err.type)
		return (err);
	if (!string_split_on_char(&path, ':', true, &path_entries))
		return (error_sys());
	err = cmd_find(cmd_name, &path_entries, out_cmd_path);
	vector_free(&path_entries, string_free_void);
	return (err);
}
