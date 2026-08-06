/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_pwd_is_valid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:10:42 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 15:04:11 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <assert.h>	// DEBUG

static bool	pwd_has_no_dot_components(const char *pwd)
{
	size_t	i;
	size_t	start;
	size_t	len;

	assert(pwd != NULL);
	i = 1;
	while (pwd[i] != '\0')
	{
		start = i;
		while (pwd[i] != '\0' && pwd[i] != '/')
			i++;
		len = i - start;
		if (len == 1 && pwd[start] == '.')
			return (false);
		if (len == 2 && pwd[start] == '.' && pwd[start + 1] == '.')
			return (false);
		while (pwd[i] == '/')
			i++;
	}
	return (true);
}

/*
cf [POSIX.1-2024, Base Definitions, header <sys/stat.h>](https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/sys_stat.h.html)
	- "A file identity is uniquely determined by the combination of st_dev and st_ino"
*/
// @ret ERR_LIBC.
static t_error	pwd_is_the_current_working_dir(const char *pwd, bool *res)
{
	struct stat	current;
	struct stat	from_pwd;

	assert(pwd != NULL);
	assert(res != NULL);
	*res = false;
	if (stat(".", &current) == -1)
		return (error_sys());
	if (stat(pwd, &from_pwd) == -1)
	{
		if (errno == ENOENT || errno == ENOTDIR || errno == ELOOP
			|| errno == ENAMETOOLONG)
			return (error(ERR_NO));
		return (error_sys());
	}
	if (current.st_dev != from_pwd.st_dev)
		return (error(ERR_NO));
	if (current.st_ino != from_pwd.st_ino)
		return (error(ERR_NO));
	*res = true;
	return (error(ERR_NO));
}

/*
cf [2.5.3 Shell Variables](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_05_03)
	- "the value is an absolute pathname"
	- "the value does not contain any components that are dot or dot-dot"
	- "the value is [...] the current working directory"
*/
t_error	var_pwd_is_valid(const char *pwd, bool *res)
{
	assert(res != NULL);
	*res = false;
	if (!pwd)
		return (error(ERR_NO));
	if (pwd[0] != '/')
		return (error(ERR_NO));
	if (!pwd_has_no_dot_components(pwd))
		return (error(ERR_NO));
	return (pwd_is_the_current_working_dir(pwd, res));
}
