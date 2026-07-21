#include "fd.h"
#include "params.h"
#include "redirect_stack.h"

// @ret ERR_NO / ERR_INTERNAL / ERR_LIBC
t_error	fd_use_new_frame()
{
	t_fd_manager	*fd_manager;
	t_redir_frame	frame;
	t_redir_frame	*frame_ptr;
	t_error			err;

	err = params_get_fd_manager(&fd_manager);
	if (err.type)
		return (err);
	if (fd_manager->stack.len < fd_manager->max_frame_count)
	{
		frame_ptr = ((t_redir_frame *)fd_manager->stack.data);
		frame_ptr += fd_manager->stack.len;
		frame_ptr->len = 0;
		fd_manager->stack.len++;
		return (error(ERR_NO));
	}
	redirect_frame_init(&frame);
	err = redirect_stack_push(&fd_manager->stack, &frame);
	if (err.type == ERR_NO)
		fd_manager->max_frame_count++;
	return (err);
}
