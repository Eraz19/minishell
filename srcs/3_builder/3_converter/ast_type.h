#ifndef AST_TYPE_H
# define AST_TYPE_H

# include "libft.h"
# include "error.h"
# include <stddef.h>

/* ************************************************************************* */
/*                                 REDIRECTOR                                */
/* ************************************************************************* */

/* ---------- REDIRECT NODE (IN CONVERTER) ---------- */

typedef enum e_ast_redir_op
{
    AST_REDIR_READ,          // <			SYM_LESS
    AST_REDIR_HEREDOC,       // << / <<-	SYM_DLESS / SYM_DLESSDASH
    AST_REDIR_DUP_READ,      // <&			SYM_LESSAND
    AST_REDIR_WRITE,         // >			SYM_GREAT
    AST_REDIR_APPEND,        // >>			SYM_DGREAT
    AST_REDIR_DUP_WRITE,     // >&			SYM_GREATAND
    AST_REDIR_CLOBBER,       // >|			SYM_CLOBBER
    AST_REDIR_READ_WRITE,    // <>			SYM_LESSGREAT
	AST_REDIR_COUNT
}	t_ast_redir_op;

typedef struct s_ast_redirection
{
	t_ast_redir_op	operation;
	int				fd;					// pre-computed fd
	char			*word;				// raw token content / heredoc file path
	bool			expand_heredoc_body;
}	t_ast_redirection;

typedef t_vector	t_ast_redir_list;	// vector of t_ast_redirection

/* ---------- REDIRECTOR MODULE (IN RUNNER) ---------- */

typedef struct s_redir_frame
{
	t_vector	fds;		// vector of int
	t_vector	backup_fds;	// vector of int (-1 if fd was closed before redirection)
}	t_redir_frame;

typedef t_vector	t_redir_stack;

void	redirect_init(t_redir_stack *stack);
t_error	redirect_push(t_redir_stack *stack, t_ast_redir_list *redirections);
t_error	redirect_pop(t_redir_stack *stack);
t_error	redirect_restore(t_redir_stack *stack);
void	redirect_free(t_redir_stack *stack);

/* ************************************************************************* */
/*                                   EXECUTOR                                */
/* ************************************************************************* */

/* ---------- SIMPLE COMMAND NODE (IN CONVERTER) ---------- */

typedef struct s_ast_simple_command
{
	t_vector	assignments;	// vector of char *
	t_vector	words;			// vector of char *
}	t_ast_simple_command;

/* ---------- EXECUTOR (IN RUNNER) ---------- */

t_error	execute(t_ast_simple_command *cmd, t_ast_redir_list *redirections, int *exit_status);

/* ************************************************************************* */
/*                                    WALKER                                 */
/* ************************************************************************* */

/* ---------- LIST NODE (IN CONVERTER) ---------- */

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
	t_vector	and_or;				// vector of t_ast_and_or
	t_vector	async;				// vector of bool (& => true)
	bool		subshell;
}	t_ast_list;

/* ---------- CONTROL NODES (IN CONVERTER) ---------- */

typedef struct s_ast_if
{
	t_vector	conditions;			// vector of t_ast_list
	t_vector	bodies;				// vector of t_ast_list
	bool		has_else;
	t_ast_list	else_body;
}	t_ast_if;

typedef struct s_ast_for
{
	char		*item_var_name;
	t_vector	words;				// vector of char * (set to ["@"] if input doesn't contain)
	t_ast_list	body;
}	t_ast_for;

typedef struct s_ast_loop
{
	t_ast_list		condition;
	bool			condition_must_be_true;	// While = true | Until = false
	t_ast_list		body;
}	t_ast_loop;

typedef struct s_ast_case
{
	char		*word;				// raw tested word
	t_vector	patterns;			// vector of t_vector(char *)
	t_vector	bodies;				// vector of t_ast_list
	t_vector	fallthrough;		// vector of bool
}	t_ast_case;

typedef struct s_ast_command	t_ast_command;

typedef struct s_ast_function_def
{
	char			*name;
	t_ast_command	*body;
}	t_ast_function_def;

/* ---------- MAIN COMMAND (IN CONVERTER) ---------- */

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
	t_ast_simple_command	simple;
	t_ast_list				list;
	t_ast_if				if_clause;
	t_ast_for				for_clause;
	t_ast_loop				loop;
	t_ast_case				case_clause;
	t_ast_function_def		function_def;
}	t_ast_command_data;

typedef struct s_ast_command
{
	t_ast_command_type	type;
	t_ast_command_data	data;
	t_vector			redirs;		// vector of t_ast_redirection
}	t_ast_command;

typedef t_ast_list	t_ast_root;

/* ---------- WALKER (IN RUNNER) ---------- */

/* --- LIST WALKER (INTERNAL) --- */
t_error	walk_command(t_ast_command *command);
t_error	walk_pipeline(t_ast_pipeline *pipeline);
t_error	walk_and_or(t_ast_and_or *and_or);

/* --- LIST WALKER (PRIVATE) --- */
t_error	walk_list(t_ast_list *list);

/* --- CONTROL WALKER (PRIVATE) --- */
t_error	walk_if(t_ast_if *if_clause);
t_error	walk_for(t_ast_for *for_clause);
t_error	walk_loop(t_ast_loop *loop);
t_error	walk_case(t_ast_case *case_clause);
t_error	walk_func(t_ast_function_def *function_def);

/* --- MAIN WALKER (PRIVATE) --- */
t_error walk_ast(t_ast_root *root_ast_node);

#endif
