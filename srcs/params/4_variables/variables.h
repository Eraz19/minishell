#ifndef VARIABLES_H
# define VARIABLES_H

# include "libft.h"
# include "error.h"
# include <stdbool.h>

/* ************************************************************************* */
/*                                   TYPES                                   */
/* ************************************************************************* */

/**
 * @brief Variable list stored as a vector of @ref t_var entries.
 */
typedef t_vector	t_var_list;

/**
 * @enum e_var_print_mode
 * @brief Output mode used by @ref var_print().
 */
typedef enum e_var_print_mode
{
	VAR_PRINT_EXPORT,
	VAR_PRINT_READONLY
}	t_var_print_mode;

/* ************************************************************************* */
/*                                 LIFE CYCLE                                */
/* ************************************************************************* */

/**
 * @brief Initialize an empty variable list.
 *
 * @param variables Destination list (borrowed).
 */
void	var_init(t_var_list *variables);

/**
 * @brief Load variables from the environment array.
 *
 * @param variables Destination list (borrowed).
 * @param envp Environment vector (borrowed, read-only).
 * @return @c ERR_VAR_INVALID_NAME, @c ERR_VAR_NOT_FOUND, @c ERR_VAR_READ_ONLY
 *         or @c ERR_LIBC.
 */
t_error	var_load(t_var_list *variables, char **envp);

/**
 * @brief Release every variable owned by the list.
 *
 * @param variables List to clear (borrowed).
 */
void	var_free(t_var_list *variables);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @brief Build an envp array from exported variables.
 *
 * The returned array and entries are owned by the caller.
 *
 * @param variables Source list (borrowed, read-only).
 * @param dst_envp Destination envp pointer (borrowed).
 * @return @c ERR_LIBC.
 */
t_error	var_build_envp(const t_var_list *variables, char ***dst_envp);

/**
 * @brief Read a variable value into a fresh string.
 *
 * The caller owns @p dst_val on success and must release it with
 * @ref string_free(). @p dst_val->data may be @c NULL when the variable
 * exists but has no value.
 *
 * @param name Variable name (borrowed, read-only).
 * @param dst_val Initialized destination string (borrowed).
 * @return @c ERR_SHELL_NOT_FOUND, @c ERR_VAR_INVALID_NAME, @c ERR_VAR_NOT_FOUND
 *         or @c ERR_LIBC.
 */
t_error	var_get(const t_string *name, t_string *dst_val);

/**
 * @brief Const-name variant of @ref var_get().
 *
 * The caller owns @p dst_val on success and must release it with
 * @ref string_free(). @p dst_val->data may be @c NULL when the variable
 * exists but has no value.
 *
 * @param name Variable name (borrowed, read-only).
 * @param dst_val Destination string initialized by the function (borrowed).
 * @return @c ERR_SHELL_NOT_FOUND, @c ERR_VAR_INVALID_NAME, @c ERR_VAR_NOT_FOUND
 *         or @c ERR_LIBC.
 */
t_error	var_get_from_const(const char *name, t_string *dst_val);

/**
 * @brief Print variables in export or readonly format.
 *
 * @param mode Output mode.
 * @return @c ERR_SHELL_NOT_FOUND, @c ERR_INTERRUPTED or @c ERR_LIBC.
 */
t_error	var_print(t_var_print_mode mode);

/**
 * @brief Create or update a variable.
 *
 * @p value may be @c NULL. When the variable already exists, @p export and
 * @p readonly only affect the stored flags when the function updates them. If
 * the variable is new and @c OPT_EXPORT_ALL is active, it becomes exported
 * even when @p export is false.
 *
 * @param name Variable name (borrowed, read-only).
 * @param value Variable value (borrowed, read-only).
 * @param export Export flag to apply.
 * @param rdonly Read-only flag to apply.
 * @return @c ERR_SHELL_NOT_FOUND, @c ERR_VAR_INVALID_NAME, @c ERR_VAR_READ_ONLY
 *         or @c ERR_LIBC.
 */
t_error	var_set(
			const t_string *name,
			const t_string *value,
			bool export,
			bool rdonly);

/**
 * @brief Remove a variable by name.
 *
 * @param name Variable name (borrowed, read-only).
 * @return @c ERR_SHELL_NOT_FOUND, @c ERR_VAR_INVALID_NAME, @c ERR_VAR_READ_ONLY
 *         or @c ERR_INDEX_OUT_OF_BOUND.
 */
t_error	var_unset(const t_string *name);

/* ************************************************************************* */
/*                                   DEBUG                                   */
/* ************************************************************************* */

/**
 * @brief Dump the variable list to stderr.
 */
void	var_dump(void);

#endif
