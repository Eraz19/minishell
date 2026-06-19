/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 20:22:35 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/16 17:51:38 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "reader_.h"
#include "history.h"

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
	if (*res == NULL)
		return (*res = heredoc, ERR_NO);
	err = history_append_to_entry(heredoc);
	if (err != ERR_NO)
		return (free(heredoc), err);
	new_input = str_join(*res, heredoc);
	if (new_input == NULL)
		return (free(heredoc), ERR_LIBC);
	return (free(*res), free(heredoc), *res = new_input, ERR_NO);
}

t_error	reader_new_input(char **res)
{
	t_error	err;

	if (res == NULL)
		return (ERR_NULL_ARGS);
	history_save_entry();
	err = readline_(res, "$ ");
	if (err)
		return (err);
	if (str_len(*res) == 1)
		return (free(*res), *res = NULL, ERR_NO);
	err = history_append_to_entry(*res);
	if (err != ERR_NO)
		return (free(*res), err);
	return (ERR_NO);
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
	err = history_append_to_entry(continuation);
	if (err != ERR_NO)
		return (free(continuation), err);
	new_input = str_join(*res, continuation);
	if (new_input == NULL)
		return (free(continuation), ERR_LIBC);
	return (free(*res), free(continuation), *res = new_input, ERR_NO);
}

t_error	reader_file_input(char **res, const char *path)
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
