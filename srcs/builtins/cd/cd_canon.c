#include <sys/stat.h>
#include <errno.h>
#include "cd_.h"
#include "params.h"

static t_error	cd_prepend_pwd(t_cd_args *args)
{
	t_string	pwd;
	t_error		err;

	err = params_get_from_const("PWD", &pwd);
	if (err.type)
		return (err);
	if ((pwd.len == 0 || pwd.data[pwd.len - 1] != '/')
		&& !string_append_n(&pwd, "/", 1))
		return (string_free(&pwd), error_sys());
	if (!string_append_n(&pwd, args->curpath.data, (long)args->curpath.len))
		return (string_free(&pwd), error_sys());
	string_free(&args->curpath);
	args->curpath = pwd;
	return (err);
}

static t_error	cd_pop_component(t_string *out, const char *utility)
{
	struct stat	info;
	size_t		i;

	if (out->len <= 1)
		return (error(ERR_NO));
	if (stat(out->data, &info) != 0)
		return (error_print(error_sys(), utility, out->data, NULL, NULL));
	if (!S_ISDIR(info.st_mode))
	{
		errno = ENOTDIR;
		return (error_print(error_sys(), utility, out->data, NULL, NULL));
	}
	i = out->len;
	while (i > 1 && out->data[i - 1] != '/')
		i--;
	if (i > 1)
		i--;
	out->len = i;
	out->data[i] = '\0';
	return (error(ERR_NO));
}

static t_error	cd_apply_component(t_string *out, const char *comp,
					size_t len, const char *utility)
{
	if (len == 1 && comp[0] == '.')
		return (error(ERR_NO));
	if (len == 2 && comp[0] == '.' && comp[1] == '.')
		return (cd_pop_component(out, utility));
	if (out->len > 1 && !string_append_n(out, "/", 1))
		return (error_sys());
	if (!string_append_n(out, comp, (long)len))
		return (error_sys());
	return (error(ERR_NO));
}

static t_error	cd_walk_components(t_cd_args *args, t_string *out,
					const char *utility)
{
	size_t	i;
	size_t	len;
	t_error	err;

	i = 0;
	err = error(ERR_NO);
	while (err.type == ERR_NO && i < args->curpath.len)
	{
		while (i < args->curpath.len && args->curpath.data[i] == '/')
			i++;
		len = 0;
		while (i + len < args->curpath.len
			&& args->curpath.data[i + len] != '/')
			len++;
		if (len == 0)
			break ;
		err = cd_apply_component(out, args->curpath.data + i, len, utility);
		i += len;
	}
	return (err);
}

t_error	cd_canonicalize(t_cd_args *args, const char *utility)
{
	t_string	result;
	t_error		err;

	if (args->curpath.len == 0)
		return (error(ERR_NO));
	if (args->curpath.data[0] != '/')
	{
		err = cd_prepend_pwd(args);
		if (err.type)
			return (err);
	}
	if (!string_init(&result, 0, "/", 1))
		return (error_sys());
	err = cd_walk_components(args, &result, utility);
	if (err.type)
		return (string_free(&result), err);
	string_free(&args->curpath);
	args->curpath = result;
	return (err);
}
