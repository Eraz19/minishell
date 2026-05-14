#ifndef PARAMS_H
# define PARAMS_H

# include "variables.h"
# include "options.h"
# include "specials.h"
# include "positionals.h"
# include "functions.h"

typedef struct s_params
{
	void				*parent_shell;	// (internal)
	const char			*name;			// (internal)
	t_var_list			variables;		// $<var_name>
	t_option			options;		// $-
	t_specials			specials;		// $0 $$ $! $?
	t_positionals_stack	positionals;	// $@ $* $# $<n>
	t_fun_list			functions;		// (internal)
}	t_params;

void	params_init(t_params *params);
t_error	params_load(t_params *params, int argc, char **argv, char **envp);
void	params_free(t_params *params);

#endif
