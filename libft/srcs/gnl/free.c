/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 11:49:03 by adouieb           #+#    #+#             */
/*   Updated: 2026/02/02 15:39:50 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

/**
 * free_reader - Frees the content of a reader
 *
 * @param reader Pointer to the reader content to free
 */
void	free_reader(void *reader)
{
	size_t	i;

	((t_reader *)reader)->fd = -1;
	((t_reader *)reader)->read_count = 0;
	((t_reader *)reader)->start = 0;
	i = 0;
	while (i < BUF_SIZE)
		((t_reader *)reader)->buf[i++] = 0;
	free(reader);
}
