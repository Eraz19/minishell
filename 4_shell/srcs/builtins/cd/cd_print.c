/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:40:45 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 13:40:46 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "env.h"
#include "posix_helpers.h"

t_error	cd_print_new(void)
{
	t_string	pwd;
	t_error		err;

	err = env_get_from_const("PWD", &pwd);
	if (err.type)
		return (err);
	if (!string_append_n(&pwd, "\n", 1))
		return (string_free(&pwd), error_sys());
	err = posix_write(STDOUT_FILENO, pwd.data, pwd.len);
	return (string_free(&pwd), err);
}
