/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_error_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 19:55:21 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 19:57:28 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "posix_helpers.h"
#include "shell.h"
#include <unistd.h>

#define SEPARATOR			": "
#define WRITE_ERROR_PREFIX	"write error: "

static void	error_print_format(const char *fstring, va_list args)
{
	va_list		copy;
	t_buff		buff;
	const char	default_message[] = "(unable to compute formatted message)";

	va_copy(copy, args);
	(void)buff_init(&buff, 0, NULL, -1);
	if (buff_append_vformat(&buff, fstring, copy))
	{
		(void)posix_write(STDERR_FILENO, buff.data, buff.len);
		(void)posix_write(STDERR_FILENO, SEPARATOR, str_len(SEPARATOR));
	}
	else
		(void)posix_write(
			STDERR_FILENO,
			default_message,
			str_len(default_message));
	va_end(copy);
	buff_free(&buff);
}

static inline void	error_print_end(t_error err)
{
	const char	*string;

	if (err.type == ERR_POSIX_WRITE)
		(void)posix_write(STDERR_FILENO, WRITE_ERROR_PREFIX,
			str_len(WRITE_ERROR_PREFIX));
	string = error_to_string(err);
	(void)posix_write(STDERR_FILENO, string, str_len(string));
	(void)posix_write(STDERR_FILENO, "\n", 1);
}

t_error	error_print(t_error err, ...)
{
	va_list		args;
	const char	*shell_name;
	const char	*string;

	if (err.printed == true)
		return (err);
	shell_name = shell_get_name();
	(void)posix_write(STDERR_FILENO, shell_name, str_len(shell_name));
	(void)posix_write(STDERR_FILENO, SEPARATOR, str_len(SEPARATOR));
	va_start(args, err);
	string = va_arg(args, const char *);
	while (string)
	{
		(void)posix_write(STDERR_FILENO, string, str_len(string));
		(void)posix_write(STDERR_FILENO, SEPARATOR, str_len(SEPARATOR));
		string = va_arg(args, const char *);
	}
	string = va_arg(args, const char *);
	if (string)
		error_print_format(string, args);
	va_end(args);
	error_print_end(err);
	return (err.printed = true, err);
}
