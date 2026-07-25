#include "xtrace_priv.h"
#include "params.h"
#include "posix_helpers.h"
#include <unistd.h>

static inline t_error	xtrace_get_prefix(t_string *out_prefix)
{
	t_error	err;

	err = params_get_from_const("PS4", out_prefix);
	if (err.type == ERR_VAR_NOT_FOUND)
	{
		if (!string_init(out_prefix, 1, "", 0))
			return (error_sys());
		return (error(ERR_NO));
	}
	return (err);
}

t_error	xtrace_print_prefix(void)
{
	t_string	prefix;
	t_error		err;

	err = xtrace_get_prefix(&prefix);
	if (err.type)
		return (err);
	err = posix_write(STDERR_FILENO, prefix.data, prefix.len);
	string_free(&prefix);
	return (err);
}
