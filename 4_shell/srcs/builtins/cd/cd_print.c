#include <unistd.h>
#include "env.h"
#include "posix_helpers.h"

t_error	cd_print_new(void)
{
	t_string	pwd;
	t_error		err;

	err = env_get_from_const("PWD", &pwd);
	if (err.type)
		return (err);
	if (!string_append_n(&pwd, "\n", 1))
		return (string_free(&pwd), error_sys());
	err = posix_write(STDOUT_FILENO, pwd.data, pwd.len);
	return (string_free(&pwd), err);
}
