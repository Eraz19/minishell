/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 10:39:01 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/01 09:56:11 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <readline/readline.h>
#include "_reader.h"

static t_error	readline_(char **res, const char *prompt)
{
	char	*input;

	*res = readline(prompt);
	if (*res == NULL)
		return (shell_exit_on_veof(), readline_(res, prompt));
	if (str_len(*res) == 0)
		return (free(*res), readline_(res, prompt));
	input = str_join(*res, "\n");
	if (input == NULL)
		return (ERR_LIBC);
	return (free(*res), *res = input, ERR_NO);
}

t_error	reader_continuation(char **res)
{
	t_error	err;
	char	*new_input;
	char	*continuation;

	if (res == NULL)
		return (ERR_NULL_ARGS);
	err = readline_(&continuation, "> ");
	if (err != ERR_NO)
		return (err);
	new_input = str_join(*res, continuation);
	if (new_input == NULL)
		return (ERR_LIBC);
	free(*res);
	free(continuation);
	*res = new_input;
	return (ERR_NO);
}

t_error	reader_new_input(char **res)
{
	if (res == NULL)
		return (ERR_NULL_ARGS);
	return (readline_(res, "$ "));
}

t_error	reader_heredoc(char **res)
{
	t_error	err;
	char	*new_input;
	char	*continuation;

	if (res == NULL)
		return (ERR_NULL_ARGS);
	err = readline_(&continuation, "> ");
	if (err != ERR_NO)
		return (err);
	new_input = str_join(*res, continuation);
	if (new_input == NULL)
		return (ERR_LIBC);
	free(*res);
	free(continuation);
	*res = new_input;
	return (ERR_NO);
}
