#include "variables.h"
# include "logs.h"		// DEBUG
# include <assert.h>	// DEBUG

#define IFS_NAME	"IFS"
#define IFS_VALUE	" \t\n\0"

static inline void	ifs_build_name(t_string *out)
{
	static char	name[] = IFS_NAME;
	size_t		len;

	assert(out != NULL);
	len = sizeof(IFS_NAME) - 1;
	string_take(out, name, len + 1, len);
}

static inline void	ifs_build_value(t_string *out)
{
	static char	value[] = IFS_VALUE;
	size_t		len;

	assert(out != NULL);
	len = sizeof(IFS_VALUE) - 1;
	string_take(out, value, len + 1, len);
}

/*
cf [2.5.3 Shell Variables](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_05_03)
- "The shell shall set IFS to <space><tab><newline> when it is invoked"
*/
t_error	var_set_ifs(void)
{
	t_error		err;
	t_string	name;
	t_string	value;

	ifs_build_name(&name);
	ifs_build_value(&value);
	err = var_set(&name, &value, false, false);
	if (err.type == ERR_NO)
		print_pass("'IFS'  initialized                     ' \\t\\n\\0'\n");
	return (err);
}
