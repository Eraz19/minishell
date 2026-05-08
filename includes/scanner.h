/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 16:05:23 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/07 16:35:27 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCANNER_H
# define SCANNER_H

# include "libft.h"

// ---------- Token ----------

typedef enum e_token_type
{
	TOKEN,			// - Non-specific token (WORD, NAME, ASSIGNMENT_WORD, ...) that doesn't fit into other categories
	// control
	NEWLINE,		// `\n` - command separator
	SCOLON,			// `;`- command separator
	AMPERSAND,		// `&` - background command separator
	DSEMI,			// `;;` - case separator
	SEMI_AND,		// `;&` - case fallthrough
	AND_IF,			// `&&` - logical AND operator
	OR_IF,			// `||` - logical OR operator
	PIPE,			// `|` - pipeline operator
	LPARENTHESIS,	// `(` - subshell start
	RPARENTHESIS,	// `)` - subshell end
	EOF,			// \<EOF> - end of input	
	// redirection
	IO_NUMBER,		// `[0-9]+` - file descriptor for redirection
	LESSAND,		// `<&` - duplicate input file descriptor
	GREATAND,		// `>&` - duplicate output file descriptor
	LESS,			// `<` - input redirection
	GREAT,			// `>` - output redirection
	CLOBBER,		// `>|` - output redirection with clobbering (force overwrite)
	LESSGREAT,		// `<>` - input/output redirection
	DGREAT,			// `>>` - append redirection
	DLESS,			// `<<` - here document
	DLESSDASH		// `<<-` - here document with tab stripping
}	t_token_type;

typedef t_buff	t_token_value;	// The string value of the token (e.g., the actual word, operator, etc.)

typedef struct s_token
{
	t_token_type	type;	// Indicates which type of token this is
	t_token_value	value;
	size_t			offset;	// Offset of the token start in the original input (for error output)
}	t_token;

// ---------- Lexer state ----------

typedef enum e_quote_mode
{
	NONE_,		// Not in a quote
	SINGLE_,	// In a single quote
	DOUBLE_,	// In a double quote
}	t_quote_mode;

typedef enum e_lexer_ctx
{
	NONE,
	SQUOTE,    // '
	DQUOTE,    // "
	BACKTICK,  // `
	CMD_SUB,   // $(
	ARITH,     // $((
	PARAM,     // ${
}   t_lexer_ctx_type;

typedef struct s_lexer_ctx
{
	t_lexer_ctx_type	type;
	int					nesting_depth;
}	t_lexer_ctx;

typedef struct s_ctx_stack
{
	size_t		len;
	size_t		size;
	t_lexer_ctx	*data;
}	t_ctx_stack;

typedef struct s_lexer
{
	size_t		i;
	t_ctx_stack	ctx;
	char		*input;
	char		*script_path;
}	t_lexer;

// ------------ Scanner API ------------

void	free_token(t_token **token_ptr);

t_token	*get_next_token(t_lexer *lexer);

#endif
