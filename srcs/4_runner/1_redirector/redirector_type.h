#ifndef REDIRECTOR_TYPE_H
# define REDIRECTOR_TYPE_H

# include "fd_tracker_type.h"
# include "redirect_stack_type.h"

/**
 * @struct s_redirector
 * @brief Runtime state used to apply and restore shell redirections.
 *
 * @var s_redirector::max_frame_count Maximum number of stack frames allocated
 *                                    so far for temporary redirections.
 * @var s_redirector::stack Redirection backup stack managed by the
 *                          redirect_stack submodule.
 * @var s_redirector::tracker File-descriptor tracker managed by the
 *                            fd_tracker submodule.
 */
typedef struct s_redirector
{
	/** @brief Maximum number of stack frames allocated so far. */
	size_t			max_frame_count;
	/** @brief Redirection backup stack managed by the redirect_stack submodule. */
	t_redir_stack	stack;
	/** @brief File-descriptor tracker managed by the fd_tracker submodule. */
	t_fd_tracker	tracker;
}	t_redirector;

#endif
