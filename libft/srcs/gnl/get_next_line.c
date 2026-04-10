/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 17:26:03 by adouieb           #+#    #+#             */
/*   Updated: 2026/02/03 11:48:30 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

/**
 * on_failure - Handles cleanup on read failure
 *
 * @param readers The list of current readers
 * @param reader The reader that encountered the failure
 * @param buf The buffer containing data from previous reads to free
 * @return A NULL t_dstr indicating failure
 */
t_dstr	on_failure(t_readers *readers, t_reader_node *reader, t_dbuf *buf)
{
	free_node(readers, (t_node *)reader, free_reader);
	free_dbuf(buf);
	return (dstr_s(0));
}

/**
 * on_file_end - Handles cleanup on end-of-file
 *
 * @param readers The list of current readers
 * @param reader The reader that reached EOF
 * @param buf The buffer containing data from previous reads to convert
 * @return A t_dstr containing any remaining data before EOF
 */
t_dstr	on_file_end(t_readers *readers, t_reader_node *reader, t_dbuf *buf)
{
	free_node(readers, (t_node *)reader, free_reader);
	return (str_from_buf(buf));
}

/**
 * merge_buffer - Merges data from the reader's buffer into the output buffer
 *
 * @param reader Pointer to the reader content
 * @param buf Pointer to the output buffer to merge into
 * @param delim The line delimiter (e.g., "\n")
 * @return The updated output buffer
 */
t_dbuf	merge_buffer(t_reader *reader, t_dbuf *buf, t_cstr delim)
{
	t_cbuf	buf_;
	ssize_t	buf_size;

	buf_size = reader->read_count - (ssize_t)reader->start;
	buf_ = cbuf(reader->buf + reader->start, (size_t)buf_size);
	buf_size = buf_findindex(buf_, cbuf(delim.s, delim.len));
	if (buf_size == -1)
		buf_size = (ssize_t)buf_.size;
	else
		buf_size = (buf_size * (ssize_t)delim.len) + (ssize_t)delim.len;
	buf_.size = (size_t)buf_size;
	*buf = buf_insertc(buf, buf_, buf->size, x2);
	reader->start = reader->start + (size_t)buf_size;
	return (*buf);
}

t_bool	buf_contains_delimiter(t_dbuf *buf, t_cstr delim)
{
	t_cbuf	buf_;
	t_cbuf	delim_;

	buf_ = cbuf(buf->data, buf->len);
	delim_ = cbuf(delim.s, delim.len);
	if (buf_findindex(buf_, delim_) != -1)
		return (TRUE);
	return (FALSE);
}

/**
 * get_next_line - Reads the next line from the given file descriptor
 *
 * @param fd The file descriptor to read from
 * @param readers The list of current readers
 * @param delim The line delimiter (e.g., "\n")
 * @return A t_dstr containing the next line
 *
 * @error: On reading failure, returns a NULL t_dstr (errno EBADF/EIO/EAGAIN).
 *         On allocation failure, returns a NULL t_dstr (errno ENOMEM).
 */
t_dstr	get_next_line(t_u32 fd, t_readers *readers, t_cstr delim)
{
	t_dbuf			buf;
	t_reader		*reader;
	t_reader_node	*reader_node;

	1 && (buf = dbuf_s(0), reader_node = select_reader_node(readers, fd));
	if (reader_node == NULL || reader_node->content == NULL)
		return (free_lst(readers, free_reader), dstr_s(0));
	reader = reader_node->content;
	while (TRUE)
	{
		if ((reader->start == 0) || reader->start >= (size_t)reader->read_count)
		{
			read_file(reader, fd);
			if (reader->read_count == 0)
				return (on_file_end(readers, reader_node, &buf));
			else if (reader->read_count == -1 && errno != EINTR)
				return (on_failure(readers, reader_node, &buf));
		}
		buf = merge_buffer(reader, &buf, delim);
		if (buf.data == NULL)
			return (on_failure(readers, reader_node, &buf));
		else if (buf_contains_delimiter(&buf, delim) == TRUE)
			return (str_from_buf(&buf));
	}
}
