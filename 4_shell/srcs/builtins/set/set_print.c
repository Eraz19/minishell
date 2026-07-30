#include <unistd.h>
#include "set_.h"
#include "options.h"
#include "posix_helpers.h"

t_error	set_print_one(char sign, const char *name, bool on)
{
	t_error		err;
	t_string	line;
	const char	*prefix;
	const char	*sufix;

	if (sign == '-')
	{
		sufix = "\ton\n";
		if (!on)
			sufix = "\toff\n";
		prefix = "";
	}
	else
	{
		prefix = "set -o ";
		if (!on)
			prefix = "set +o ";
		sufix = "\n";
	}
	if (!string_init(&line, 0, prefix, -1))
		return (error_sys());
	if (!string_append_n(&line, name, -1) || !string_append_n(&line, sufix, -1))
		return (err = error_sys(), string_free(&line), err);
	err = posix_write(STDOUT_FILENO, line.data, line.len);
	return (string_free(&line), err);
}

t_error	set_print_options(char sign)
{
	size_t		i;
	bool		on;
	t_option	bit;
	t_error		err;
	const char	*name;

	i = 0;
	while (set_named_option(i, &name, &bit))
	{
		err = option_is_active(bit, &on);
		if (err.type)
			return (err);
		err = set_print_one(sign, name, on);
		if (err.type)
			return (err);
		i++;
	}
	return (error(ERR_NO));
}
