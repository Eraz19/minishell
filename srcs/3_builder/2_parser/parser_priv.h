#ifndef PARSER_PRIV_H
# define PARSER_PRIV_H

# include "builder.h"
# include <stdbool.h>

/* ************************************************************************* */
/*                                   ERROR                                   */
/* ************************************************************************* */

t_error	parser_internal_error(void);
t_error	parser_invalid_syntax(void);

/* ************************************************************************* */
/*                                LIFE CYCLE                                 */
/* ************************************************************************* */

void	parser_init(t_parser *parser);
void	parser_free_token(void *token);
void	parser_free_stack_item(void *raw_item);
void	parser_free(t_parser *parser);

/* ************************************************************************* */
/*                                  SYMBOLS                                  */
/* ************************************************************************* */

t_error	parser_read_next_symbol(t_parser *parser);

/* ************************************************************************* */
/*                                   STACK                                   */
/* ************************************************************************* */

# define STACK_INITIAL_CAP	16

void			parser_stack_init(t_stack *stack);
t_stack_item	*parser_stack_top(t_stack *stack);
bool			parser_stack_push(t_stack *stack, t_stack_item *item);
bool			parser_stack_pop(t_stack *stack, t_stack_item *dst);
void			parser_stack_free(t_stack *stack);

/* ************************************************************************* */
/*                                  ACTIONS                                  */
/* ************************************************************************* */

t_error	parser_shift(t_parser *parser, size_t lr_state_id);
t_error	parser_reduce(t_parser *parser, t_lr_machine *machine, size_t rule_id);

/* ************************************************************************* */
/*                                    CST                                    */
/* ************************************************************************* */

t_error	parser_cst_node_new(
	t_stack_item *lhs,
	t_stack_item *rhs,
	size_t item_count,
	t_cst_node **dst);
void	parser_cst_node_free(t_cst_node **node);

/* ************************************************************************* */
/*                                   DEBUG                                   */
/* ************************************************************************* */

#include "token.h"

const char	*token_type_to_string(t_token_type token_type);
const char	*symbol_to_string(t_symbol symbol);
const char	*action_type_to_string(t_action_type action_type);

#endif
