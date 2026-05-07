#ifndef VARIABLE_PRIV_H
# define VARIABLE_PRIV_H

# include "variable.h"

// TODO: add documentation
int	ft_getppid(void);
t_var	var_new(const char *name, const char *value, bool export, bool ronly);
t_error	var_set_ifs(t_var_list *variables);
t_error	var_set_pwd(t_var_list *variables);
t_error	var_set_ppid(t_var_list *variables);

/* ************************************************************************* */
/*                                   GROUPS                                  */
/* ************************************************************************* */

/** @defgroup var_priv Variable Internal API
 *  @brief Internal helpers used by the variable module implementation.
 *
 *  @warning These functions are intended for intra-module use only.
 */

/* ************************************************************************* */
/*                                  PRIVATE                                  */
/* ************************************************************************* */

/**
 * @ingroup var_priv
 * @brief Searches a variable by exact name match and returns its index.
 *
 * Comparison is performed against the full null-terminated @p var_name.
 * Search proceeds from index 0 to the last valid index currently stored in
 * @p variables and stops at the first match.
 *
 * @note On success, the object pointed to by @p res receives the matching
 *       index.
 * @note On failure, the object pointed to by @p res is left unmodified.
 *
 * @warning @p variables, @p var_name and @p res must NOT be NULL.
 *
 * @param variables Variable list to search (borrowed, must NOT be NULL).
 * @param var_name Variable name to look up (borrowed, must NOT be NULL).
 * @param res Output index receiving the first matching position
 *            (modified on success, must NOT be NULL).
 * @return true if a matching variable was found, false otherwise.
 */
bool	var_find(const t_var_list *variables, const char *var_name, size_t *res);

/**
 * @ingroup var_priv
 * @brief Releases the dynamic resources owned by an initialized variable.
 *
 * Frees the strings owned through the `name` and `value` fields of @p var when
 * they are non-NULL, then sets these pointers to NULL and resets `export` and
 * `readonly` to false.
 *
 * @warning @p var must NOT be NULL.
 * @warning @p var must have been initialized before calling this function: its
 *          `name` and `value` fields must each be either NULL or a valid owned
 *          pointer.
 * @warning This function does NOT free the @ref t_var object itself.
 *
 * @param var Variable to clear in place (borrowed, must NOT be NULL).
 */
void	var_free(t_var *var);

/**
 * @ingroup var_priv
 * @brief Replaces the value string owned by a variable.
 *
 * Allocates a duplicate of @p value first, then frees the previous value
 * string owned by @p var only after allocation succeeds.
 *
 * @note On failure, the previous value is left unchanged.
 *
 * @warning @p var and @p value must NOT be NULL.
 *
 * @param var Variable to update in place (borrowed, must NOT be NULL).
 * @param value New value to duplicate and assign (borrowed, must NOT be NULL).
 * @retval @ref ERR_NO Value was updated successfully.
 * @retval @ref ERR_OUT_OF_MEMORY Memory allocation failed and the variable was
 *                                left unchanged.
 */
t_error	var_update_value(t_var *var, const char *value);

#endif
