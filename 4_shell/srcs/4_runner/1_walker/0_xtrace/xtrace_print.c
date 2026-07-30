#include "xtrace.h"
#include "xtrace_priv.h"
#include "options.h"

t_error	xtrace_print_one(const t_string *string)
{
	bool		trace_is_active;
	t_error		err;

	if (string->len == 0)
		return (error(ERR_NO));
	err = option_is_active(OPT_XTRACE, &trace_is_active);
	if (err.type || trace_is_active == false)
		return (err);
	err = xtrace_print_prefix();
	if (err.type)
		return (err);
	return (xtrace_print_content(string, 0, 1));
}

t_error	xtrace_print(const t_vector *expanded_strings)
{
	bool			trace_is_active;
	size_t			i;
	const t_string	*string;
	t_error			err;

	if (expanded_strings->len == 0)
		return (error(ERR_NO));
	err = option_is_active(OPT_XTRACE, &trace_is_active);
	if (err.type || trace_is_active == false)
		return (err);
	err = xtrace_print_prefix();
	i = 0;
	while (err.type == ERR_NO && i < expanded_strings->len)
	{
		string = &((t_string *)expanded_strings->data)[i];
		err = xtrace_print_content(string, i, expanded_strings->len);
		i++;
	}
	return (err);
}

t_error	xtrace_print_argv(const t_vector *argv)
{
	bool		trace_is_active;
	size_t		i;
	t_string	string;
	t_error		err;

	if (argv->len < 2)
		return (error(ERR_NO));
	err = option_is_active(OPT_XTRACE, &trace_is_active);
	if (err.type || trace_is_active == false)
		return (err);
	err = xtrace_print_prefix();
	i = 0;
	while (err.type == ERR_NO && i < argv->len - 1)
	{
		string.data = ((char **)argv->data)[i];
		string.len = str_len(string.data);
		err = xtrace_print_content(&string, i, argv->len - 1);
		i++;
	}
	return (err);
}
