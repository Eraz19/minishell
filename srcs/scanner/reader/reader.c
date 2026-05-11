/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 15:55:11 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/09 16:30:35 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include "libft.h"
#include "types.h"

static char	*read_display(const char *prompt)
{
	char	*line;

	line = readline(prompt);
	return (line);
}

char	*read_script(t_file_path script)
{
	char	*res;
	t_buff	buffer;
	int		script_fd;

	if (script == NULL || access(script, F_OK) != 0)
		return (NULL);
	script_fd = open(script, O_RDONLY);
	if (script_fd < 0 || !buff_init(&buffer, 0))
		return (NULL);
	if (!buff_read_all(&buffer, script_fd))
		return (buff_free(&buffer), close(script_fd), NULL);
	close(script_fd);
	res = buff_get_string(&buffer);
	if (res == NULL)
		return (buff_free(&buffer), NULL);
	buff_free(&buffer);
	return (res);
}

bool	complete_tty(char **prev_line)
{
	char	*new_line;
	char	*completion;

	if (prev_line == NULL || *prev_line == NULL)
		return (false);
	completion = read_display("> ");
	if (completion == NULL)
		return (false);
	new_line = str_join(*prev_line, completion);
	free(completion);
	if (new_line == NULL)
		return (false);
	*prev_line = new_line;
	return (true);
}

char	*read_tty(void)
{
	char	*res;

	//ft_printf("ENTER READ_TTY\n");
	res = read_display("minishell> ");
	if (res == NULL)
		return (/*ft_printf("LEAVE ERROR READ_TTY\n"),*/ NULL);
	//ft_printf("LEAVE READ_TTY\n");
	//ft_printf("RES = '%s'\n", res);
	return (res);
}
