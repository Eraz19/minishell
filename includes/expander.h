#ifndef EXPANDER_H
# define EXPANDER_H

# include "error.h"
# include "context.h"

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

#endif
