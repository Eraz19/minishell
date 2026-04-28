/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 16:05:23 by adouieb           #+#    #+#             */
/*   Updated: 2026/04/28 15:14:59 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include <stddef.h>
#include <stdbool.h>
#include "libft.h"

// Forwarded types
typedef struct s_lexer_token t_lexer_token;

// ---------- Token ----------

typedef enum e_default_token_id
{
	TOKEN = 0			//        - Non-specific token (WORD, NAME, ASSIGNMENT_WORD, ...) that doesn't fit into other categories
}	t_default_token_id;

typedef enum e_control_token_id
{
	NEWLINE = 1,		// `\n` - command separator
	SCOLON = 2,			// `;`- command separator
	AMPERSAND = 3,		// `&` - background command separator
	DSEMI = 4,			// `;;` - case separator
	SEMI_AND = 5,		// `;&` - case fallthrough
	AND_IF = 6,			// `&&` - logical AND operator
	OR_IF = 7,			// `||` - logical OR operator
	PIPE = 8,			// `|` - pipeline operator
	LPARENTHESIS = 9,	// `(` - subshell start
	RPARENTHESIS = 10,	// `)` - subshell end
	EOF = 11			// \<EOF> - end of input
}	t_control_token_id;

typedef enum e_redirection_token_id
{
	IO_NUMBER = 12,		// `[0-9]+` - file descriptor for redirection
	LESSAND = 13,		// `<&` - duplicate input file descriptor
	GREATAND = 14,		// `>&` - duplicate output file descriptor
	LESS = 15,			// `<` - input redirection
	GREAT = 16,			// `>` - output redirection
	CLOBBER = 17,		// `>|` - output redirection with clobbering (force overwrite)
	LESSGREAT = 18,		// `<>` - input/output redirection
	DGREAT = 19,			// `>>` - append redirection
	DLESS = 20,			// `<<` - here document
	DLESSDASH = 21		// `<<-` - here document with tab stripping
}	t_redirection_token_id;

typedef enum e_reserved_word_token_id
{
	Bang,			// `!`      - logical negation operator
	Lbrace,			// `{`      - group command start
	Rbrace,			// `}`      - group command end
	Case,			// `case`   - case statement start
	Esac,			// `esac`   - case statement end
	Do,				// `do`     - do block start
	Done,			// `done`   - do block end
	If,				// `if`     - if conditional statement start
	Then,			// `then`   - if conditional statement then block start
	Elif,			// `elif`   - else if conditional statement start
	Else,			// `else`   - else conditional statement start
	Fi,				// `fi`     - if conditional statement end
	For,			// `for`    - for loop start
	In,				// `in`     - used in for loops and case statements to introduce a list of items
	Until,			// `until`  - until loop start
	While			// `while`  - while loop start
}	t_reserved_word_token_id;

typedef enum e_contextual_token_id
{
	WORD,			// A non-specific word token that doesn't fit into other categories
	NAME,			// A word that is a valid variable name (used in assignments)
	ASSIGNMENT_WORD	// A word that is part of an assignment (e.g., VAR=value)
}	t_contextual_token_id;

typedef enum e_token_type
{
	DEFAULT,		// A non-specific token that doesn't fit into other categories
	CONTROL,		// A token that represents a control operator (e.g., `|`, `&&`, `;`)
	REDIRECTION,	// A token that represents a redirection operator (e.g., `>`, `<`, `>>`)
	RESERVED_WORD,	// A token that represents a reserved word (e.g., `if`, `for`, `do`)
	CONTEXTUAL		// A token whose specific type depends on the context (e.g., WORD, NAME, ASSIGNMENT_WORD)
}	t_token_type;

typedef union u_token_id
{
	t_default_token_id			default_;		// Valid if discriminant == DEFAULT
	t_control_token_id			control_;		// Valid if discriminant == CONTROL
	t_redirection_token_id		redirection_;	// Valid if discriminant == REDIRECTION
	t_reserved_word_token_id	reserved_word_;	// Valid if discriminant == RESERVED_WORD
	t_contextual_token_id		contextual_;	// Valid if discriminant == CONTEXTUAL
}	t_token_id;

typedef t_buff	t_token_value;	// The string value of the token (e.g., the actual word, operator, etc.)
typedef int		t_grammar_rule;

typedef t_list t_tokens;
typedef t_node t_tokens_item;
typedef struct s_token
{
	t_token_type	type;	// Indicates which type of token this is
	t_token_id		id;
	t_grammar_rule	rule;	// The grammar rule that this token matches (used for parsing)
	size_t			offset;	// The raw string from the input that corresponds to this token (before any processing)
	t_token_value	value;
}	t_token;

// ---------- Lexer state ----------

typedef enum e_lexer_mode
{
	LEXER_MODE_DEFAULT,	// Mode de lexing standard, utilisé pour la plupart des commandes
	LEXER_MODE_HEREDOC,	// Mode de lexing spécifique pour les heredocs, qui traite les expansions différemment (ex: <<- strip les tabs)
}	t_lexer_mode;

typedef enum e_quote_mode
{
	QUOTE_MODE_NONE,	// Not in a quote
	QUOTE_MODE_SINGLE,	// In a single quote
	QUOTE_MODE_DOUBLE,	// In a double quote
}	t_quote_mode;

typedef char*	t_file_path;
typedef char*	t_raw_string;

typedef struct s_state
{
	t_lexer_mode	mode;			// !!! NEED TO PROVE TO BE USEFULL
	t_quote_mode	quote_mode;
	bool			char_escaped;	// Indicates if the next character is escaped (preceded by a backslash)
}	t_state;

typedef t_list t_heredoc_stack;
typedef t_node t_heredoc_stack_item;
typedef struct s_heredoc
{
	int				fd;
	t_file_path		path;
	t_token_value	delimiter;
	bool			strip_tabs;			// Indicates if leading tabs should be stripped from the input (for <<-)
	bool			enable_expansion;
}	t_heredoc;

typedef struct s_lexer
{
	bool			is_eof;			// Indicates if the end of the input has been reached
	size_t			index;			// Current position in the input string
	t_raw_string	input;			// The original input string being lexed
	t_state			state;
	t_tokens		token_stream;	// List of tokens generated by the lexer
	t_heredoc_stack	heredoc_stack;	// Non-NULL if currently lexing a heredoc delimiter
}	t_lexer;

// ------------ Utils ------------

t_lexer_token	*to_lexer_token(t_token **token_ptr);
t_token			*from_lexer_token(t_lexer_token **token_ptr);

// ------------ API ------------

void			lex_line(t_lexer *lexer, t_raw_string input);

t_token			*get_next_token(t_lexer *lexer);
t_token			*peek_token(t_lexer *lexer, size_t offset);

typedef struct s_add_heredoc
{
	t_token_value	delimiter;
	bool			strip_tabs;
}	t_add_heredoc;

void			read_heredoc_stack(void);
t_file_path		add_heredoc_to_stack(t_lexer *lexer, t_add_heredoc params);

#endif
