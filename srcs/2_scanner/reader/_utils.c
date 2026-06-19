/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 17:35:13 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/16 16:52:56 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include "libft.h"
#include "shell.h"
#include "reader_.h"

t_error	readline_(char **res, const char *prompt)
{
	char	*input;

	*res = readline(prompt);
	while (*res == NULL)
	{
		shell_exit_on_veof();
		if (!option_is_active(OPT_INTERACTIVE))
			return (ERR_VEOF);
		*res = readline(prompt);
	}
	if (**res == '\0')
	{
		free(*res);
		*res = str_dup("");
		if (*res == NULL)
			return (ERR_LIBC);
	}
	input = str_join(*res, "\n");
	if (input == NULL)
		return (free(*res), ERR_LIBC);
	return (free(*res), *res = input, error(ERR_NO));
}
