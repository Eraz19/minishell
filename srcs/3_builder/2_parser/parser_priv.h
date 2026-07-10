#ifndef PARSER_PRIV_H
# define PARSER_PRIV_H

# include "parser_type.h"
# include "lr_machine_type.h"
# include "token.h"

/* ************************************************************************* */
/*                                   ERROR                                   */
/* ************************************************************************* */

t_error	parser_internal_error(t_error err);
t_error	parser_invalid_syntax(void);

/* ************************************************************************* */
/*                                LIFE CYCLE                                 */
/* ************************************************************************* */

void	parser_init(t_parser *parser);
void	parser_free_stack_item(void *raw_item);
void	parser_free(t_parser *parser);

/* ************************************************************************* */
/*                                    READ                                   */
/* ************************************************************************* */

t_error	parser_read_next_symbol(t_parser *parser);
t_error	parser_read_heredoc(t_parser *parser);

/* ************************************************************************* */
/*                                   STACK                                   */
/* ************************************************************************* */

t_parser_stack_item	*parser_stack_top(const t_parser_stack *stack);

/* ************************************************************************* */
/*                                  ACTIONS                                  */
/* ************************************************************************* */

t_error	parser_shift(t_parser *parser, size_t lr_state_id);
t_error	parser_reduce(
			t_parser *parser,
			const t_lr_machine *machine,
			size_t rule_id);

/* ************************************************************************* */
/*                                   DEBUG                                   */
/* ************************************************************************* */

#include "token.h"

const char	*token_type_to_string(t_token_type token_type);
const char	*symbol_to_string(t_symbol symbol);
const char	*action_type_to_string(t_action_type action_type);

#endif
