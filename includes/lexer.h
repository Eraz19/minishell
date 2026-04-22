/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 16:05:23 by adouieb           #+#    #+#             */
/*   Updated: 2026/04/22 20:30:12 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include <stddef.h>
#include <stdbool.h>
#include "libft.h"

// ---------- Token ----------

typedef enum e_default_token_id
{
	TOKEN // Non-specific token (WORD, NAME, ASSIGNMENT_WORD) that doesn't fit into other categories
}	t_default_token_id;

typedef enum e_control_token_id
{
	NEW_LINE,		// `\n` - command separator
	SCOLON,			// `;`- command separator
	DSCOLON,		// `;;` - case separator
	CASEFT,			// `;&` - case fallthrough
	BACKGROUND,		// `&` - background command separator
	ANDIF,			// `&&` - logical AND operator
	PIPE,			// `|` - pipeline operator
	ORIF,			// `||` - logical OR operator
	OPARENTHESIS,	// `(` - subshell start
	CPARENTHESIS,	// `)` - subshell end
	EOF				// \<EOF> - end of input
}	t_control_token_id;

typedef enum e_redirection_token_id
{
	IO_NUMBER,		// `[0-9]+` - file descriptor for redirection
	IREDIRECT,		// `<` - input redirection
	OREDIRECT,		// `>` - output redirection
	CLOBBER,		// `>|` - output redirection with clobbering (force overwrite)
	HERE_DOC,		// `<<` - here document
	AREDIRECT,		// `>>` - append redirection
	IDUP_FD,		// `<&` - duplicate input file descriptor
	ODUP_FD,		// `>&` - duplicate output file descriptor
	HERE_DOC_STRIP,	// `<<-` - here document with tab stripping
	IOREDIRECT		// `<>` - input/output redirection
}	t_redirection_token_id;

typedef enum e_reserved_word_token_id
{
	NOT,	//- `!` - logical negation operator
	OBRACE,	//- `{` - group command start
	CBRACE,	//- `}` - group command end
	CASE,	//- `case` - case statement start
	ESAC,	//- `esac` - case statement end
	DO,		//- `do` - do block start
	DONE,	//- `done` - do block end
	IF,		//- `if` - `if` conditional statement start
	THEN,	//- `then` - `if` conditional statement then block start
	ELIF,	//- `elif` - `else if` conditional statement start
	ELSE,	//- `else` - `else` conditional statement start
	FI,		//- `fi` - `if` conditional statement end
	FOR,	//- `for` - for loop start
	IN,		//- `in` - used in for loops and case statements to introduce a list of items
	UNTIL,	//- `until` - until loop start
	WHILE	//- `while` - while loop start
}	t_reserved_word_token_id;

typedef enum e_contextual_token_id
{
	WORD,			// A non-specific word token that doesn't fit into other categories
	NAME,			// A word that is a valid variable name (used in assignments)
	ASSIGNMENT_WORD	// A word that is part of an assignment (e.g., VAR=value)
}	t_contextual_token_id;

typedef enum e_token_discriminant
{
	DEFAULT,		// A non-specific token that doesn't fit into other categories
	CONTROL,		// A token that represents a control operator (e.g., `|`, `&&`, `;`)
	REDIRECTION,	// A token that represents a redirection operator (e.g., `>`, `<`, `>>`)
	RESERVED_WORD,	// A token that represents a reserved word (e.g., `if`, `for`, `do`)
	CONTEXTUAL		// A token whose specific type depends on the context (e.g., WORD, NAME, ASSIGNMENT_WORD)
}	t_token_discriminant;

typedef union u_token_type
{
	t_token_discriminant		discriminant;	// Indicates which type of token this is
	t_default_token_id			default_;		// Valid if discriminant == DEFAULT
	t_control_token_id			control_;		// Valid if discriminant == CONTROL
	t_redirection_token_id		redirection_;	// Valid if discriminant == REDIRECTION
	t_reserved_word_token_id	reserved_word_;	// Valid if discriminant == RESERVED_WORD
	t_contextual_token_id		contextual_;	// Valid if discriminant == CONTEXTUAL
}	t_token_type;

typedef char*	t_raw_string_ptr;
typedef char*	t_token_value;	// The string value of the token (e.g., the actual word, operator, etc.)
typedef int		t_grammar_rule;

typedef t_list t_tokens;
typedef t_node t_tokens_item;
typedef struct s_token
{
	t_token_type		type;
	t_grammar_rule		rule;	// The grammar rule that this token matches (used for parsing)
	t_raw_string_ptr	start;	// The raw string from the input that corresponds to this token (before any processing)
	t_token_value		value;
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
	size_t			index;			// Current position in the input string
	t_raw_string	input;			// The original input string being lexed
	t_state			state;
	t_tokens		token_stream;	// List of tokens generated by the lexer
	t_heredoc_stack	heredoc_stack;	// Non-NULL if currently lexing a heredoc delimiter
}	t_lexer;

void		lex_line(t_lexer *lexer, t_raw_string input);

t_token		*get_next_token(t_lexer *lexer);
t_token		*peek_token(t_lexer *lexer, size_t offset);

void		read_heredoc_stack();
t_file_path	add_heredoc_to_stack(t_token_value delimiter, bool strip_tabs);

#endif
