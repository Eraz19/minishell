/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 18:15:35 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/04 21:36:59 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "../_lexer.h"

static bool	is_heredoc_file_exists(t_file_path *res, size_t specifier)
{
	t_file_path	path;
	t_file_path	path_specifier_str;

	path = str_dup(HEREDOC_TMP_PATH);
	if (path == NULL)
		return (false);
	path_specifier_str = ft_ltoa((long)specifier);
	if (path_specifier_str == NULL)
		return (free(path), false);
	*res = str_join(path, path_specifier_str);
	free(path);
	free(path_specifier_str);
	if (*res == NULL)
		return (false);
	return (access(*res, F_OK) == 0);
}

t_file_path	create_heredoc_tmp_file(void)
{
	size_t		i;
	t_file_path	path;

	i = 0;
	while (true)
	{
		if (is_heredoc_file_exists(&path, i) == false)
		{
			if (create_new_file(path) == true)
				return (path);
			else
				return (free(path), NULL);
		}
		free(path);
		++i;
	}
}

bool	is_heredoc_expansion_enabled(t_token_value delimiter)
{
	if (str_chr(buff_get_string(&delimiter), '\'') != NULL)
		return (false);
	else if (str_chr(buff_get_string(&delimiter), '"') != NULL)
		return (false);
	else if (str_chr(buff_get_string(&delimiter), '\\') != NULL)
		return (false);
	return (true);
}
