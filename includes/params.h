#ifndef PARAMS_H
# define PARAMS_H

# include "variables.h"
# include "options.h"
# include "specials.h"
# include "positionals.h"

typedef struct s_params
{
	void				*parent_shell;	// (internal)
	const char			*name;			// (internal)
	t_var_list			variables;		// $<var_name>
	t_option			options;		// $-
	t_specials			specials;		// $0 $$ $! $?
	t_positionals_stack	positionals;	// $@ $* $# $<n>
}	t_params;

/* ************************************************************************* */
/*                                LIFE CYCLE                                 */
/* ************************************************************************* */

void	params_init(t_params *params);
t_error	params_load(t_params *params, int argc, char **argv, char **envp);
void	params_free(t_params *params);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

// @warning: caller owns *dst, he must free it (if not NULL).
// @ret ERR_NO / ERR_VAR_INVALID_NAME / ERR_VAR_NOT_FOUND / ERR_LIBC.
t_error	params_get(const char *name, char **dst);

// @ret ERR_NO / ERR_VAR_NOT_FOUND
t_error	params_get_positionals(t_positionals *dst);

// @ret ERR_NO / ERR_SHELL_NOT_FOUND / ERR_VAR_INVALID_NAME / ERR_VAR_READ_ONLY
// / ERR_LIBC.
t_error	params_set_variable(const char *name, const char *value);

// @ret ERR_NO / ERR_SHELL_NOT_FOUND.
t_error	params_set_last_bg_pid(pid_t value);

// @ret ERR_NO / ERR_SHELL_NOT_FOUND.
t_error	params_set_last_status(int value);

// @ret ERR_NO / ERR_SHELL_NOT_FOUND.
t_error	params_set_option(t_option option, bool on);

// @note src becomes owned by params module (on success only).
// @ret ERR_NO / ERR_SHELL_NOT_FOUND / ERR_LIBC.
t_error	params_push_positionals(t_positionals *src);

// @ret ERR_SHELL_NOT_FOUND / ERR_VAR_NOT_FOUND / ERR_SHIFT_INVALID_VALUE.
t_error	params_shift_positionals(size_t n);

// @note src becomes owned by params module (on success only).
// @warning src must not alias any frame already owned by stack.
// @ret ERR_NO / ERR_SHELL_NOT_FOUND / ERR_VAR_NOT_FOUND / ERR_LIBC.
t_error	params_replace_positionals(t_positionals *src);

// @ret ERR_NO / ERR_SHELL_NOT_FOUND / ERR_LIBC.
t_error	params_pop_positionals(void);

/* ************************************************************************* */
/*                                   DEBUG                                   */
/* ************************************************************************* */

void	params_dump(void);

#endif
