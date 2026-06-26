#ifndef EXPANDER_H
# define EXPANDER_H

# include "error.h"
# include "context.h"

/* ---------- TODO: private API ---------- */

typedef enum e_expander_role
{
	EXPANDER_NORMAL,
	EXPANDER_ASSIGNMENT,
	EXPANDER_REDIRECT_FILENAME,
	EXPANDER_HEREDOC_DELIMITER,
	EXPANDER_HEREDOC_BODY
}	t_expander_role;

typedef	struct s_expander_args
{
	t_buff			value;
	t_expander_role role;
	t_context_stack *contexts;
}	t_expander_args;

t_error	expander_expand_word(char ***expansion, t_expander_args *args);

/* ---------- TODO: public API ---------- */

# include "token.h"

// out is a vector of t_buff
// t_error	expander_expand_word(const t_token *word, t_vector *out);

// out is a vector of t_buff
t_error	expander_expand_filename(const t_token *filename, t_vector *out);

t_error	expander_expand_heredoc_delim(const t_buff *heredoc_delim, t_buff *out);

t_error	expander_expand_heredoc_body(const t_buff *heredoc_file_path);

// VAR="$@" => VAR=" param_1 param_2 param_3 param_4"
t_error	expander_expand_assignment(const t_token *assignment, t_buff *out);

#endif
