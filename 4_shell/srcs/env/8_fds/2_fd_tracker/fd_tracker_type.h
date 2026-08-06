/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_tracker_type.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:12:42 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 14:12:43 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FD_TRACKER_TYPE_H
# define FD_TRACKER_TYPE_H

# include "redirect_stack_type.h"
# include <stddef.h>
# include <stdbool.h>

typedef struct s_tracked_fd
{
	size_t	user_count;			// number of user redirection touching this fd
	bool	is_used_by_shell;	// if true, fd is used by the shell as backup
	size_t	frame_index;		// the index of the target frame in the stack
	size_t	backup_index;		// the index of the target backup in the frame
}	t_tracked_fd;

typedef struct s_fd_tracker
{
	t_redir_stack	*stack;				// borrowed from t_redirector
	t_tracked_fd	*data;				// access it with tracker[fd]
	size_t			cap;				// capacity of data array
	size_t			next_available;		// next available fd
}	t_fd_tracker;

#endif
