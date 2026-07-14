#ifndef CST_TYPE_H
# define CST_TYPE_H

# include "libft.h"
# include "symbols_type.h"
# include "rules__type.h"
# include <stddef.h>

typedef void	(*t_cst_free_data)(void *data);

/**
 * @struct s_cst_node
 * @brief One node of the concrete syntax tree built by the parser.
 *
 * @var s_cst_node::symbol Grammar symbol the node reduces to.
 * @var s_cst_node::rule_id Grammar rule of the reduction.
 * @var s_cst_node::tokens_start_id First token of the node's span in the
 *                                  parser token pool.
 * @var s_cst_node::tokens_count Number of tokens in the span.
 * @var s_cst_node::children Array of the reduced children, in grammar
 *                           order (owned).
 * @var s_cst_node::child_count Number of children.
 * @var s_cst_node::heredoc_body Body text of an @c io_here node, read by
 *                               @c parser_read_heredoc at the line's
 *                               newline; empty for every other node
 *                               (owned).
 */
typedef struct s_cst_node
{
	t_symbol			symbol;
	t_rule_id			rule_id;
	size_t				tokens_start_id;
	size_t				tokens_count;
	struct s_cst_node	**children;
	size_t				child_count;
	t_string			heredoc_body;
}	t_cst_node;

#endif
