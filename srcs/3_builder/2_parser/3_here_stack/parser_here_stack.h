#ifndef PARSER_HERE_STACK_H
# define PARSER_HERE_STACK_H

# include "cst_type.h"
# include "parser_here_stack_type.h"

/** @defgroup parser_here_stack Parser here stack
 *  @brief Pending here-document nodes of the command line being parsed.
 *
 *  Each reduced @c io_here node is pushed in reduction order; when the
 *  newline ending the line is reached, @c parser_read_heredoc reads one
 *  body per entry, in order (POSIX 2.7.4), then the stack is cleared.
 *  The nodes belong to the syntax tree: the stack never frees them.
 */

/* ************************************************************************* */
/*                                LIFE_CYCLE                                 */
/* ************************************************************************* */

/**
 * @ingroup parser_here_stack
 * @brief Initializes @p stack as an empty stack of node pointers.
 *
 * @param stack Stack initialized by the function (borrowed).
 */
void	parser_here_stack_init(t_parser_here_stack *stack);

/**
 * @ingroup parser_here_stack
 * @brief Releases the storage of @p stack; the recorded nodes are left
 *        to the syntax tree.
 *
 * @param stack Already initialized stack (borrowed).
 */
void	parser_here_stack_free(t_parser_here_stack *stack);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup parser_here_stack
 * @brief Empties @p stack, keeping its storage; the recorded nodes are
 *        left to the syntax tree.
 *
 * @param stack Already initialized stack (borrowed).
 */
void	parser_here_stack_clear(t_parser_here_stack *stack);

/**
 * @ingroup parser_here_stack
 * @brief Fetches the @p i -th recorded node, in push order.
 *
 * @param stack Already initialized stack (borrowed, read-only).
 * @param i Index of the node.
 * @return The node, or @c NULL when @p stack is empty; @p stack keeps
 *         ownership (borrowed).
 */
t_cst_node	*parser_here_stack_get(const t_parser_here_stack *stack, size_t i);

#endif
