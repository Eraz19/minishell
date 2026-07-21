#include "runner_priv.h"
#include "parser.h"
#include "params.h"
# include "logs.h"	// DEBUG
# include <stdio.h>	// DEBUG

static inline void	runner_handle_eof(t_error *err, bool interactive)
{
	if (interactive == true)
		err->type = ERR_NO;
}

static inline void	runner_handle_syntax_errors(
						t_runner *runner,
						t_error *err,
						bool interactive)
{
	*err = error_print(*err, NULL, NULL);
	(void)params_set_last_status((int)err->type);
	if (interactive == true)
	{
		parser_clear(&runner->parser);
		err->type = ERR_NO;
	}
}

static inline void	runner_handle_read_errors(t_error *err)
{
	*err = error_print(*err, NULL, NULL);
	(void)params_set_last_status((int)err->type);
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

void	runner_handle_error(t_runner *runner, t_error *err)
{
	bool	interactive;
	t_error	option_err;

	fprintf(stderr, "[RUNNER] handling error %i (%s)\n", (int)err->type, error_to_string(*err));
	option_err = option_is_active(OPT_INTERACTIVE, &interactive);
	if (option_err.type)
	{
		*err = option_err;
		return ;
	}
	if (err->type == ERR_NOT_IMPLEMENTED)
	{
		(void)error_print(*err, NULL, NULL);
		err->type = ERR_NO;
	}
	if (err->type == ERR_EOF)
		runner_handle_eof(err, interactive);
	else if (err->type == ERR_POSIX_SYNTAX)
		runner_handle_syntax_errors(runner, err, interactive);
	else if (err->type == ERR_POSIX_READ)
		runner_handle_read_errors(err);
	else if (err->type >= ERR_CONTINUE && err->type <= ERR_RETURN)
	{
		*err = error_print(*err, NULL, NULL);
		if (interactive == true)
			err->type = ERR_NO;
	}
	runner_handle_bad_errors(err, interactive);
	if (err->type && err->type != ERR_EXIT && err->type != ERR_EXIT_WITH_CURRENT_STATUS)
		*err = error_print(*err, NULL, NULL);
	fprintf(stderr, "[RUNNER] => final error %i (%s)\n", (int)err->type, error_to_string(*err));
	fprintf(stderr, "--------------------------------------------------\n");
}
