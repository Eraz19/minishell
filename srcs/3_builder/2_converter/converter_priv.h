#ifndef CONVERTER_PRIV_H
# define CONVERTER_PRIV_H

# include "cst_type.h"
# include "parser_type.h"
# include "ast.h"
# include <stdbool.h>

/* ************************************************************************* */
/*                                CST_HELPERS                                */
/* ************************************************************************* */

t_token	*converter_get_token(
			const t_parser *parser,
			const t_cst_node *node,
			size_t node_token_id);

void	converter_take_token(
			t_parser *parser,
			const t_cst_node *node,
			size_t node_token_id,
			t_token *dst);

t_error	converter_transfer_token(
			t_parser *parser,
			const t_cst_node *node,
			size_t node_token_id,
			t_token_pool *dst);

/* ************************************************************************* */
/*                                REDIRECTION                                */
/* ************************************************************************* */

// input = io_redirect
t_error	convert_redirection(
			t_parser *parser,
			const t_cst_node *io_redirect,
			t_ast_redirection *out);

// input = io_redirect
t_error	convert_redirection_add(
			t_parser *parser,
			const t_cst_node *io_redirect,
			t_ast_redir_list *out);

			// input = redirect_list
t_error	convert_redirection_add_list(
			t_parser *parser,
			const t_cst_node *redirect_list,
			t_ast_redir_list *out);

/* ************************************************************************* */
/*                              SIMPLE_COMMAND                               */
/* ************************************************************************* */

// input = simple_command
t_error	convert_simple_command(
			t_parser *parser,
			const t_cst_node *simple_command,
			t_ast_scmd *out);

/* ************************************************************************* */
/*                                 PIPELINE                                  */
/* ************************************************************************* */

// input = pipeline
t_error	convert_pipeline(
			t_parser *parser,
			const t_cst_node *pipeline,
			t_ast_pipeline *out);

/* ************************************************************************* */
/*                                  AND_OR                                   */
/* ************************************************************************* */

// input = and_or
t_error	convert_and_or(
			t_parser *parser,
			const t_cst_node *and_or,
			t_ast_and_or *out);

/* ************************************************************************* */
/*                                   LIST                                    */
/* ************************************************************************* */

// input = subshell / compound_list / complete_command
t_error	convert_list(
			t_parser *parser,
			const t_cst_node *node,
			t_ast_list *out);

// input = subshell / compound_list / complete_command
t_error	convert_list_add(
			t_parser *parser,
			const t_cst_node *node,
			t_ast_list *out);

/* ************************************************************************* */
/*                                    IF                                     */
/* ************************************************************************* */

// input = if_clause
t_error	convert_if(
			t_parser *parser,
			const t_cst_node *if_node,
			t_ast_if *out);

/* ************************************************************************* */
/*                                    FOR                                    */
/* ************************************************************************* */

// input = for_clause
t_error	convert_for(
			t_parser *parser,
			const t_cst_node *for_clause,
			t_ast_for *out);

/* ************************************************************************* */
/*                                   LOOP                                    */
/* ************************************************************************* */

// input = while_clause / until_clause
t_error	convert_loop(
			t_parser *parser,
			const t_cst_node *loop,
			t_ast_loop *out);

/* ************************************************************************* */
/*                                   CASE                                    */
/* ************************************************************************* */

// input = case_clause
t_error	convert_case(
			t_parser *parser,
			const t_cst_node *case_clause,
			t_ast_case *out);

/* ************************************************************************* */
/*                                 FUNCTION                                  */
/* ************************************************************************* */

// input = function_definition
t_error	convert_function(
			t_parser *parser,
			const t_cst_node *function_definition,
			t_ast_function_def *out);

/* ************************************************************************* */
/*                                  COMMAND                                  */
/* ************************************************************************* */

// input = command
t_error	convert_command(
			t_parser *parser,
			const t_cst_node *command,
			t_ast_command *out);

// input = compound_command
t_error	convert_compound_command(
			t_parser *parser,
			const t_cst_node *compound_command,
			t_ast_command *out);

#endif
