#include "error.h"
#include "redirect_stack.h"
#include "posix_helpers.h"

static inline void	redirect_stack_close_frame_backups(const t_redir_frame *frame)
{
	t_redir_backup	*backup;
	size_t			i;
	t_error			err;

	i = 0;
	while (i < frame->len)
	{
		err = redirect_frame_get_backup(frame, i, &backup);
		if (err.type)
			break ;
		if (backup->backup_fd >= 0)
			(void)posix_close_if_open(backup->backup_fd);
		i++;
	}
}

void	redirect_stack_close_backups(const t_redir_stack *redir_stack)
{
	t_redir_frame	*frame;
	size_t			i;
	t_error			err;

	i = 0;
	while (i < redir_stack->len)
	{
		err = redirect_stack_get_frame(redir_stack, i, &frame);
		if (err.type)
			break ;
		redirect_stack_close_frame_backups(frame);
		i++;
	}
}
