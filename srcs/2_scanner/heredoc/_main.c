/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 10:37:07 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/05 20:31:07 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "ft_time.h"
#include "__lexer.h"
#include "__heredoc_body.h"

static t_error	heredoc_tty(t_heredoc *state, t_here_queue_item *item)
{
	t_heredoc_body				body;
	t_heredoc_body_load_args	load_args;

	heredoc_body_init(&body);
	load_args = (t_heredoc_body_load_args){
		.i = NULL,
		.item = item,
		.input = NULL,
		.is_tty = true};
	if (heredoc_body_load(&body, load_args))
		return (heredoc_body_free(&body), state->err = body.err, state->err);
	if (heredoc_body_content_tty(&body))
		return (heredoc_body_free(&body), state->err = body.err, state->err);
	if (heredoc_body_save_content(&body))
		return (heredoc_body_free(&body), state->err = body.err, state->err);
	return (heredoc_body_free(&body), state->err);
}

static t_error	heredoc_no_tty(t_heredoc *state, t_here_queue_item *item)
{
	t_heredoc_body				body;
	t_heredoc_body_load_args	load_args;

	heredoc_body_init(&body);
	load_args = (t_heredoc_body_load_args){
		.item = item,
		.i = state->i,
		.is_tty = false,
		.input = state->input};
	if (heredoc_body_load(&body, load_args))
		return (heredoc_body_free(&body), state->err = body.err, state->err);
	if (heredoc_body_content_no_tty(&body))
		return (heredoc_body_free(&body), state->err = body.err, state->err);
	if (heredoc_body_save_content(&body))
		return (heredoc_body_free(&body), state->err = body.err, state->err);
	return (heredoc_body_free(&body), state->err);
}

static t_error	heredoc_generate_file_id(char **id)
{
	time_t	current_time;

	current_time = get_now_unix_seconds();
	if (current_time == -1)
		return (ERR_LIBC);
	*id = ft_ltoa(current_time);
	if (*id == NULL)
		return (ERR_LIBC);
	return (ERR_NO);
}

t_error	heredoc_create_tmp_file(t_heredoc *state, t_file_path *file_path)
{
	int		fd;
	char	*id;
	t_buff	path;
	char	*path_;

	if (!buff_init(&path, 0, "/tmp/minishell_heredoc_", 23))
		return (state->err = ERR_LIBC, state->err);
	state->err = heredoc_generate_file_id(&id);
	if (state->err)
		return (buff_free(&path), state->err);
	if (!buff_append(&path, id, (long)str_len(id)))
		return (free(id), buff_free(&path), state->err = ERR_LIBC, state->err);
	free(id);
	path_ = buff_get_string(&path);
	if (path_ == NULL)
		return (buff_free(&path), state->err = ERR_LIBC, state->err);
	fd = open(path_, O_CREAT, 0644);
	if (fd != -1)
		return (close(fd), buff_free(&path), *file_path = path_, state->err);
	return (buff_free(&path), free(path_), state->err = ERR_LIBC, state->err);
}

t_error	heredoc_consume(t_heredoc *state, t_lexer *lexer)
{
	size_t				i;
	t_here_queue_item	item;

	i = 0;
	state->i = &lexer->i;
	state->input = lexer->input;
	while (i < state->queue.len)
	{
		state->err = here_queue_get(&state->queue, &item, i);
		if (state->err)
			return (state->err);
		if (state->is_tty && heredoc_tty(state, &item))
			return (state->err);
		else if (!state->is_tty && heredoc_no_tty(state, &item))
			return (state->err);
		i++;
	}
	return (state->err);
}
