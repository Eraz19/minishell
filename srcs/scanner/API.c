/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   API.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 11:37:31 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/05 16:14:52 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include "libft.h"
#include "types.h"
#include "scanner.h"
#include "_scanner.h"
#include "./command_lexer/_lexer.h"


- read
- line_lexing
	- 

/*
t_token	*get_next_token(t_lexer *lexer)
{
	t_token	*res;
	t_node	*node;
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


bool	is_blank(char c)
{
	return (c == ' ' || c == '\t');
}

bool	is_double_quote_special_char(char c)
{
	return (c == '"' || c == '\\' || c == '$' || c == '`' || c == '\n');
}
/*
bool	is_operator_char(t_token_type *operator_type, t_lexer *lexer)
{
	is_dsemi();
	is_semi_and();
	is_newline();
	is_semicolon();
	is_ampersand();
	is_and_if();
	is_or_if();
	is_pipe();
	is_lparenthesis();
	is_rparenthesis();
	is_greatand();
	is_lessand();
	is_io_number();
	is_dless();
	is_dlessdash();
	is_less();
	is_great();
	is_clobber();
	is_lessgreat();
	is_dgreat();
}

bool	lex_blank(t_lexer *lexer)
{
	
}

static bool	lex_line_unquoted(t_lexer *lexer)
{
	if (lexer->quotes == NONE_ && lexer->input[lexer->index] == '\'')
		lexer->quotes = SINGLE_;
	else if (lexer->quotes == NONE_ && lexer->input[lexer->index] == '"')
		lexer->quotes = DOUBLE_;
	else if (lexer->input[lexer->index] == '\\')
	{
		
	}
		
	else if (is_blank(lexer->input[lexer->index]))
		return (lex_blank(lexer));


	
		
	
	
	else if (is_operator_char(&operator_type, lexer))
		lex_operator(lexer);
	else
		lex_word(lexer);
}

static bool	lex_line_quoted(t_lexer *lexer)
{
	if (lexer == NULL)
		return (false);
	if (lexer->quotes != SINGLE_ && lexer->input[lexer->index] == '\\')
		++lexer->index;	
	else if (lexer->quotes == SINGLE_ && lexer->input[lexer->index] == '\'')
		lexer->quotes = NONE_;
	else if (lexer->quotes == DOUBLE_ && lexer->input[lexer->index] == '"')
		lexer->quotes = NONE_;
	++lexer->index;
	return (true);
}

bool	end_of_input(t_lexer *lexer)
{
	if (is_eof(lexer))
	{
		if (add_new_token(lexer, token_(lexer->start, lexer->index)) == false)
			return (false);

	}
}

bool	lex_line(t_lexer *lexer)
{
	if (lexer == NULL)
		return (false);
	while (*lexer->start == '\0')
	{
		if ( && end_of_input(lexer) == false)
			return (false);
		if (lexer->quotes == NONE_ && lex_line_unquoted(lexer) == false)
			return (false);
		else if (lex_line_quoted(lexer) == false)
			return (false);
	}	
	return (true);
}

bool	read_command_continuation(t_lexer *lexer)
{



	return (true);
}

bool	read_input(t_scanner *scanner, t_lexer *lexer)
{
	union u_const_cast
	{
		const char	*const_input;
		char		*input;
	}		cast;
	char	*line;
	char	*new_input;

	if (scanner == NULL || lexer == NULL)
		return (false);
	if (scanner->mode == INTERACTIVE)
		line = read_line();
	if (line == NULL)
		return (false);
	line = remove_escapable_newlines(line);
	cast.const_input = lexer->input;
	new_input = str_join(cast.input, line);
	if (new_input == NULL)
		return (false);
	free(line);
	free(lexer->input);
	lexer->input = new_input;
	return (true);
}
*/










// --------------- READER ---------------
static bool	get_script_content(t_buff *buffer, t_file_path script)
{
	int	script_fd;

	if (script == NULL || access(script, F_OK) != 0)
		return (false);
	script_fd = open(script, O_RDONLY);
	if (script_fd < 0)
		return (false);
	if (!buff_init(buffer, 0))
		return (false);
	if (!buff_read_all(buffer, script_fd))
		return (buff_free(buffer), false);
	close(script_fd);
	return (true);
}

bool	read_non_interactif(char ***res, t_file_path script)
{
	t_buff	buffer;
	char	*script_content;

	if (get_script_content(&buffer, script) == false)
		return (false);
	script_content = buff_get_string(&buffer);
	if (script_content == NULL)
		return (buff_free(&buffer), false);
	remove_escapable_newlines(script_content);
	*res = str_split(script_content, '\n');
	if (*res == NULL)
		return (free(script_content), buff_free(&buffer), false);
	buff_free(&buffer);
	free(script_content);
	return (true);
}
// --------------------------------------
bool	complete_line(char ***res)
{
	char	*new_line;
	char	*completion;

	if (res == NULL || *res == NULL || **res == NULL)
		return (false);
	completion = read_line_continuation();
	if (completion == NULL)
		return (free(**res), **res = NULL, free(*res), *res = NULL, false);
	new_line = str_join(**res, completion);
	free(**res);
	free(completion);
	if (new_line == NULL)
		return (false);
	remove_escapable_newlines(new_line);
	**res = new_line;
	return (true);
}

char	*read_tty(void)
{
	char	*res;

	res = read_line();
	if (res == NULL)
		return (false);
	remove_escapable_newlines(res);
	return (res);
}
// --------------- SCANNER ---------------

get_next_token();
peek_token();
io_here();