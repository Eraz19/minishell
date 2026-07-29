#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <readline/readline.h>
#include "sig.h"
#include "logs.h"	// DEBUG
#include "options.h"
#include "posix_helpers.h"
#include "reader_interactive_priv.h"

static t_error	ensure_reader_stdin_is_blocking(void)
{
	int			enabled;
	bool		is_fifo;
	struct stat	stat_buff;
	bool		is_a_terminal;
	
	is_a_terminal = isatty(STDIN_FILENO);
	if (!is_a_terminal)
	{
		if (fstat(STDIN_FILENO, &stat_buff) != 0)
			return (error_print(error_sys(), "unable to check if stdin is FIFO", NULL, NULL));
		is_fifo = S_ISFIFO(stat_buff.st_mode);
		if (!is_fifo)
		{
			print_pass("stdin is not a fifo: not set to blocking mode\n");
			return (error(ERR_NO));
		}
	}
	enabled = 0;
	if (ioctl(STDIN_FILENO, FIONBIO, &enabled) == -1)
		return (error_print(error_sys(), "Unable to set stdin to blocking mode", NULL, NULL));
	print_pass("stdin set to blocking mode\n");
	return (error(ERR_NO));
}

static t_error	read_line_secured(const char *prompt, char **out, bool *retry)
{
	t_error	err;

	*retry = false;
	err = sig_process();
	if (err.type)
		return (err);
	err = ensure_reader_stdin_is_blocking();
	if (err.type)
		return (err);
	*out = readline(prompt);
	err = handle_reader_signals(retry);
	if (err.type)
		return (err);
	return (sig_process());
}

static t_error	on_max_retry_reached(size_t counter, size_t max_retry)
{
	if (counter > max_retry && max_retry > 0)
		return (err_infinite_loop());
	else if (counter > max_retry)
		return (error(ERR_VEOF));
	return (error(ERR_NO));
}

static t_error	read_line_until(const char *prompt, char **out, size_t max_retry)
{
	t_error	err;
	bool	retry;
	size_t	counter;
	bool	ignore_eof;

	counter = 0;
	fprintf(stderr, CYAN "####################### IN #######################\n" NC);
	while (++counter)
	{
		err = read_line_secured(prompt, out, &retry);
		if (err.type || *out != NULL)
			break ;
		if (retry == true)
			continue ;
		err = option_is_active(OPT_IGNOREEOF, &ignore_eof);
		if (err.type == ERR_NO && ignore_eof == false)
			err = error(ERR_VEOF);
		if (err.type == ERR_NO && isatty(STDIN_FILENO) != 1)
			err = posix_write(STDOUT_FILENO, "\n", 1);
		if (err.type || counter > max_retry)
		{
			err = on_max_retry_reached(counter, max_retry);
			break ;
		}
	}
	fprintf(stderr, CYAN "##################################################\n" NC);
	return (err);
}

t_error	read_line(t_string *out, const char *prompt, size_t max_retry)
{
	t_error	err;
	char	*input;

	if (prompt == NULL)
		prompt = "";
	err = read_line_until(prompt, &input, max_retry);
	if (err.type)
		return (err);
	if (!string_init(out, 0, input, -1))
		return (free(input), error_sys());
	free(input);
	if (!string_append_n(out, "\n", 1))
		return (err = error_sys(), string_free(out), err);
	return (error(ERR_NO));
}
