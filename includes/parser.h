#ifndef PARSER_H
# define PARSER_H

# include "libft.h"



typedef struct s_ast_ctx
{
	// TODO
}	t_ast_ctx;

typedef enum e_reserved_word
{
	RW_BANG,		// !
	RW_OPEN_BR,		// {
	RW_CLOSE_BR,	// }
	RW_IF,			// if
	RW_THEN,		// then
	RW_ELSE,		// else
	RW_ELIF,		// elif
	RW_FI,			// fi
	RW_CASE,		// case
	RW_ESAC,		// esac
	RW_DO,			// do
	RW_DONE,		// done
	RW_WHILE,		// while
	RW_UNTIL,		// until
	RW_FOR,			// for
	RW_IN			// in
}	t_reserved_word;
/*
RESERVED WORDS REQUIREMENTS:
- Grammatical position:
	- 1st word of a command
	- 1st word following a [reserved word which is NOT `case`, `for`, `in`]
	- 3rd word of a [command starting by `case`] => only for `in`
	- 3rd word of a [command starting by `for`] => only for `in` and `do`
- token.type == TOKEN_WORD
- token.expand_type == EXPAND_ALL for all chars of the token
- strcmp(token.value, <reserved word>) == 0
---------
A COMMAND MUST START:
- First token
- After these tokens: `;`, `&`, `|`, `|&`, `&&`, `||`, `(`
- After these reserved words: `if`, `then`, `elif`, `else`, `do`, `while`, `until`, `!`, `{`
A COMMAND MAY START (depending on context):
- After these tokens: `;;`, `\n`, `)`
*/

// TODO: from tokenizer.h
typedef void	t_token;

typedef struct s_ast_node
{
	// TODO
}	t_ast_node;

typedef struct s_parser_token
{
	t_token			*token;
	t_btree_node	*ast_node;
	
}	t_parser_token;

// Public
bool	could_be_a_command_name(t_ast_ctx *state, char *token);
void	parse_token(t_ast_ctx *state, t_token *token);

// Private
void	shift(t_token *token);		// Add a token to the stack
t_token	*peek(size_t position);		// Get the token at <position> forward
bool	reduce(t_list tokens);		// Merge tokens into a new, higher-level, one

#endif
