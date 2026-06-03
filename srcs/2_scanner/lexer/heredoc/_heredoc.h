/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _heredoc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 16:10:57 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/03 15:18:32 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _HEREDOC_H
# define _HEREDOC_H

# include "libft.h"
# include "types.h"
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
	size_t			i;
	int				fd;
	t_heredoc_mode	mode;
	t_buff			delim;
	char			*line;
	char			*input;
	t_buff			content;
	bool			reached_here_end;
	bool			reached_end_of_input;
}	t_heredoc_body;

void	heredoc_body_init(t_heredoc_body *state);
void	heredoc_body_free(t_heredoc_body *state);
t_error	heredoc_body_load(t_heredoc_body *state, t_here_queue_item *item);

bool	heredoc_get_body(t_lexer *state, t_here_queue_item *item);

void	heredoc_advance(t_heredoc_body *body, size_t len);
bool	is_line_delimiter(t_lexer *state, t_heredoc_body *body);
t_error	heredoc_consume_line(t_lexer *state, t_heredoc_body *body);
t_error	heredoc_read_tty_line(t_lexer *state, t_heredoc_body *body);
t_error	heredoc_build_delimiter(t_lexer *state, t_heredoc_body *body);
	
#endif
