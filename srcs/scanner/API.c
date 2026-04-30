/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   API.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 11:37:31 by adouieb           #+#    #+#             */
/*   Updated: 2026/04/29 18:23:26 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "scanner.h"
#include "_scanner.h"

t_token	*get_next_token(t_lexer *lexer)
{
	t_token			*res;
	t_node			*node;
	t_token	*node_content;

	if (lexer == NULL || lexer->tokens == NULL)
		return (NULL);
	if (list_get_size(lexer->tokens) == 0)
		return (NULL);
	node = list_get_node_n(lexer->tokens, 0);
	node_content = (t_token *)node->content;
	list_rm(&lexer->tokens, node, free_lexer_token);
	return (res);
}

t_token	*peek_token(t_lexer *lexer, size_t offset)
{
	if (lexer == NULL || lexer->token_stream == NULL)
		return (NULL);
	if (list_get_size(lexer->token_stream) <= offset)
		return (NULL);
	return (list_get_content_n(lexer->token_stream, offset));
}

void	read_heredoc_stack(void)
{
	
}

t_file_path	add_heredoc_to_stack(t_lexer *lexer, t_add_heredoc args)
{
	t_heredoc	*new;
	
	if (lexer == NULL)
		return (NULL);
	new = malloc(sizeof(t_heredoc));
	if (new == NULL)
		return (NULL);
	new->path = create_heredoc_tmp_file();
	if (new->path == NULL)
		return (NULL);
	new->fd = -1;
	new->delimiter = args.delimiter;
	new->strip_tabs = args.strip_tabs;
	new->enable_expansion = is_heredoc_expansion_enabled(args.delimiter);
	list_add_end(&lexer->heredoc_stack, new);
	return (new->path);
}
bool	get_command_continuation(t_lexer *lexer)
{
	char	*line;

	line = read_line_continuation();
	if (line == NULL)
		return (false);
	line = remove_escapable_newlines(line);
	str_join(lexer->index, line);
}

bool	lex_line(t_lexer *lexer)
{
	if (lexer == NULL)
		return (false);
	while (is_contains_eof(lexer) == false)
	{
		if (lexer->input[lexer->index] == '\0')
			
	}
}
