/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __heredoc_body.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 18:41:25 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/05 19:33:34 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __HEREDOC_BODY_H
# define __HEREDOC_BODY_H

# include "__heredoc.h"

typedef struct s_heredoc_body_load_args
{
	size_t				*i;
	t_here_queue_item	*item;
	char				*input;
	bool				is_tty;
}	t_heredoc_body_load_args;

typedef struct s_heredoc_body_no_tty
{
	size_t	*i;
}	t_heredoc_body_no_tty;

typedef struct s_heredoc_body
{
	t_error					err;
	t_heredoc_mode			mode;
	t_file_path				path;
	t_heredoc_body_no_tty	no_tty;
	bool					is_tty;
	char					*input;
	char					*line;
	char					*delim;
	t_buff					content;
}	t_heredoc_body;

void	heredoc_body_init(t_heredoc_body *state);
void	heredoc_body_free(t_heredoc_body *state);
t_error	heredoc_body_load(t_heredoc_body *state, t_heredoc_body_load_args args);

bool	is_line_delimiter(t_heredoc_body *state);
t_error	heredoc_body_add_line(t_heredoc_body *state);
t_error	heredoc_body_line(t_heredoc_body *state, char *EOL, size_t *i);

t_error	heredoc_body_content_tty(t_heredoc_body *state);
t_error	heredoc_body_save_content(t_heredoc_body *state);
t_error	heredoc_body_content_no_tty(t_heredoc_body *state);

#endif
