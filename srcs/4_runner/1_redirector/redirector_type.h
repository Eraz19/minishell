#ifndef REDIRECTOR_TYPE_H
# define REDIRECTOR_TYPE_H

# include "fd_tracker_type.h"
# include "redirect_stack_type.h"

typedef struct s_redirector
{
	size_t			max_frame_count;
	t_redir_stack	stack;
	t_fd_tracker	tracker;
}	t_redirector;

#endif
