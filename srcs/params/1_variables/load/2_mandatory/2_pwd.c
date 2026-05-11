#include "variables.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/param.h>
#include <sys/stat.h>
# include <stdio.h>	// TODO: tmp debug

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
// Errors can be ERR_LIBC.
static t_error	pwd_is_the_current_working_dir(const char *pwd, bool *res)
{
	struct stat	current;
	struct stat	from_pwd;

	if (stat(".", &current) == -1)
		return (ERR_LIBC);
	if (stat(pwd, &from_pwd) == -1)
		return (ERR_LIBC);
	if (current.st_dev != from_pwd.st_dev)
		return (*res = false, ERR_NO);
	if (current.st_ino != from_pwd.st_ino)
		return (*res = false, ERR_NO);
	return (*res = true, ERR_NO);
}

/*
cf [2.5.3 Shell Variables](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_05_03)
	- "the value is an absolute pathname"
	- "the value does not contain any components that are dot or dot-dot"
	- "the value is [...] the current working directory"
*/
// Errors can be ERR_LIBC.
static t_error	var_pwd_is_valid(const char *pwd, bool *res)
{
	*res = false;
	if (pwd[0] != '/')
		return (ERR_NO);
	if (!pwd_has_no_dot_components(pwd))
		return (ERR_NO);
	return (pwd_is_the_current_working_dir(pwd, res));
}

/*
cf [2.5.3 Shell Variables](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_05_03)
	a) "If a value for PWD is passed to the shell in the environment when it is executed, the value is an absolute pathname of the current working directory [...optional...] and the value does not contain any components that are dot or dot-dot, then the shell shall set PWD to the value from the environment"
	b) "Otherwise, the sh utility sets PWD to the pathname that would be output by pwd -P" (= getcwd())
*/
t_error	var_set_pwd(t_var_list *variables)
{
	char	*pwd;
	t_error	error;
	bool	is_valid;

	error = var_get(variables, "PWD", &pwd);
	if (error != ERR_NO && error != ERR_VAR_NOT_FOUND)
		return (error);
	if (error == ERR_NO)
	{
		error = var_pwd_is_valid(pwd, &is_valid);
		free(pwd);
		if (error != ERR_NO)
			return (error);
		if (is_valid)
			return (printf("-> 'PWD' is already valid\n"), ERR_NO);
	}
	pwd = getcwd(NULL, MAXPATHLEN);
	if (!pwd)
		return (ERR_LIBC);
	error = var_set(variables, "PWD", pwd);
	if (error == ERR_NO)
		printf("-> 'PWD' has been set to '%s'\n", pwd);
	free(pwd);
	return (error);
}
