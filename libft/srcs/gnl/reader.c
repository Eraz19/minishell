/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 23:45:50 by adouieb           #+#    #+#             */
/*   Updated: 2026/01/30 14:30:17 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

/**
 * is_fd_reader - Predicate to check if a reader matches the given fd
 *
 * @param reader The reader content to check
 * @param fd Pointer to the fd to match against
 * @return TRUE if matches, FALSE otherwise
 */
static t_bool	is_fd_reader(void *reader, void *fd)
{
	t_i32	fd_;

	fd_ = *(t_i32 *)fd;
	return (((t_reader *)reader)->fd == fd_);
}

/**
 * select_reader_node - Selects or creates a reader for the given fd
 *
 * @param readers The list of current readers
 * @param fd The file descriptor to select
 * @return Pointer to the selected or newly created reader
 *
 * @error: On allocation failure, returns NULL (errno ENOMEM).
 */
t_reader_node	*select_reader_node(t_readers *readers, t_u32 fd)
{
	t_reader_node	*reader_node;
	t_readers		matching_readers;

	matching_readers = filter(*readers, is_fd_reader, &fd);
	if (matching_readers.nodes != NULL)
		return ((t_reader_node *)matching_readers.nodes);
	reader_node = reader_((t_i32)fd);
	if (reader_node == NULL)
		return (NULL);
	lst_insert(readers, (t_node *)reader_node, 0);
	return (reader_node);
}

/**
 * read_file - Reads data from the file descriptor into the reader's buffer
 *
 * @param reader Pointer to the reader content
 * @param fd The file descriptor to read from
 */
void	read_file(t_reader *reader, t_u32 fd)
{
	reader->read_count = read((t_i32)fd, reader->buf, BUF_SIZE);
	reader->start = 0;
}
