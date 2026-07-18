#include <fcntl.h>
#include "history_file_.h"
#include "posix_helpers.h"
# include "logs.h"	// DEBUG

t_error	history_file_read(t_history_file *state)
{
	int		fd;
	int		oflag;
	t_error	err;

	if (state->path.len == 0)
		return (state->err);
	oflag = O_CREAT | O_RDONLY;
	state->err = posix_open_with_mode(state->path.data, oflag, 0644, &fd);
	if (state->err.type)
	{
		(void)error_print(state->err,
			"history", "unable to open history file",
			"persistent history disabled", NULL, "%s", state->path.data);
		return (state->err = error(ERR_NO));
	}
	err = posix_read_all(fd, &state->content);
	if (err.type)
	{
		(void)error_print(error_sys(),
			"history", "unable to read history file",
			"persistent history disabled", NULL, "%s", state->path.data);
		string_free(&state->content);
	}
	return (state->err = posix_close_if_open(fd));
}

t_error	history_file_write(t_history_file *state)
{
	int	fd;
	int	oflag;

	if (state->path.len == 0)														// DEBUG
		print_warn("[HISTORY] History disabled: %sskipping save%s\n", YELLOW, NC);	// DEBUG
	else if (state->content.len == 0)												// DEBUG
		print_warn("[HISTORY] History empty: %sskipping save%s\n", YELLOW, NC);		// DEBUG
	if (state->path.len == 0 || state->content.len == 0)
		return (state->err);
	oflag = O_WRONLY | O_APPEND;
	state->err = posix_open_with_mode(state->path.data, oflag, 0644, &fd);
	if (state->err.type)
	{
		(void)error_print(state->err,
			"history", "unable to open history file",
			"persistent history disabled", NULL, "%s", state->path.data);
		return (state->err = error(ERR_NO));
	}
	state->err = posix_write(fd, state->content.data, state->content.len);
	if (state->err.type == ERR_INTERRUPTED)
		return (posix_close_if_open(fd), state->err);
	if (state->err.type)
	{
		(void)error_print(state->err,
			"history", "unable to write to history file",
			"persistent history disabled", NULL, "%s", state->path.data);
		return (posix_close_if_open(fd), state->err = error(ERR_NO));
	}
	print_pass("[HISTORY] History saved to = %s%s%s\n", BLUE, state->path.data, NC);	// DEBUG
	return (state->err = posix_close_if_open(fd));
}
