/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 14:42:56 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/01 16:50:36 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

time_t	get_now_unix_seconds(void)
{
	struct stat	stat;
	int			fds[2];

	if (pipe(fds) == -1)
		return (-1);
	if (fstat(fds[0], &stat) == -1)
		return (close(fds[0]), close(fds[1]), -1);
	return (close(fds[0]), close(fds[1]), stat.st_mtim.tv_sec);
}
