#include "asm_stubs.h"
#include "variables.h"
#include <stdlib.h>
# include "logs.h"	// DEBUG
#include <assert.h>	// DEBUG

#define PPID_NAME	"PPID"

static inline void	ppid_build_name(t_string *out)
{
	static char	name[] = PPID_NAME;
	size_t		len;

	assert(out != NULL);
	len = sizeof(PPID_NAME) - 1;
	string_take(out, name, len + 1, (ssize_t)len);
}

/*
cf [2.5.3 Shell Variables](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_05_03)
	- Set by the shell to the decimal value of its parent process ID during initialization of the shell
*/
t_error	var_set_ppid(void)
{
	t_string	name;
	char		*value_str;
	t_string	value;
	t_error		err;

	ppid_build_name(&name);
	value_str = ft_pidtoa(ft_getppid());
	if (!value_str)
		return (error_sys());
	if (!string_init(&value, 0, value_str, -1))
		return (err = error_sys(), free(value_str), err);
	free(value_str);
	err = var_set(&name, &value, false, false);
	print_pass("'PPID' initialized                     '%s'\n", value.data);
	string_free(&value);
	return (err);
}
