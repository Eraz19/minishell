#include "cmd.h"
#include "sig.h"
#include "options.h"
# include "debug.h"	// DEBUG

static inline t_error	cmd_qualify_error(t_cmd *cmd, t_error err, int *status)
{
	bool	interactive;
	int		signo;
	t_error	option_err;

	(void)error_print(err, NULL, NULL);
	if (err.type == ERR_INTERRUPTED)
	{
		if (sig_has_pending_trap(&signo))
			*status = ERR_POSIX_SIGNAL_BASE_CODE + signo;
		err.type = ERR_NO;
	}
	else if (err.type == ERR_REDIRECTION && cmd->entry.type != CMD_SPECIAL_BUILTIN)
		err.type = ERR_NO;
	else if (err.type == ERR_POSIX_CMD_NOT_FOUND || err.type == ERR_POSIX_CMD_NOT_EXECUTABLE)
		err.type = ERR_NO;
	else if (err.type > ERR_POSIX_SYNTAX && err.type < ERR_POSIX_READ)
	{
		option_err = option_is_active(OPT_INTERACTIVE, &interactive);
		if (option_err.type)
			err = error_priorize(err, option_err);
		else if (interactive == true)
			err.type = ERR_NO;
	}
	return (err);
}

t_error	cmd_finalize(t_cmd *cmd, t_error err, int *exit_status)
{
	/* ---------- DEBUG (START) ---------- */
	int		initial_exit_status;
	t_error	initial_error;

	initial_exit_status = *exit_status;
	initial_error = err;
	/* ---------- DEBUG (END) ---------- */
	if (*exit_status < 0)
		*exit_status = (int)err.type;
	if (err.type && error_is_flow_control(err) == false)
		err = cmd_qualify_error(cmd, err, exit_status);
	/* ---------- DEBUG (START) ---------- */
	fprintf(stderr, MAGENTA "##################################################\n" NC);
	fprintf(stderr, "[CMD   ] type        => %s\n", cmd_type_to_string(cmd->entry.type));
	fprintf(stderr, "[CMD   ] exit_status => %i => %i\n", initial_exit_status, *exit_status);
	fprintf(stderr, "[CMD   ] error       = %s => %s\n", error_to_string(initial_error), error_to_string(err));
	/* ---------- DEBUG (END) ---------- */
	sig_process();
	return (err);
}

t_error	cmd_finalize_and_free(t_cmd *cmd, t_error err, int *exit_status)
{
	cmd_finalize(cmd, err, exit_status);
	cmd_free(cmd);
	return (err);
}
