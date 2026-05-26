/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _token.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 16:23:48 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/19 16:31:47 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _TOKEN_H
# define _TOKEN_H

# include "libft.h"
# include "../_lexer.h"

// Forward declaration
typedef struct s_operator_args	t_operator_args;

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
	char			*input_ptr;
}	t_token;

void	free_token(t_token **token_ptr);
t_token	*create_word_token(t_lexer *lexer, size_t i);
t_token	*create_operator_token(t_lexer *lexer, );
t_token	*create_token(char *content, size_t offset, t_token_type type);

// For testing purposes

void	DEBUG_print_token(t_token *token);
char	*DEBUG_token_type_stringify(t_token_type type);
bool	DEBUG_is_token_equal(t_token token1, t_token token2);

#endif
