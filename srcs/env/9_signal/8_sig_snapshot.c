#include "sig_priv.h"
#include "shell.h"

void	sig_snapshot(void)
{
	t_sig_state	*state;
	t_sig_state	*snapshot;
	size_t		n;
	t_sig_id	i;

	state = &g_signals.state;
	snapshot = &g_signals.snapshot;
	n = SIG_ID_COUNT * sizeof(*state->ignored_on_entry);
	ft_memcpy(snapshot->ignored_on_entry, state->ignored_on_entry, n);
	i = 0;
	while (i < SIG_ID_COUNT)
	{
		snapshot->actions[i].type = state->actions[i].type;
		string_free(&snapshot->actions[i].cmd);
		string_take_string(&snapshot->actions[i].cmd, &state->actions[i].cmd);
		i++;
	}
	snapshot->exit_action.type = state->exit_action.type;
	string_free(&snapshot->exit_action.cmd);
	string_take_string(&snapshot->exit_action.cmd,&state->exit_action.cmd);
	snapshot->is_executing_exit_action = false;
}

t_error	sig_get_printable_state(t_sig_state **out_sig_state_ptr)
{
	bool	is_subshell;
	t_error	err;

	err = shell_is_subshell(&is_subshell);
	if (err.type)
		return (err);
	if (!is_subshell || g_signals.trap_with_operand_has_been_executed)
		*out_sig_state_ptr = &g_signals.state;
	else
		*out_sig_state_ptr = &g_signals.snapshot;
	return (err);
}
