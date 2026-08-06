/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator_serialize.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:19:51 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 12:19:52 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generator_serialize.h"
#include "generator_serialize_priv.h"
#include "logs.h"
#include <unistd.h>

static inline bool	generator_report_serialization_failure(int h_fd, int c_fd)
{
	if (h_fd >= 0)
		(void)close(h_fd);
	if (c_fd >= 0)
		(void)close(c_fd);
	return (false);
}

bool	generator_serialize(const t_lr_generator *generator)
{
	int	h_fd;
	int	c_fd;

	if (!generator_open(&h_fd, &c_fd))
		return (false);
	print_pass("files opened\n");
	if (!generator_write_header(h_fd, generator))
		return (generator_report_serialization_failure(h_fd, c_fd), false);
	print_pass("header_generated\n");
	if (!generator_write_c_file(c_fd, generator))
		return (generator_report_serialization_failure(h_fd, c_fd), false);
	(void)close(h_fd);
	(void)close(c_fd);
	print_pass("files closed\n");
	return (true);
}
