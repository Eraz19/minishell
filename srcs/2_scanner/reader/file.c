/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 10:40:20 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/28 15:58:47 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "_reader.h"

t_error	reader_file_input(char **res, t_scanner_path path)
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
		return (ERR_LIBC);
	*res = buff_get_string(&buffer);
	if (*res == NULL)
		return (ERR_LIBC);
	return (close(fd), buff_free(&buffer), ERR_NO);
}
