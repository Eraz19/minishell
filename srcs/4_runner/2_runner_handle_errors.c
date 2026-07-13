#include "runner_priv.h"
#include "scanner.h"
#include "builder.h"
#include "shell.h"
# include "logs.h"	// DEBUG
# include <stdio.h>	// DEBUG

static inline void	runner_handle_eof(t_error *err, bool interactive)
{
	if (interactive == true)
		err->type = ERR_NO;
}

static inline void	runner_handle_syntax_errors(
						t_shell *shell,
						t_error *err,
						bool interactive)
{
	*err = error_print(*err, NULL, NULL);
	params_set_last_status_in(&shell->params, (int)err->type);
	if (interactive == true)
	{
		scanner_reset(&shell->scanner);
		builder_clear(&shell->builder);
		err->type = ERR_NO;
	}
}

static inline void	runner_handle_read_errors(t_shell *shell, t_error *err)
{
	*err = error_print(*err, NULL, NULL);
	params_set_last_status_in(&shell->params, (int)err->type);
}

static inline void	runner_handle_bad_errors(t_error *err, bool interactive)
{
	if (err->type == ERR_NO || err->type == ERR_POSIX_READ)
		return ;
	if (err->type >= ERR_VEOF && (err->type <= ERR_LIBC || interactive == false))
		return ;
	fprintf(stderr, "%s[RUNNER] error should have been requalified : %i (%s)%s\n",
		RED, (int)err->type, error_to_string(*err), NC);
}

void	runner_handle_errors(t_shell *shell, t_error *err)
{
	bool	interactive;

	fprintf(stderr, "[RUNNER] handling error %i (%s)\n", (int)err->type, error_to_string(*err));
	interactive = option_is_active_in(shell->params.options, OPT_INTERACTIVE);
	if (err->type == ERR_EOF)
		runner_handle_eof(err, interactive);
	else if (err->type == ERR_POSIX_SYNTAX)
		runner_handle_syntax_errors(shell, err, interactive);
	else if (err->type == ERR_POSIX_READ)
		runner_handle_read_errors(shell, err);
	else if (err->type >= ERR_CONTINUE && err->type <= ERR_RETURN)
	{
		*err = error_print(*err, NULL, NULL);
		if (interactive == true)
			err->type = ERR_NO;
	}
	runner_handle_bad_errors(err, interactive);
	if (err->type)
		*err = error_print(*err, NULL, NULL);
	fprintf(stderr, "[RUNNER] => final error is %i (%s)\n", (int)err->type, error_to_string(*err));
}
