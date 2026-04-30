/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 17:52:47 by adouieb           #+#    #+#             */
/*   Updated: 2026/04/29 17:55:27 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>

char	*read_line(void)
{
	char	*line;

	line = readline("minishell> ");
	return (line);
}

char	*read_line_continuation(void)
{
	char	*line;

	line = readline("> ");
	return (line);
}

char	*read_line_heredoc(void)
{
	char	*line;

	line = readline("heredoc> ");
	return (line);
}
