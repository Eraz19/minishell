/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 16:05:23 by adouieb           #+#    #+#             */
/*   Updated: 2026/04/20 20:31:43 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

/*
EXP_NONE
EXP_VAR			- Variable expansion: $VAR or ${VAR}
EXP_TILDE		- Tilde expansion: ~/path
EXP_WILDCARD	- Pathname expansion: *.c, ?, [a-z]
EXP_CMD_SUB		- Command substitution: $(ls) or `ls`
EXP_ARITHMETIC	- Arithmetic: $((1 + 1))
EXP_BRACE		- Brace expansion: {a,b}c -> ac bc
EXP_PARAM		- Parameter expansion: ${VAR:-default}, ${VAR%suffix} etc
EXP_QUOTED		- Indicates the word was inside "" or ''
EXP_DQUOTED		- Specifically inside double quotes
*/
typedef enum e_expand_type
{
    EXP_NONE            = 0,
    EXP_VAR             = 1 << 0,
    EXP_TILDE           = 1 << 1,
    EXP_WILDCARD        = 1 << 2, 
    EXP_CMD_SUB         = 1 << 3, 
    EXP_ARITHMETIC      = 1 << 4, 
    EXP_BRACE           = 1 << 5, 
    EXP_PARAM           = 1 << 6, 
    EXP_QUOTED          = 1 << 7, 
    EXP_DQUOTED         = 1 << 8  
}   t_expand_type;

/*
Tells the parser how to treat it in the grammar
TOKEN_CAT_LITERAL 		- The "meat" of the command (program names, arguments,
							or raw numbers for file descriptors)
TOKEN_CAT_REDIRECTION 	- Tell the shell to move data between files and file
							descriptors
TOKEN_CAT_OPERATOR 		- Manipulate the "plumbing" of the command pipeline
TOKEN_CAT_CONTROL 		- Define the flow of execution—deciding if or when a
							command runs
TOKEN_CAT_GROUPING		- Create "blocks" of logic
TOKEN_CAT_END			- Marks the end of the input or a file
TOKEN_CAT_ERROR			- Signal that it encountered a character it doesn't
							recognize or a syntax error
*/
typedef enum e_token_category
{
	TOKEN_CAT_LITERAL,
	TOKEN_CAT_REDIRECTION,
	TOKEN_CAT_OPERATOR,
	TOKEN_CAT_CONTROL,
	TOKEN_CAT_GROUPING,
	TOKEN_CAT_END,
	TOKEN_CAT_ERROR
}	t_token_category;

/*
Tells exactly to the parser what the character is
// Category: Literal
TOKEN_WORD					- Standard words (ls, -la, filename)
TOKEN_IO_NUMBER				- Digit(s) prefixing a redirection (the 2 in 2>)
// Category: Redirection
TOKEN_REDIR_IN			<	- RedirectS file to standard input
TOKEN_REDIR_OUT			>	- RedirectS standard output to a file (truncate)
TOKEN_APPEND			>>	- RedirectS standard output to a file (append)
TOKEN_HEREDOC			<<	- Reads input until a delimiter string is reached
TOKEN_REDIR_IN_OUT		<>	- Opens a file for both reading and writing
TOKEN_DUP_IN			<&	- Duplicates an input file descriptor
TOKEN_DUP_OUT			>&	- Duplicates an output file descriptor
TOKEN_CLOBBER			>|	- Overwrites a file even if noclobber is on
TOKEN_HERE_STRING		<<<	- Passes the following word as standard input
TOKEN_HEREDOC_STRIP		<<-	- Heredoc that strips leading tabs from the input
TOKEN_REDIR_ERR_OUT		&>	- Redirects both stdout and stderr (shorthand)
TOKEN_APPEND_ERR_OUT	&>>	- Appends both stdout and stderr (shorthand)
// Category: Operator
TOKEN_PIPE				|	- Passes output of one command to input of next
TOKEN_PIPE_STDERR		|&	- Pipes both stdout and stderr to the next command
TOKEN_NEGATION			!	- Inverts the logical exit status of the command
// Category: Control
TOKEN_AND				&&	- Executes next command only if previous succeeded
TOKEN_OR				||	- Executes next command only if previous failed
TOKEN_BACKGROUND		&	- Runs the command in a background process
TOKEN_SEQUENCE			;	- Separates commands to run one after another
TOKEN_CASE_BREAK		;;	- Ends a clause in a case conditional block
TOKEN_NEWLINE			\n	- Acts as a command terminator, similar to ;
// Category: Grouping
TOKEN_SUBSHELL_START	(	- Opens a subshell environment
TOKEN_SUBSHELL_END		)	- Closes a subshell environment
TOKEN_BLOCK_START		{	- Starts a command group in the current shell
TOKEN_BLOCK_END			}	- Ends a command group in the current shell
// Special
TOKEN_EOF					- Marks the end of the input or a file
TOKEN_ERROR					- Signal that it encountered a character it doesn't
								recognize or a syntax error
*/
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_IO_NUMBER,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_REDIR_IN_OUT,
	TOKEN_DUP_IN,
	TOKEN_DUP_OUT,
	TOKEN_CLOBBER,
	TOKEN_HERE_STRING,
	TOKEN_HEREDOC_STRIP,
	TOKEN_REDIR_ERR_OUT,
	TOKEN_APPEND_ERR_OUT,
	TOKEN_PIPE,
	TOKEN_PIPE_STDERR,
	TOKEN_NEGATION,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_BACKGROUND,
	TOKEN_SEQUENCE,
	TOKEN_CASE_BREAK,
	TOKEN_NEWLINE,
	TOKEN_SUBSHELL_START,
	TOKEN_SUBSHELL_END,
	TOKEN_BLOCK_START,
	TOKEN_BLOCK_END,
	TOKEN_EOF,
	TOKEN_ERROR
}	t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	t_token_category	category;
	t_expand_type		expand_type;
}	t_token;

typedef t_token*	t_tokens;

#endif
