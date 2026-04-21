/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 16:05:23 by adouieb           #+#    #+#             */
/*   Updated: 2026/04/21 19:49:13 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

#include <stddef.h>
#include <stdbool.h>

typedef enum e_blank
{
	BLK_TAB = '\t',
	BLK_SPACE = ' '
}	t_blank;

typedef enum e_lexer_mode
{
	LEXER_MODE_GENERAL,					// Mode de lexing standard, utilisé pour la plupart des commandes
	LEXER_MODE_HEREDOC,					// Mode de lexing spécifique pour les heredocs, qui traite les expansions différemment (ex: <<- strip les tabs)
}	t_lexer_mode;

typedef enum e_quote_mode
{
	QUOTE_MODE_NONE,					// Not in a quote
	QUOTE_MODE_SINGLE,					// In a single quote
	QUOTE_MODE_DOUBLE,					// In a double quote
}	t_quote_mode;

typedef struct s_state
{
	t_lexer_mode	mode;
	t_quote_mode	quote_mode;
	bool			char_escaped;		// Indicates if the next character is escaped (preceded by a backslash)
}	t_state;

typedef struct s_heredoc
{
	char	*delimiter;
	bool	strip_tabs;					// Indicates if leading tabs should be stripped from the input (for <<-)
	bool	enable_expansion;
	int		fd;
	char	*path;
}	t_heredoc;

typedef struct s_lexer
{
	size_t			index;				// Current position in the input string
	t_state			state;
	char			*current_token;
	t_heredoc		*current_heredoc;	// Non-NULL if currently lexing a heredoc delimiter
}	t_lexer;

typedef enum e_conditional_token_type
{
	
}	t_conditional_token_type;

// ------- Public API of the lexer -------

t_token	*get_next_token(t_lexer *lexer);

void	set_lexer_mode(t_lexer *lexer, t_lexer_mode mode);

// ------- Private API of the lexer -------

char	*remove_escapable_newlines(t_lexer *lexer, char *string);

char	*get_raw_token(t_lexer *lexer, char *string);

#endif
