#ifndef AST_TYPE_H
# define AST_TYPE_H

# include "libft.h"
# include "token.h"
# include "ast_vector_type.h"
# include <stddef.h>

/* ************************************************************************* */
/*                                REDIRECTIONS                               */
/* ************************************************************************* */

typedef enum e_ast_redir_op
{
    AST_REDIR_HEREDOC,       // << / <<-	SYM_DLESS / SYM_DLESSDASH
    AST_REDIR_READ,          // <			SYM_LESS
    AST_REDIR_WRITE,         // >			SYM_GREAT
    AST_REDIR_CLOBBER,       // >|			SYM_CLOBBER
    AST_REDIR_APPEND,        // >>			SYM_DGREAT
    AST_REDIR_DUP_WRITE,     // >&			SYM_GREATAND
    AST_REDIR_DUP_READ,      // <&			SYM_LESSAND
    AST_REDIR_READ_WRITE,    // <>			SYM_LESSGREAT
	AST_REDIR_COUNT
}	t_ast_redir_op;

typedef struct s_ast_redirection
{
	t_ast_redir_op	operation;
	int				fd;
	t_token			word;
	t_string		heredoc_body;
	bool			expand_heredoc_body;
	bool			is_location;
	t_token			location;
}	t_ast_redirection;

// vector of t_ast_redirection
typedef t_vector	t_ast_redir_list;

/* ************************************************************************* */
/*                               SIMPLE COMMANDS                             */
/* ************************************************************************* */

typedef struct s_ast_scmd
{
	t_token_pool		assignments;
	t_token_pool		words;
	t_ast_redir_list	redirs;
}	t_ast_scmd;

/* ************************************************************************* */
/*                                    LISTS                                  */
/* ************************************************************************* */

typedef struct s_ast_pipeline
{
	t_vector	commands; 			// vector of t_ast_command
	bool		negated;
}	t_ast_pipeline;

typedef struct s_ast_and_or
{
	t_vector	pipelines;			// vector of t_ast_pipeline
	t_vector	next_on_success;	// vector of bool (&& (SYM_AND) = true, || (SYM_OR) = false)
}	t_ast_and_or;

typedef struct s_ast_list
{
	t_vector	and_ors;			// vector of t_ast_and_or
	t_vector	asyncs;				// vector of bool (& => true)
	bool		subshell;
}	t_ast_list;

/* ************************************************************************* */
/*                                   CONTROLS                                */
/* ************************************************************************* */

typedef struct s_ast_if
{
	t_vector	conditions;			// vector of t_ast_list
	t_vector	bodies;				// vector of t_ast_list
	bool		has_else;
	t_ast_list	else_body;
}	t_ast_if;

typedef struct s_ast_for
{
	t_token			var_name;
	t_token_pool	words;			// (set to ["@"] if input doesn't contain any word)
	t_ast_list		body;
}	t_ast_for;

typedef struct s_ast_loop
{
	t_ast_list		condition;
	bool			condition_must_be_true;	// While = true | Until = false
	t_ast_list		body;
}	t_ast_loop;

typedef struct s_ast_case
{
	t_token		word;				// raw tested word
	t_vector	patterns;			// vector of t_token_pool
	t_vector	bodies;				// vector of t_ast_list
	t_vector	fallthrough;		// vector of bool
}	t_ast_case;

typedef struct s_ast_command	t_ast_command;

typedef struct s_ast_function_def
{
	t_token				name;
	t_ast_command		*body;		// owned
	t_ast_redir_list	redirs;		// vector of t_ast_redirection
}	t_ast_function_def;

/* ************************************************************************* */
/*                                 MAIN COMMAND                              */
/* ************************************************************************* */

typedef enum e_ast_command_type
{
	AST_CMD_SIMPLE,
	AST_CMD_LIST,
	AST_CMD_IF,
	AST_CMD_FOR,
	AST_CMD_LOOP,
	AST_CMD_CASE,
	AST_CMD_FUNCTION_DEF,
	AST_CMD_TYPE_COUNT
}	t_ast_command_type;

typedef union u_ast_command_data
{
	t_ast_scmd			simple;
	t_ast_list			list;
	t_ast_if			if_clause;
	t_ast_for			for_clause;
	t_ast_loop			loop;
	t_ast_case			case_clause;
	t_ast_function_def	function_def;
}	t_ast_command_data;

typedef struct s_ast_command
{
	t_ast_command_type	type;
	t_ast_command_data	data;
	t_ast_redir_list	redirs;		// vector of t_ast_redirection
}	t_ast_command;

typedef t_ast_list	t_ast_root;

// Life cycle

void	ast_redirection_init(t_ast_redirection *redirection);
t_error	ast_redirection_dup(void *dst, const void *src);
void	ast_redirection_free(void *redirection);

void	ast_redir_list_init(t_ast_redir_list *redir_list);
t_error	ast_redir_list_dup(void *dst, const void *src);
void	ast_redir_list_free(t_ast_redir_list *redir_list);

void	ast_simple_command_init(t_ast_scmd *simple_command);
t_error	ast_simple_command_dup(void *dst, const void *src);
void	ast_simple_command_free(void *simple_command);

void	ast_pipeline_init(t_ast_pipeline *pipeline);
t_error	ast_pipeline_dup(void *dst, const void *src);
void	ast_pipeline_free(void *pipeline);

void	ast_and_or_init(t_ast_and_or *and_or);
t_error	ast_and_or_dup(void *dst, const void *src);
void	ast_and_or_free(void *and_or);

void	ast_list_init(t_ast_list *list);
t_error	ast_list_dup(void *dst, const void *src);
void	ast_list_free(void *list);

void	ast_if_init(t_ast_if *if_node);
t_error	ast_if_dup(void *dst, const void *src);
void	ast_if_free(t_ast_if *if_node);

void	ast_for_init(t_ast_for *for_node);
t_error	ast_for_dup(void *dst, const void *src);
void	ast_for_free(t_ast_for *for_node);

void	ast_loop_init(t_ast_loop *loop);
t_error	ast_loop_dup(void *dst, const void *src);
void	ast_loop_free(t_ast_loop *loop);

void	ast_case_init(t_ast_case *case_node);
t_error	ast_case_dup(void *dst, const void *src);
void	ast_case_free(t_ast_case *case_node);

void	ast_function_def_init(t_ast_function_def *function_def);
t_error	ast_function_def_dup(void *dst, const void *src);
void	ast_function_def_free(t_ast_function_def *function_def);

void	ast_command_init(t_ast_command *command);
t_error	ast_command_dup(void *dst, const void *src);
void	ast_command_free(void *command);

void	ast_root_init(t_ast_root *root);
t_error	ast_root_dup(void *dst, const void *src);
void	ast_root_free(t_ast_root *root);
void	ast_root_free_void(void *ast_root);

void	ast_vector_init(t_ast_vector *ast_vector);
t_error	ast_vector_dup(t_ast_vector *dst, const t_ast_vector *src);
// @warning returned pointer is valid ONLY until vector is realloc'd
// @ret ERR_INTERNAL if index is out of bound
t_error	ast_vector_get(
			const t_ast_vector *ast_vector,
			size_t index,
			t_ast_root **out_ast_root);
t_error	ast_vector_push(t_ast_vector *ast_vector, t_ast_root *ast_root);
void	ast_vector_free(t_ast_vector *ast_vector);

#endif
