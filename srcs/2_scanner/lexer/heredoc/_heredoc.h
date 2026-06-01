/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _heredoc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 16:10:57 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/01 10:56:21 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _HEREDOC_H
# define _HEREDOC_H

# include "libft.h"
# include "./here_queue/_here_queue.h"

// Forwarded types
typedef struct s_lexer		t_lexer;

typedef enum e_heredoc_mode
{
	NORMAL,
	TAB_STRIP
}	t_heredoc_mode;

typedef struct s_here_queue_item
{
	t_file_path		path;
	t_heredoc_mode	mode;
	t_heredoc_delim	delim;
}	t_here_queue_item;

typedef struct s_heredoc_body
{
	int				fd;
	t_heredoc_mode	mode;
	t_buff			delim;
	t_buff			content;
	char			*last_line;
}	t_heredoc_body;

void	heredoc_body_init(t_heredoc_body *state);
void	heredoc_body_free(t_heredoc_body *state);
t_error	heredoc_body_load(t_heredoc_body *state, t_here_queue_item *item);

bool	heredoc_get_body(t_lexer *state, t_here_queue_item *item);

#endif
