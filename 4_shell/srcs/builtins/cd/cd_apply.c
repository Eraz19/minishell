/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_apply.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:40:40 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 13:40:41 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>
#include "cd_.h"
#include "env.h"
#include "posix_helpers.h"

static t_error	cd_set_var(const char *name, const t_string *value)
{
	t_string	name_str;
	t_error		err;

	if (!string_init(&name_str, 0, name, -1))
		return (error_sys());
	err = env_set_variable(&name_str, value, true, false);
	return (string_free(&name_str), err);
}

static void	cd_shorten(t_cd_args *args, const t_string *pwd)
{
	size_t	skip;

	if (args->curpath.len < PATH_MAX || pwd->len == 0)
		return ;
	if (str_ncmp(args->curpath.data, pwd->data, pwd->len) != 0)
		return ;
	skip = pwd->len;
	if (pwd->data[pwd->len - 1] != '/')
	{
		if (args->curpath.data[skip] != '/')
			return ;
		skip++;
	}
	if (args->curpath.len == skip)
		return ;
	args->curpath.len -= skip;
	ft_memmove(args->curpath.data, args->curpath.data + skip,
		args->curpath.len + 1);
}

static t_error	cd_update_pwd(t_cd_args *args, const char *utility)
{
	t_string	physical;
	t_error		getcwd_err;
	t_error		err;

	if (args->mode == 'L')
		return (cd_set_var("PWD", &args->curpath));
	getcwd_err = posix_getcwd(&physical);
	if (getcwd_err.type)
	{
		err = cd_set_var("PWD", &args->curpath);
		if (err.type == ERR_NO && args->ensure_pwd)
			return (error_print(getcwd_err, utility, "PWD", NULL, NULL));
		return (err);
	}
	err = cd_set_var("PWD", &physical);
	return (string_free(&physical), err);
}

static t_error	cd_chdir_and_update(
					t_cd_args *args,
					const t_string *oldpwd,
					const char *utility)
{
	const char	*path;
	t_error		err;

	path = args->curpath.data;
	if (path == NULL)
		path = "";
	if (chdir(path) != 0)
	{
		error_print(error_sys(), utility, path, NULL, NULL);
		return (error(ERR_BUILTIN));
	}
	err = cd_update_pwd(args, utility);
	if (err.type)
		return (err);
	return (cd_set_var("OLDPWD", oldpwd));
}

t_error	cd_apply(t_cd_args *args, const char *utility)
{
	t_string	oldpwd;
	t_error		err;

	err = env_get_from_const("PWD", &oldpwd);
	if (err.type == ERR_VAR_NOT_FOUND)
	{
		err = error(ERR_NO);
		string_init(&oldpwd, 0, NULL, 0);
	}
	if (err.type)
		return (err);
	cd_shorten(args, &oldpwd);
	err = cd_chdir_and_update(args, &oldpwd, utility);
	return (string_free(&oldpwd), err);
}
