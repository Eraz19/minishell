/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 18:18:15 by adouieb           #+#    #+#             */
/*   Updated: 2026/04/27 18:34:07 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "_lexer.h"

bool	create_new_file(t_file_path path)
{
	int	fd;

	fd = open(path, O_CREAT, 0644);
	if (fd < 0)
		return (false);
	if (close(fd) < 0)
		return (false);
	return (true);
}
