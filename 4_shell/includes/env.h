#ifndef ENV_H
# define ENV_H

# include "variables.h"
# include "options.h"
# include "specials.h"
# include "positionals.h"
# include "functions.h"
# include "process.h"
# include "cmd_cache.h"
# include "fd.h"
# include "alias.h"

typedef struct s_params
{
	const char			*name;
	t_var_list			variables;
	t_option			options;
	t_specials			specials;
	t_positionals_stack	positionals_stack;
	t_functions			functions;
	t_process_table		processes;
	t_cmd_cache			cmd_cache;
	t_fd_manager		fd_manager;
	t_alias				alias;
}	t_params;

typedef enum e_env_print_mode
{
	ENV_PRINT_EXPORT,
	ENV_PRINT_READONLY,
	ENV_PRINT_SET,
	ENV_PRINT_ALIAS
}	t_env_print_mode;

/* ************************************************************************* */
/*                                LIFE CYCLE                                 */
/* ************************************************************************* */

void	env_init(t_params *params);
void	env_init_subshell(t_params *params, bool async_no_job_ctrl);
t_error	env_load(t_params *params, int argc, char **argv, char **envp);
void	env_clear(t_params *params);
void	env_free(t_params *params);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

bool	env_alias_is_forbidden(const t_string *name);
t_error	env_build_envp(t_vector *dst_envp);
void	env_clear_forbidden_aliases(void);
t_error	env_get_cmd_cache(t_cmd_cache **out_cmd_cache_ptr);
t_error	env_get_function(const char *name, t_function **out);
t_error	env_get_last_status(int *out);
int		env_get_last_status_from(t_params *params);
t_error	env_get_fd_manager(t_fd_manager **out_fd_manager_ptr);
t_error	env_get(const t_string *name, t_string *dst);
t_error	env_get_alias(const t_string *name, const t_string **out_value);
t_error	env_get_from_const(const char *name, t_string *dst);
t_error	env_get_positionals(const t_positionals **dst);
t_error	env_get_source(const t_string **source);
t_error	env_is_readonly(const char *name, bool *out_is_readonly);
t_error	env_push_positionals(t_positionals *src);
void	env_pop_alias_from_stack(void);
t_error	env_pop_positionals(void);
t_error	env_print(t_env_print_mode mode);
t_error	env_print_one_alias(const char *name);
t_error	env_reap(void);
t_error	env_register_process(pid_t pid);
t_error	env_replace_positionals(t_positionals *src);
t_error	env_set_alias(const char *name, const char *value);
t_error	env_set_function(t_ast_function_def *function_def);
t_error	env_set_option(t_option option, bool on);
t_error	env_set_last_status(int value);
void	env_set_last_status_in(t_params *params, int value);
t_error	env_set_variable(
	const t_string *name,
	const t_string *value,
	bool export,
	bool readonly);
t_error	env_shift_positionals(size_t n);
void	env_stop_function(t_function **function);
t_error	env_unset_alias(const char *name);
void	env_unset_all_alias(void);
t_error	env_unset_function(const char *name);
t_error	env_unset_variable(const t_string *name);
t_error	env_wait(pid_t pid, int *status);
t_error	env_wait_all(int *status);

#endif
