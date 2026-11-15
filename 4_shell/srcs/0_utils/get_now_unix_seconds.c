/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_now_unix_seconds.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:47:26 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 12:47:27 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

// TODO: stub ASM
time_t	get_now_unix_seconds(void)
{
	struct stat	stat;
	int			fds[2];

	if (pipe(fds) == -1)
		return (-1);
	if (fstat(fds[0], &stat) == -1)
		return (close(fds[0]), close(fds[1]), -1);
	return (close(fds[0]), close(fds[1]), stat.st_mtime);
}
