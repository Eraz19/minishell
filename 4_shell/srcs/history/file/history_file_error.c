/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_file_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:08:29 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 17:29:05 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history_file_priv.h"

t_error	on_history_file_open_error(t_error err, const char *path)
{
	(void)error_print(err,
		"history",
		"unable to open history file",
		"persistent history disabled", NULL,
		"%s", path);
	return (err.type = ERR_NO, err);
}

t_error	on_history_file_read_error(t_error err, const char *path)
{
	return (error_print(err,
			"history",
			"unable to read history file",
			"persistent history disabled", NULL,
			"%s", path));
}

t_error	on_history_file_write_error(t_error err, const char *path)
{
	(void)error_print(err,
		"history",
		"unable to write to history file",
		"persistent history disabled", NULL,
		"%s", path);
	return (err.type = ERR_NO, err);
}
