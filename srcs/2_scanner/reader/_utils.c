#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include "libft.h"
#include "shell.h"
#include "reader_.h"
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <unistd.h>
# include "logs.h"	// DEBUG

// ERR_NO / ERR_LIBC
static inline t_error	reader_set_stdin_to_blocking(void)
{
	int			enabled;
	struct stat	stat_buff;
	bool		is_a_terminal;
	bool		is_fifo;
	
	is_a_terminal = isatty(STDIN_FILENO);
	if (!is_a_terminal)
	{
		if (fstat(STDIN_FILENO, &stat_buff) != 0)
			return (error_print(error_sys(),
					"unable to check if stdin is FIFO", NULL, NULL));
		is_fifo = S_ISFIFO(stat_buff.st_mode);
		if (!is_fifo)
		{
			print_pass("stdin is not a fifo: not set to blocking mode\n");
			return (error(ERR_NO));
		}
	}
	enabled = 0;
	if (ioctl(STDIN_FILENO, FIONBIO, &enabled) == -1)
		return (error_print(error_sys(),
				"Unable to set stdin to blocking mode", NULL, NULL));
	print_pass("stdin set to blocking mode\n");
	return (error(ERR_NO));
}

t_error	readline_(t_string *res, const char *prompt)
{
	t_error	err;
	char	*input;

	if (prompt == NULL)
		prompt = "";
	err = reader_set_stdin_to_blocking();
	if (err.type)
		return (err);
	fprintf(stderr, CYAN "####################### IN #######################\n" NC);
	input = readline(prompt);
	while (input == NULL)
	{
		err = shell_should_exit_on_veof();
		if (err.type)
			return (err);
		err = reader_set_stdin_to_blocking();
		if (err.type)
			return (err);
		input = readline(prompt);
	}
	fprintf(stderr, CYAN "##################################################\n" NC);
	if (!string_init(res, 0, input, -1))
		return (free(input), error_sys());
	free(input);
	if (!string_append_n(res, "\n", 1))
		return (err = error_sys(), string_free(res), err);
	return (error(ERR_NO));
}

t_error	reader_read_error(t_error err, const char *source)
{
	err = error_print(err, "scanner", source, "read error", NULL, NULL);
	err.type = ERR_POSIX_READ;
	return (err);
}
