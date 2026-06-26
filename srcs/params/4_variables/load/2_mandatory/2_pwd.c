#include "variables.h"
#include "posix_helpers.h"
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/param.h>
#include <sys/stat.h>
# include "logs.h"	// DEBUG

static bool pwd_has_no_dot_components(const char *pwd)
{
	size_t	i;
	size_t	start;
	size_t	len;
	
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
// @ret ERR_LIBC.
static t_error	var_pwd_is_valid(const char *pwd, bool *res)
{
	*res = false;
	if (!pwd)
		return (error(ERR_NO));
	if (pwd[0] != '/')
		return (error(ERR_NO));
	if (!pwd_has_no_dot_components(pwd))
		return (error(ERR_NO));
	return (pwd_is_the_current_working_dir(pwd, res));
}

static inline t_error	handle_pwd_getcwd_error(t_error err, char **pwd)
{
	size_t	default_pwd_len;

	if (err.type == ERR_LIBC && err.saved_errno == EACCES)
	{
		default_pwd_len = str_len(PWD_UNSPECIFIED_VALUE);
		*pwd = malloc(default_pwd_len + 1);
		if (!*pwd)
			return (error_sys());
		(void)str_lcpy(*pwd, PWD_UNSPECIFIED_VALUE, default_pwd_len + 1);
		return (error(ERR_NO));
	}
	return (err);
}

/*
cf [2.5.3 Shell Variables](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_05_03)
	a) "If a value for PWD is passed to the shell in the environment when it is executed, the value is an absolute pathname of the current working directory [...optional...] and the value does not contain any components that are dot or dot-dot, then the shell shall set PWD to the value from the environment"
	b) "Otherwise, the sh utility sets PWD to the pathname that would be output by pwd -P" (= getcwd())
*/
t_error	var_set_pwd(void)
{
	char	*pwd;
	t_error	err;
	bool	is_valid;

	err = var_get("PWD", &pwd);
	if (err.type != ERR_NO && err.type != ERR_VAR_NOT_FOUND)
		return (err);
	if (err.type == ERR_NO)
	{
		err = var_pwd_is_valid(pwd, &is_valid);
		free(pwd);
		if (err.type != ERR_NO)
			return (err);
		if (is_valid)
			return (print_pass("'PWD' is already valid\n"), error(ERR_NO));
	}
	err = posix_getcwd(&pwd);
	err = handle_pwd_getcwd_error(err, &pwd);
	if (err.type != ERR_NO)
		return (err);
	err = var_set("PWD", pwd, false, false);
	if (err.type == ERR_NO)
		print_pass("'PWD' has been set to '%s'\n", pwd);
	free(pwd);
	return (err);
}
