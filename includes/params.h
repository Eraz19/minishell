#ifndef PARAMS_H
# define PARAMS_H

# include "variables.h"
# include "options.h"
# include "specials.h"
# include "positionals.h"
# include "functions.h"
# include "process.h"

/**
 * @struct s_params
 * @brief Aggregates the shell parameter state and dispatch API.
 *
 * @var s_params::name Shell name (borrowed).
 * @var s_params::variables Variable state managed by the variables submodule.
 * @var s_params::options Shell option state managed by the options submodule.
 * @var s_params::specials Special parameter state managed by the specials
 *                         submodule.
 * @var s_params::positionals_stack Positional state managed by the
 *                                  positionals submodule.
 */
typedef struct s_params
{
	/** @brief Shell name (borrowed). */
	const char			*name;
	/** @brief Variable state managed by the variables submodule. */
	t_var_list			variables;
	/** @brief Shell option state managed by the options submodule. */
	t_option			options;
	/** @brief Special parameter state managed by the specials submodule. */
	t_specials			specials;
	/** @brief Positional state managed by the positionals submodule. */
	t_positionals_stack	positionals_stack;
	// TODO: doc
	t_functions			functions;
	// TODO: doc
	t_process_table		processes;
}	t_params;

/**
 * @enum e_params_print_mode
 * @brief Output mode used by params_print().
 */
typedef enum e_params_print_mode
{
	PARAMS_PRINT_EXPORT,
	PARAMS_PRINT_READONLY,
	PARAMS_PRINT_SET
}	t_params_print_mode;

/* ************************************************************************* */
/*                                LIFE CYCLE                                 */
/* ************************************************************************* */

/**
 * @brief Release all owned resources stored in a params aggregate.
 *
 * @param params Params object to clear.
 */
void	params_free(t_params *params);

/**
 * @brief Initialize a params aggregate with empty owned state.
 *
 * @param params Destination params object to initialize.
 */
void	params_init(t_params *params);

// TODO: doc
void	params_init_subshell(t_params *params);

// TODO: doc
void	params_clear(t_params *params);

/**
 * @brief Load all shell parameters from argc/argv/envp.
 *
 * @param params Destination params object to populate.
 * @param argc Argument count.
 * @param argv Argument array (borrowed, read-only).
 * @param envp Environment array (borrowed, read-only).
 */
t_error	params_load(t_params *params, int argc, char **argv, char **envp);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

// TODO: doc
t_error	params_set_function(t_ast_function_def *function_def);
t_error	params_get_function(const char *name, t_function **out);
void	params_stop_function(t_function **function);
t_error	params_unset_function(const char *name);

// @ret ERR_INTERNAL
t_error	params_get_last_status(int *out);
int		params_get_last_status_from(t_params *params);

/**
 * @brief Build the exported environment as a @ref t_vector of C-strings.
 *
 * Only exported variables with a non-NULL value are emitted.
 *
 * @warning The resulting array is not NUL-terminated.
 *
 * @note @p dst_envp is initialized by the function with @c sizeof(char *)
 *       items.
 * @note The caller owns each generated C-string and must free @p dst_envp with
 *       @ref vector_free() using @ref free_char_ptr_void() as callback.
 *
 * @param dst_envp Destination vector receiving owned @c char* items
 *                 (borrowed, initialized by the function).
 * @return @c ERR_SHELL_NOT_FOUND or @c ERR_LIBC on failure.
 */
t_error	params_build_envp(t_vector *dst_envp);

/**
 * @brief Read a scalar parameter by name into a fresh string.
 *
 * The caller owns @p dst on success and must release it with
 * @ref string_free(). @p dst->data may be @c NULL when the parameter exists
 * but has no value.
 *
 * @param name Parameter name (borrowed, read-only).
 * @param dst Destination string initialized by the function (borrowed).
 * @return @c ERR_SHELL_NOT_FOUND, @c ERR_VAR_INVALID_NAME, @c ERR_VAR_NOT_FOUND
 *         or @c ERR_LIBC on failure.
 */
t_error	params_get(const t_string *name, t_string *dst);

/**
 * @brief Const-name variant of @ref params_get().
 *
 * The caller owns the resulting string on success and must release it with
 * @ref string_free().
 *
 * @param name Parameter name (borrowed, read-only).
 * @param dst Destination string initialized by the function (borrowed).
 * @return @c ERR_SHELL_NOT_FOUND, @c ERR_VAR_INVALID_NAME, @c ERR_VAR_NOT_FOUND
 *         or @c ERR_LIBC on failure.
 */
t_error	params_get_from_const(const char *name, t_string *dst);

/**
 * @brief Borrow the current positional frame as a read-only vector view.
 *
 * @param dst Destination pointer to the borrowed read-only frame view.
 * @return @c ERR_SHELL_NOT_FOUND or @c ERR_VAR_NOT_FOUND on failure.
 */
