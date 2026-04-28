/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   API.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 11:37:31 by adouieb           #+#    #+#             */
/*   Updated: 2026/04/27 18:19:44 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "_lexer.h"

t_token			*get_next_token(t_lexer *lexer)
{
	
}

t_token			*peek_token(t_lexer *lexer, size_t offset)
{
	
}

void			read_heredoc_stack(void)
{
	
}

// --------------------------------------------------

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

static t_file_path	create_heredoc_tmp_file(void)
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

static bool	is_heredoc_expansion_enabled(t_token_value delimiter)
{
	if (str_chr(buff_get_string(delimiter), '\'') != NULL)
		return (false);
	else if (str_chr(buff_get_string(delimiter), '"') != NULL)
		return (false);
	else if (str_chr(buff_get_string(delimiter), '\\') != NULL)
		return (false);
	return (true);
}

t_file_path		add_heredoc_to_stack(t_lexer *lexer, bool strip_tabs, t_token_value delimiter)
{
	t_heredoc	*new_heredoc;
	
	new_heredoc = malloc(sizeof(t_heredoc));
	if (new_heredoc == NULL)
		return (NULL);
	new_heredoc->path = create_heredoc_tmp_file();
	if (new_heredoc->path == NULL)
		return (NULL);
	new_heredoc->fd = -1;
	new_heredoc->delimiter = delimiter;
	new_heredoc->strip_tabs = strip_tabs;
	new_heredoc->enable_expansion = is_heredoc_expansion_enabled(delimiter);
	list_add_end(&lexer->heredoc_stack, new_heredoc);
}

void	lex_line(t_lexer *lexer, t_raw_string input)
{	
	lexer->index = 0;
	lexer->token_stream = NULL;
	lexer->heredoc_stack = NULL;
	lexer->state.char_escaped = false;
	lexer->state.mode = LEXER_MODE_DEFAULT;
	lexer->state.quote_mode = QUOTE_MODE_NONE;
	lexer->input = remove_escapable_newlines(input);
}
