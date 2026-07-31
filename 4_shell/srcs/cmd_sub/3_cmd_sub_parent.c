#include "cmd_sub_priv.h"
#include "posix_helpers.h"
#ifdef DEBUG_CMD_SUB
# include "logs.h"	// DEBUG
#endif

static inline t_error	cmd_sub_parent_read_and_close(
							int pipe_fds[2],
							t_string *out_string)
{
	t_error	err;

	err = posix_close_if_open(pipe_fds[1]);
	if (err.type)
		return (error_priorize(err, posix_close_if_open(pipe_fds[0])));
	err = posix_read_all(pipe_fds[0], out_string);
	if (err.type)
		return (error_priorize(err, posix_close_if_open(pipe_fds[0])));
	return (posix_close_if_open(pipe_fds[0]));
}

static inline void	cmd_sub_parent_trim(t_string *string)
{
	while (string->len > 0 && string->data[string->len - 1] == '\n')
		string->len--;
	string->data[string->len] = '\0';
}

t_error	cmd_sub_parent(
			int pipe_fds[2],
			pid_t child_pid,
			t_string *out_string,
			int *out_exit_status)
{
	t_error	err;

	err = cmd_sub_parent_read_and_close(pipe_fds, out_string);
	err = error_priorize(err, posix_wait_and_retry(child_pid, out_exit_status));
	if (err.type)
		return (err);
	cmd_sub_parent_trim(out_string);
#ifdef DEBUG_CMD_SUB
	fprintf(stderr, YELLOW "##################################################\n" NC);
#endif
	return (err);
}
