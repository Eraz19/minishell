/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 20:22:35 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/09 16:21:41 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "__reader.h"

t_error	reader_file_input(char **res, t_file_path path)
{
	int		fd;
	t_buff	buffer;

	if (path == NULL)
		return (ERR_NULL_ARGS);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ERR_OPEN_FILE);
	buff_init(&buffer, 0, NULL, 0);
	if (!buff_read_all(&buffer, fd))
		return (close(fd), buff_free(&buffer), ERR_LIBC);
	*res = buff_get_string(&buffer);
	if (*res == NULL)
		return (close(fd), buff_free(&buffer), ERR_LIBC);
	return (close(fd), buff_free(&buffer), ERR_NO);
}

t_error	reader_new_input(char **res)
{
	if (res == NULL)
		return (ERR_NULL_ARGS);
	return (readline_(res, "$ "));
}

t_error	reader_continuation(char **res)
{
	t_error	err;
	char	*new_input;
	char	*continuation;

	if (res == NULL)
		return (ERR_NULL_ARGS);
	err = readline_(&continuation, "> ");
	if (err != ERR_NO)
		return (err);
	new_input = str_join(*res, continuation);
	if (new_input == NULL)
		return (free(continuation), ERR_LIBC);
	return (free(*res), free(continuation), *res = new_input, ERR_NO);
}

t_error	reader_heredoc(char **res)
{
	t_error	err;
	char	*new_input;
	char	*heredoc;

	if (res == NULL)
		return (ERR_NULL_ARGS);
	err = readline_(&heredoc, "> ");
	if (err != ERR_NO)
		return (err);
	new_input = str_join(*res, heredoc);
	if (new_input == NULL)
		return (free(heredoc), ERR_LIBC);
	return (free(*res), free(heredoc), *res = new_input, ERR_NO);
}
