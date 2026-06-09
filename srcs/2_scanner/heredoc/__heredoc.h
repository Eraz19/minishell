/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __heredoc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 16:10:57 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/05 20:29:22 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __HEREDOC_H
# define __HEREDOC_H

# include "libft.h"
# include "types.h"
# include "__here_queue.h"

typedef struct s_heredoc
{
	size_t			*i;
	t_error			err;
	t_here_queue	queue;
	char			*input;
	bool			is_tty;
}	t_heredoc;

void	heredoc_init(t_heredoc *state);
void	heredoc_free(t_heredoc *state);
void	heredoc_reset(t_heredoc *state);
void	heredoc_load(t_heredoc *state, bool is_tty);
	
#endif
