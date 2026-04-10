/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 11:52:04 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/30 18:05:21 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

/**
 * reader_ - Allocates and initializes a new reader node for the given fd
 *
 * @param fd The file descriptor for the reader
 * @return Pointer to the newly allocated reader node
 *
 * @error: On allocation failure, returns NULL (errno ENOMEM).
 */
t_reader_node	*reader_(t_i32 fd)
{
	size_t			i;
	t_reader_node	*res;
	t_reader		*reader;

	reader = malloc(sizeof(t_reader));
	if (reader == NULL)
		return (NULL);
	i = 0;
	reader->start = 0;
	reader->read_count = 0;
	reader->fd = (t_i32)fd;
	while (i < BUF_SIZE)
		reader->buf[i++] = 0;
	res = (t_reader_node *)node(reader);
	if (res == NULL)
		return (free(reader), NULL);
	return (res);
}
