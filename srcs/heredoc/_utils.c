/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 17:29:41 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/15 16:40:38 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "libft.h"
#include "utils.h"
#include "heredoc_.h"
#include "expander.h"

t_error	heredoc_build_delimiter(t_heredoc *state, char **delim)
{
	char		*delim_;
	t_expansion	delim_unquoted;
	char		*delim_unquoted_str;

	expander_init(&delim_unquoted);
	state->err = expander_word(&delim_unquoted, *delim, QUOTE_REMOVE_ONLY);
	if (state->err)
		return (state->err);
	if (delim_unquoted.len == 0)
		return (expander_free(&delim_unquoted), state->err = ERR_LIBC);
	state->err = expander_get(&delim_unquoted, &delim_unquoted_str, 0);
	if (state->err)
		return (expander_free(&delim_unquoted), state->err);
	delim_ = str_join(delim_unquoted_str, "\n");
	if (delim_ == NULL)
		state->err = ERR_LIBC;
	return (expander_free(&delim_unquoted), *delim = delim_, state->err);
}

static t_error	heredoc_build_path(t_heredoc *state, char **path)
{
	char	*id;
	t_buff	path_buff;

	if (!buff_init(&path_buff, 0, "/tmp/minishell_heredoc_", 23))
		return (state->err = ERR_LIBC);
	id = ft_ltoa((long)state->file_id);
	if (id == NULL || id[0] == '-')
		return (free(id), buff_free(&path_buff), state->err = ERR_LIBC);
	if (!buff_append(&path_buff, id, (long)str_len(id)))
		return (free(id), buff_free(&path_buff), state->err = ERR_LIBC);
	free(id);
	*path = buff_get_string(&path_buff);
	if (*path == NULL)
		return (buff_free(&path_buff), state->err = ERR_LIBC);
	return (buff_free(&path_buff), state->err);
}

t_error	heredoc_create_file(t_heredoc *state, char **path)
{
	int	fd;

	fd = -1;
	while (fd == -1)
	{
		if (heredoc_build_path(state, path))
			return (state->err);
		fd = open(*path, O_CREAT | O_EXCL | O_WRONLY, 0600);
		if (fd == -1 && errno != EEXIST)
			return (free(*path), state->err = ERR_LIBC);
		if (fd == -1)
			free(*path);
		state->file_id++;
	}
	return (close(fd), state->err);
}
