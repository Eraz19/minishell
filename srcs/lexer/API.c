/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   API.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 11:37:31 by adouieb           #+#    #+#             */
/*   Updated: 2026/04/28 13:43:20 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "_lexer.h"

t_token			*get_next_token(t_lexer *lexer)
{
	t_token			*res;
	t_node			*node;
	t_lexer_token	*node_content;

	if (list_get_size(lexer->token_stream) == 0)
		return (NULL);
	node = list_get_node_n(lexer->token_stream, 0);
	node_content = (t_lexer_token *)node->content;
	res = from_lexer_token(&node_content);
	list_rm(&lexer->token_stream, node, free_lexer_token);
	return (res);
}

t_token	*peek_token(t_lexer *lexer, size_t offset)
{
	if (list_get_size(lexer->token_stream) <= offset)
		return (NULL);
	return (list_get_content_n(lexer->token_stream, offset));
}

void			read_heredoc_stack(void)
{
	
}

t_file_path		add_heredoc_to_stack(t_lexer *lexer, t_add_heredoc args)
{
	t_heredoc	*new;
	
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
