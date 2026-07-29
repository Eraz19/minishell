#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include "sig.h"
#include "history.h"
#include "options.h"
#include "reader_priv.h"
#include "posix_helpers.h"
#include "reader_interactive.h"

int	reader_readline_hook(FILE *stream)
{
	unsigned char	out;
	ssize_t			read_count;

	(void)stream;
	while (true)
	{
		read_count = read(STDIN_FILENO, &out, 1);
		if (read_count == 1)
			return ((int)out);
		else if (read_count == 0)
			return (EOF);
		else if (errno == EINTR)
		{
			if (sig_int_is_pending())
				return (EOF);
			continue ;
		}
		return (EOF);
	}
}

t_error	reader_read_PS1(t_string *out)
{
	t_error	err;
	bool	is_interactive;
	bool	is_reading_stdin;

	err = option_is_active(OPT_STDIN_INPUT, &is_reading_stdin);
	if (err.type)
		return (err);
	err = option_is_active(OPT_INTERACTIVE, &is_interactive);
	if (err.type)
		return (err);
	if (!is_interactive || !is_reading_stdin)
		return (error(ERR_VEOF));
	err = history_save_entry();
	if (err.type)
		return (err);
	err = read_interactive(out, PROMPT_PS1, MAX_RETRY_PS1);
	if (err.type)
		return (err);
	err = history_append_to_entry(out);
	if (err.type)
		return (string_free(out), err);
	return (err);
}

t_error	reader_read_PS2(t_string *out)
{
	t_error		err;
	t_string	continuation;
	bool		is_interactive;
	bool		is_reading_stdin;

	err = option_is_active(OPT_STDIN_INPUT, &is_reading_stdin);
	if (err.type)
		return (err);
	err = option_is_active(OPT_INTERACTIVE, &is_interactive);
	if (err.type)
		return (err);
	if (!is_interactive || !is_reading_stdin)
		return (error(ERR_POSIX_SYNTAX));
	err = read_interactive(&continuation, PROMPT_PS2, MAX_RETRY_PS2);
	if (err.type)
		return (err);
	err = history_append_to_entry(&continuation);
	if (err.type)
		return (string_free(&continuation), err);
	if (!string_append(out, &continuation))
		err = error_sys();
	return (string_free(&continuation), err);
}

t_error	reader_read_file(t_string * out, const char *path)
{
	return (read_file(out, path));
}

t_error	reader_read_stdin(t_string *out)
{
	t_error	err;

	err = posix_read_all(STDIN_FILENO, out);
	if (err.type == ERR_LIBC)
		return (on_read_error(err, "stdin"));
	return (err);
}
