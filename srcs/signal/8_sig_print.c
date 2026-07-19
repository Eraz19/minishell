#include "sig.h"
#include "posix_helpers.h"
#include <unistd.h>

static inline t_error	sig_print_one(t_sig_action *action, t_sig_id sig_id)
{
	t_string	out;
	t_error		err;

	err = sig_build_output(action, sig_id, &out);
	if (err.type)
		return (err);
	err = posix_write(STDOUT_FILENO, out.data, out.len);
	string_free(&out);
	return (err);
}

t_error	sig_print_conditions(char **conditions)
{
	size_t		i;
	t_sig_id	sig_id;
	int			signo;
	t_error		err;

	i = 0;
	while (conditions[i] != NULL)
	{
		if (str_cmp(conditions[i], "EXIT") == 0
			|| str_cmp(conditions[i], "0") == 0)
			err = sig_print_one(&g_signals.state.exit_action, SIG_EXIT_ID);
		else
		{
			err = sig_parse_name(conditions[i], &signo, &sig_id);
			if (err.type == ERR_NO)
				err = sig_print_one(&g_signals.state.actions[sig_id], sig_id);
		}
		if (err.type)
			return (err);
		i++;
	}
	return (error(ERR_NO));
}

// trap -p
t_error	sig_print_all(void)
{
	t_sig_id	sig_id;
	t_error		err;

	sig_id = 0;
	while (sig_id < SIG_ID_COUNT)
	{
		err = sig_print_one(&g_signals.state.actions[sig_id], sig_id);
		if (err.type)
			return (err);
		sig_id++;
	}
	return (sig_print_one(&g_signals.state.exit_action, SIG_EXIT_ID));
}

// trap
t_error	sig_print_all_except_default(void)
{
	t_sig_id		sig_id;
	t_sig_action	*action;
	t_error			err;

	sig_id = 0;
	while (sig_id < SIG_ID_COUNT)
	{
		action = &g_signals.state.actions[sig_id];
		if (action->type != SIG_DEFAULT)
		{
			err = sig_print_one(action, sig_id);
			if (err.type)
				return (err);
		}
		sig_id++;
	}
	if (g_signals.state.exit_action.type != SIG_DEFAULT)
		return (sig_print_one(&g_signals.state.exit_action, SIG_EXIT_ID));
	return (error(ERR_NO));
}
