#include "sig.h"
#include "sig_priv.h"

static inline t_error	sig_error_if_ignored_on_entry(t_sig_id sig_id)
{
	t_sig_state	*sig_state;

	sig_state = &g_signals.state;
	if (sig_state->ignored_on_entry[sig_id] == true)
		return (error(ERR_SIG_WAS_IGNORED_ON_ENTRY));
	return (error(ERR_NO));
}

static inline t_error	sig_install_on_signal(
							t_sig_state *state,
							const char *sig_name,
							t_string *cmd)
{
	int				signo;
	t_sig_id		sig_id;
	t_sig_action	*action;
	t_error			err;

	err = sig_parse_name(sig_name, &signo, &sig_id);
	if (err.type)
		return (string_free(cmd), err);
	err = sig_error_if_ignored_on_entry(sig_id);
	if (err.type)
		return (string_free(cmd), err);
	action = &state->actions[sig_id];
	return (sig_install_trap(action, signo, cmd));
}

t_error	sig_set_trap(const char *sig_name, const char *cmd)
{
	t_sig_state	*sig_state;
	t_string	cmd_string;

	sig_state = &g_signals.state;
	if (!string_init(&cmd_string, 0, cmd, -1))
		return (error_sys());
	if (str_cmp("EXIT", sig_name) == 0 || str_cmp("0", sig_name) == 0)
	{
		string_free(&sig_state->exit_action.cmd);
		sig_state->exit_action.cmd = cmd_string;
		sig_state->exit_action.type = SIG_TRAPPED;
		return (error(ERR_NO));
	}
	return (sig_install_on_signal(sig_state, sig_name, &cmd_string));
}

t_error	sig_set_default(const char *sig_name)
{
	t_sig_state		*sig_state;
	int				signo;
	t_sig_id		sig_id;
	t_sig_action	*action;
	t_error			err;

	sig_state = &g_signals.state;
	err = sig_parse_name(sig_name, &signo, &sig_id);
	if (err.type)
		return (err);
	err = sig_error_if_ignored_on_entry(sig_id);
	if (err.type)
		return (err);
	action = &sig_state->actions[sig_id];
	return (sig_install_default(action, signo));
}

t_error	sig_set_ignore(const char *sig_name)
{
	t_sig_state		*sig_state;
	int				signo;
	t_sig_id		sig_id;
	t_sig_action	*action;
	t_error			err;

	sig_state = &g_signals.state;
	err = sig_parse_name(sig_name, &signo, &sig_id);
	if (err.type)
		return (err);
	action = &sig_state->actions[sig_id];
	return (sig_install_ignore(action, signo));
}
