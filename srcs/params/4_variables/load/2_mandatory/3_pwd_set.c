#include "variables.h"
#include "var_load_mandatory_priv.h"
#include "posix_helpers.h"
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/param.h>
#include <sys/stat.h>
# include "logs.h"		// DEBUG
# include <assert.h>	// DEBUG

#define PWD_NAME	"PWD"

static inline void	pwd_build_name(t_string *out)
{
	static char	name[] = PWD_NAME;
	size_t		len;

	assert(out != NULL);
	len = sizeof(PWD_NAME);
	string_take(out, name, len + 1, len);
}

// ERR_SHELL_NOT_FOUND / ERR_VAR_INVALID_NAME / ERR_VAR_READ_ONLY /
// ERR_SIZE_MAX_REACHED / ERR_LIBC.
static inline t_error	set_default_pwd(t_string *name, bool export)
{
	t_string	value;
	t_error		err;

	assert(name != NULL);
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
	if (err.type == ERR_NO)
		print_pass("'PWD' has been set to '%s'\n", value.data);
	string_free(&value);
	return (err);
}

// ERR_SHELL_NOT_FOUND / ERR_VAR_INVALID_NAME / ERR_VAR_READ_ONLY / ERR_LIBC
static inline t_error	process_existing_pwd(t_string *name, t_string *value)
{
	bool	is_valid;
	t_error	err;

	assert(name != NULL);
	assert(value != NULL);
	err = var_pwd_is_valid(value->data, &is_valid);
	if (err.type)
		return (err);
	else if (is_valid)
		return (print_pass("'PWD' is already valid\n"), error(ERR_NO));
	return (set_default_pwd(name, true));
}

/*
cf [2.5.3 Shell Variables](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_05_03)
	a) "If a value for PWD is passed to the shell in the environment when it is executed, the value is an absolute pathname of the current working directory [...optional...] and the value does not contain any components that are dot or dot-dot, then the shell shall set PWD to the value from the environment"
	b) "Otherwise, the sh utility sets PWD to the pathname that would be output by pwd -P" (= getcwd())
*/
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
