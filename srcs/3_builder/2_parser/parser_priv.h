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

void	parser_stack_item_free(void *raw_item);

/* ************************************************************************* */
/*                                    READ                                   */
/* ************************************************************************* */

t_error	parser_read_next_symbol(t_parser *parser);

/**
 * @brief Reads the pending here-document bodies when the lookahead is
 *        the line's newline (POSIX 2.7.4): one body per recorded
 *        @c io_here node, in reduction order, each stored on its node's
 *        @c heredoc_body; a no-op on any other lookahead.
 *
 * @param parser Already initialized parser state (borrowed).
 * @return From the scanner, fully qualified: @c ERR_POSIX_SYNTAX
 *         (printed with the delimiter) when the input ends before a
 *         delimiter line; @c ERR_POSIX_EXPANSION (printed) from a
 *         delimiter's quote removal; @c ERR_INTERRUPTED; @c ERR_LIBC
 *         (printed); @c ERR_INTERNAL (printed); @c ERR_NO on success or
 *         when nothing is pending.
 */
t_error	parser_read_heredoc(t_parser *parser);

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
