/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_cmd_convert_file_error.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:56:31 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 21:26:45 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_search_priv.h"

t_error	cmd_convert_file_error(t_error err)
{
	if (err.type == ERR_FILE_NOT_FOUND)
		err.type = ERR_POSIX_CMD_NFOUND;
	else if (err.type == ERR_FILE_NOT_EXECUTABLE)
		err.type = ERR_POSIX_CMD_NEXC;
	return (err);
}
