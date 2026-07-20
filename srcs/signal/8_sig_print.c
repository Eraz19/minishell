#include "sig.h"
#include "sig_priv.h"
#include "posix_helpers.h"
#include <unistd.h>

// @ret ERR_NO / ERR_INTERNAL / ERR_POSIX_WRITE / ERR_LIBC
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

static inline t_error	sig_print_err_and_absorb(
							t_error err,
							const char *builtin_name,
							const char *arg,
							int *exit_status)
{
	*exit_status = (int)err.type;
	(void)error_print(err, builtin_name, arg, NULL, NULL);
	return (error(ERR_NO));
}

// @ret ERR_NO / ERR_INTERNAL / ERR_POSIX_WRITE / ERR_LIBC
t_error	sig_print_conditions(
			const char *builtin_name,
			char **conditions,
			int *exit_status)
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
			else
				err = sig_print_err_and_absorb(
						err, builtin_name, conditions[i], exit_status);
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
