/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 17:35:13 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/07 15:02:26 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include "libft.h"
#include "shell.h"
#include "__reader.h"

t_error	readline_(char **res, const char *prompt)
{
	char	*input;

	while (true)
	{
		*res = readline(prompt);
		if (*res == NULL)
			shell_exit_on_veof();
		else if (str_len(*res) == 0)
			free(*res);
		else
			break ;
	}
	input = str_join(*res, "\n");
	if (input == NULL)
		return (free(*res), ERR_LIBC);
	return (free(*res), *res = input, ERR_NO);
}
