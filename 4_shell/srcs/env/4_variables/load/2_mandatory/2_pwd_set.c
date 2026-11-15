/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_pwd_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:10:44 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 21:43:00 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "variables.h"
#include "var_load_mandatory_priv.h"
#include "posix_helpers.h"
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/param.h>
#include <sys/stat.h>

#define PWD_NAME	"PWD"

static inline void	pwd_build_name(t_string *out)
{
	static char	name[] = PWD_NAME;
	size_t		len;

	len = sizeof(PWD_NAME) - 1;
	string_take(out, name, len + 1, (ssize_t)len);
}

// ERR_SHELL_NOT_FOUND / ERR_VAR_INVALID_NAME / ERR_VAR_READ_ONLY /
// ERR_SIZE_MAX_REACHED / ERR_LIBC.
static inline t_error	set_default_pwd(t_string *name, bool export)
{
	t_string	value;
	t_error		err;

	string_init(&value, 0, NULL, 0);
	err = posix_getcwd(&value);
	if (err.type == ERR_LIBC && err.saved_errno == EACCES)
	{
		if (!string_append_n(&value, PWD_UNSPECIFIED_VALUE, -1))
			return (string_free(&value), error_sys());
	}
	else if (err.type)
		return (string_free(&value), err);
	err = var_set(name, &value, export, false);
	string_free(&value);
	return (err);
}

// ERR_SHELL_NOT_FOUND / ERR_VAR_INVALID_NAME / ERR_VAR_READ_ONLY / ERR_LIBC
static inline t_error	process_existing_pwd(t_string *name, t_string *value)
{
	bool	is_valid;
	t_error	err;

	err = var_pwd_is_valid(value->data, &is_valid);
	if (err.type)
		return (err);
	else if (is_valid)
		return (err);
	return (set_default_pwd(name, true));
}

t_error	var_set_pwd(void)
{
	t_string	name;
	t_string	value;
	t_error		err;

	pwd_build_name(&name);
	string_init(&value, 0, NULL, 0);
	err = var_get(&name, &value);
	if (err.type == ERR_NO)
		err = process_existing_pwd(&name, &value);
	if (err.type == ERR_VAR_NOT_FOUND)
		err = set_default_pwd(&name, false);
	string_free(&value);
	return (err);
}
