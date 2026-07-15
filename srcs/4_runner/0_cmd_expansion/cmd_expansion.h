#ifndef CMD_EXPANSION_H
# define CMD_EXPANSION_H

# include "expander.h"

// vector of t_expansion (t_expansion is a vector of t_string)
typedef t_vector	t_cmd_expansions;

void	cmd_expansions_init(t_cmd_expansions *expansions);
void	cmd_expansions_free(t_cmd_expansions *expansions);

t_exp_flag	cmd_regular_expansion_flags(void);
t_exp_flag	cmd_assignment_expansion_flags(void);
t_exp_flag	cmd_case_expansion_flags(void);
t_exp_flag	cmd_redirection_expansion_flags(void);
t_exp_flag	cmd_heredoc_body_expansion_flags(void);

#endif
