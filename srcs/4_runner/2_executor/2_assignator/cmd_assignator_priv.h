#ifndef CMD_ASSIGNATOR_PRIV_H
# define CMD_ASSIGNATOR_PRIV_H

# include "error.h"
# include "token.h"
# include "expander.h"
# include "cmd_resolution_type.h"

t_error	cmd_assignment_check(const t_token *token);
t_error	cmd_assignment_expand(
			const t_token *token,
			t_exp_flag flags,
			t_string *out_expanded);
t_error	cmd_assignment_process(
			t_cmd_type cmd_type,
			const t_token *token,
			t_string *expanded,
			t_vector *out_envp);

#endif