t_error	params_get_positionals(const t_positionals **dst);

/**
 * @brief Print shell parameters in the requested builtin format.
 *
 * @param mode Output mode.
 * @return @c ERR_SHELL_NOT_FOUND, @c ERR_INTERRUPTED, @c ERR_POSIX_WRITE
 *			or @c ERR_LIBC on failure.
 */
t_error	params_print(t_params_print_mode mode);

/**
 * @brief Report whether a variable is marked read-only.
 *
 * When @p name does not match any stored variable, @p out_is_readonly receives
 * @c false.
 *
 * @param name Variable name to inspect (borrowed, read-only).
 * @param out_is_readonly Destination receiving the read-only flag (borrowed).
 * @return @c ERR_NO or @c ERR_SHELL_NOT_FOUND.
 */
t_error	params_is_readonly(const char *name, bool *out_is_readonly);

/**
 * @brief Push a new positional frame on the stack.
 *
 * @param src Positional frame (ownership taken by params).
 * @return @c ERR_SHELL_NOT_FOUND or @c ERR_LIBC on failure.
 */
t_error	params_push_positionals(t_positionals *src);

/**
 * @brief Remove the current positional frame from the stack.
 *
 * @return @c ERR_SHELL_NOT_FOUND or @c ERR_LIBC on failure.
 */
t_error	params_pop_positionals(void);

// TODO: doc
// @ret ERR_NO / ERR_LIBC
t_error	params_reap(t_params *params);

// TODO: doc
// @ret ERR_NO / ERR_INTERNAL / ERR_LIBC
t_error	params_register_process(pid_t pid);

/**
 * @brief Replace the current positional frame with a new one.
 *
 * Ownership transfers to the params module on success.
 * @p src must not alias an already stored frame.
 *
 * @param src Replacement positional frame (ownership taken by params).
 * @return @c ERR_SHELL_NOT_FOUND, @c ERR_VAR_NOT_FOUND or @c ERR_LIBC on failure.
 */
t_error	params_replace_positionals(t_positionals *src);

/**
 * @brief Set or clear a specific shell option bit.
 *
 * @param option Option bit to modify.
 * @param on True to enable the option, false to clear it.
 * @return @c ERR_INTERNAL on failure.
 */
t_error	params_set_option(t_option option, bool on);

#define params_set_last_status(value) params_set_last_status_priv(__func__, value)
/**
 * @brief Update the last command exit status.
 *
 * @param value New status value.
 * @return @c ERR_INTERNAL on failure.
 */
t_error	params_set_last_status_priv(const char *caller, int value);

// TODO: doc
#define params_set_last_status_in(params, value) params_set_last_status_in_priv(__func__, params, value)
void	params_set_last_status_in_priv(const char *caller, t_params *params, int value);

/**
 * @brief Create or update a shell variable.
 *
 * @p value may be @c NULL. When the variable already exists, @p export and
 * @p readonly only affect the stored flags when the function updates them. If
 * the variable is new and @c OPT_EXPORT_ALL is active, it becomes exported
 * even when @p export is false.
 *
 * @param name Variable name (borrowed, read-only).
 * @param value Variable value (borrowed, read-only).
 * @param export Export flag to apply.
 * @param readonly Read-only flag to apply.
 * @return @c ERR_POSIX_ASSIGNMENT or @c ERR_LIBC (both are already printed).
 */
t_error	params_set_variable(
	const t_string *name,
	const t_string *value,
	bool export,
	bool readonly);

/**
 * @brief Remove the first @p n positional arguments from the current frame.
 *
 * @param n Number of leading positional arguments to remove.
 * @return @c ERR_SHELL_NOT_FOUND, @c ERR_VAR_NOT_FOUND or
 *         @c ERR_SHIFT_INVALID_VALUE on failure.
 */
t_error	params_shift_positionals(size_t n);

/**
 * @brief Remove a shell variable by name.
 *
 * @param name Variable name (borrowed, read-only).
 * @return @c ERR_SHELL_NOT_FOUND, @c ERR_VAR_INVALID_NAME, @c ERR_VAR_READ_ONLY
 *         or @c ERR_INDEX_OUT_OF_BOUND on failure.
 */
t_error	params_unset_variable(const t_string *name);

// @ret ERR_NO / ERR_INTERRUPTED / ERR_INTERNAL / ERR_LIBC
t_error	params_wait(pid_t pid, int *status);

// @ret ERR_NO / ERR_INTERRUPTED / ERR_INTERNAL / ERR_LIBC
t_error	params_wait_all(int *status);

/* ************************************************************************* */
/*                                   DEBUG                                   */
/* ************************************************************************* */

/**
 * @brief Dump the current parameter state to stderr.
 */
void	params_dump(void);

#endif
