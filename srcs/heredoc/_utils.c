/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 17:29:41 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/19 16:24:21 by adouieb          ###   ########.fr       */
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
	char	*delim_;

	state->err = expander_quote_remove(delim);
	if (state->err.type)
		return (free(*delim), state->err);
	delim_ = str_join(*delim, "\n");
	if (delim_ == NULL)
		state->err = error_sys();
	return (free(*delim), *delim = delim_, state->err);
}

static t_error	heredoc_build_path(t_heredoc *state, char **path)
{
	char	*id;
	t_buff	path_buff;

	if (!buff_init(&path_buff, 0, "/tmp/minishell_heredoc_", 23))
		return (state->err = error_sys());
	id = ft_ltoa((long)state->file_id);
	if (id == NULL || id[0] == '-')
		return (free(id), buff_free(&path_buff), state->err = error_sys());
	if (!buff_append(&path_buff, id, (long)str_len(id)))
		return (free(id), buff_free(&path_buff), state->err = error_sys());
	free(id);
	*path = buff_get_string(&path_buff);
	if (*path == NULL)
		return (buff_free(&path_buff), state->err = error_sys());
	return (buff_free(&path_buff), state->err);
}

t_error	heredoc_create_file(t_heredoc *state, char **path)
{
	int	fd;

	fd = -1;
	while (fd == -1)
	{
		if (heredoc_build_path(state, path).type)
			return (state->err);
		fd = open(*path, O_CREAT | O_EXCL | O_WRONLY, 0600);
		if (fd == -1 && errno != EEXIST)
			return (free(*path), state->err = error_sys());
		if (fd == -1)
			free(*path);
		state->file_id++;
	}
	return (close(fd), state->err);
}
