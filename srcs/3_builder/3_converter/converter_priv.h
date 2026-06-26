#ifndef CONVERTER_PRIV_H
# define CONVERTER_PRIV_H

# include "libft.h"
# include "cst_type.h"
# include "ast_type.h"
# include <stdbool.h>

/* ************************************************************************* */
/*                                CST_HELPERS                                */
/* ************************************************************************* */

// @ret ERR_INDEX_OUT_OF_BOUND
t_error	converter_get_token(
	t_parser *parser,
	t_cst_node *node,
	size_t node_token_id,
	t_token **dst);

// @ret ERR_INDEX_OUT_OF_BOUND
t_error	converter_get_buff(
	t_parser *parser,
	t_cst_node *node,
	size_t node_token_id,
	t_buff **dst);

// @ret ERR_INDEX_OUT_OF_BOUND / ERR_LIBC
t_error	converter_dup_buff(
	t_parser *parser,
	t_cst_node *node,
	size_t node_token_id,
	t_buff *dst);

// @ret ERR_INDEX_OUT_OF_BOUND / ERR_LIBC
t_error	converter_get_string(
	t_parser *parser,
	t_cst_node *node,
	size_t node_token_id,
	char **dst);

/* ************************************************************************* */
/*                                REDIRECTION                                */
/* ************************************************************************* */

void	ast_redirection_init(t_ast_redirection *redirection);
// input = io_redirect
t_error	convert_redirection(
	t_parser *parser,
	t_cst_node *io_redirect,
	t_ast_redirection *out);
void	ast_redirection_free(void *redirection);

void	ast_redir_list_init(t_ast_redir_list *redir_list);
// input = io_redirect
t_error	convert_redirection_add(
	t_parser *parser,
	t_cst_node *io_redirect,
	t_ast_redir_list *out);
// input = redirect_list
t_error	convert_redirection_add_list(
	t_parser *parser,
	t_cst_node *redirect_list,
	t_ast_redir_list *out);
void	ast_redir_list_free(t_ast_redir_list *redir_list);

/* ************************************************************************* */
/*                              SIMPLE_COMMAND                               */
/* ************************************************************************* */

void	ast_simple_command_init(t_ast_simple_command *simple_command);
// input = simple_command
t_error	convert_simple_command(
	t_parser *parser,
	t_cst_node *simple_command,
	t_ast_simple_command *out);
void	ast_simple_command_free(void *simple_command);

/* ************************************************************************* */
/*                                 PIPELINE                                  */
/* ************************************************************************* */

void	ast_pipeline_init(t_ast_pipeline *pipeline);
// input = pipeline
t_error	convert_pipeline(
	t_parser *parser,
	t_cst_node *pipeline,
	t_ast_pipeline *out);
void	ast_pipeline_free(void *pipeline);

/* ************************************************************************* */
/*                                  AND_OR                                   */
/* ************************************************************************* */

void	ast_and_or_init(t_ast_and_or *and_or);
// input = and_or
t_error	convert_and_or(
	t_parser *parser,
	t_cst_node *and_or,
	t_ast_and_or *out);
void	ast_and_or_free(void *and_or);

/* ************************************************************************* */
/*                                   LIST                                    */
/* ************************************************************************* */

void	ast_list_init(t_ast_list *list);
// input = subshell / compound_list / complete_command
t_error	convert_list(
	t_parser *parser,
	t_cst_node *node,
	t_ast_list *out);
// input = subshell / compound_list / complete_command
t_error	convert_list_add(
	t_parser *parser,
	t_cst_node *node,
	t_ast_list *out);
void	ast_list_free(void *list);

/* ************************************************************************* */
/*                                    IF                                     */
/* ************************************************************************* */

void	ast_if_init(t_ast_if *if_node);
// input = if_clause
t_error	convert_if(
	t_parser *parser,
	t_cst_node *if_node,
	t_ast_if *out);
void	ast_if_free(t_ast_if *if_node);

/* ************************************************************************* */
/*                                    FOR                                    */
/* ************************************************************************* */

void	ast_for_init(t_ast_for *for_node);
// input = for_clause
t_error	convert_for(
	t_parser *parser,
	t_cst_node *for_clause,
	t_ast_for *out);
void	ast_for_free(t_ast_for *for_node);

/* ************************************************************************* */
/*                                   LOOP                                    */
/* ************************************************************************* */

void	ast_loop_init(t_ast_loop *loop);
// input = while_clause / until_clause
t_error	convert_loop(
	t_parser *parser,
	t_cst_node *loop,
	t_ast_loop *out);
void	ast_loop_free(t_ast_loop *loop);

/* ************************************************************************* */
/*                                   CASE                                    */
/* ************************************************************************* */

void	ast_case_init(t_ast_case *case_node);
// input = case_clause
t_error	convert_case(
	t_parser *parser,
	t_cst_node *case_clause,
	t_ast_case *out);
void	ast_case_free(t_ast_case *case_node);

/* ************************************************************************* */
/*                                 FUNCTION                                  */
/* ************************************************************************* */

void	ast_function_def_init(t_ast_function_def *function_def);
// input = function_definition
t_error	convert_function(
	t_parser *parser,
	t_cst_node *function_definition,
	t_ast_function_def *out);
void	ast_function_def_free(t_ast_function_def *function_def);

/* ************************************************************************* */
/*                                  COMMAND                                  */
/* ************************************************************************* */

void	ast_command_init(t_ast_command *command);
// input = command
t_error	convert_command(
	t_parser *parser,
	t_cst_node *command,
	t_ast_command *out);
// input = compound_command
t_error	convert_compound_command(
	t_parser *parser,
	t_cst_node *compound_command,
	t_ast_command *out);
void	ast_command_free(void *command);

/* ************************************************************************* */
/*                                   ROOT                                    */
/* ************************************************************************* */

void	ast_root_init(t_ast_root *root);

#endif
