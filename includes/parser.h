#ifndef PARSER_H
# define PARSER_H

# include <stddef.h>

/* ************************************************************************* */
/*                                  SYMBOLS                                  */
/* ************************************************************************* */


typedef enum e_symbol_id
{
	// Terminals (ACTION table entries)
	SYM_TOKEN,			// Not classified by the lexer
	SYM_WORD,			// Pre-classified by the parser
	SYM_NEWLINE,		// `\n`
	// [...] TODO
	SYM_EOF,			// End of input
	// ----------------------------------------------------
	// Non-terminals (GOTO table entries)
	SYM_PROGRAM,
	SYM_SIMPLE_COMMAND,
	SYM_CMD_NAME,
	SYM_CMD_SUFFIX,
	// [...] TODO
	SYM_ERROR,
	// ----------------------------------------------------
	SYM_COUNT
}	t_symbol_id;

# define SYM_TERMINAL_MAX		SYM_EOF
# define SYM_NON_TERMINAL_MIN	SYM_PROGRAM
# define SYM_NON_TERMINAL_MAX	SYM_ERROR

/* ************************************************************************* */
/*                                   AST                                     */
/* ************************************************************************* */

typedef struct s_ast_node
{
	// TODO
}	t_ast_node;

/* ************************************************************************* */
/*                                  STACK                                    */
/* ************************************************************************* */

typedef struct s_stack_item
{
	t_symbol_id	symbol;
	int			state;
	t_ast_node	*ast_node;	// borrowed
}	t_stack_item;

typedef struct s_stack
{
	t_stack_item	*items;
	size_t			cap;
	size_t			len;
}	t_stack;

/* ************************************************************************* */
/*                                  RULES                                    */
/* ************************************************************************* */

typedef struct s_rule
{
	// TODO
}	t_rule;

#endif
