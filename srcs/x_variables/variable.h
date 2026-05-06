#ifndef VARIABLE_H
# define VARIABLE_H

# include "libft.h"
# include "error.h"

/* ************************************************************************* */
/*                                   TYPES                                   */
/* ************************************************************************* */

/**
 * @struct s_var
 * @brief Shell variable entry stored inside a variable list.
 *
 * @var s_var::name Variable name string (owned by the variable, valid
 *                  NUL-terminated string, never NULL in an initialized
 *                  variable).
 * @var s_var::value Variable value string (owned by the variable, valid
 *                   NUL-terminated string, never NULL in an initialized
 *                   variable).
 * @var s_var::export Whether the variable is marked for export.
 * @var s_var::readonly Whether the variable is read-only.
 */
typedef struct s_var
{
	/** @brief Variable name string (owned by the variable, never NULL in an initialized variable). */
	char	*name;
	/** @brief Variable value string (owned by the variable, never NULL in an initialized variable). */
	char	*value;
	/** @brief Export flag. */
	bool	export;
	/** @brief Read-only flag. */
	bool	readonly;
}	t_var;

/**
 * @typedef t_var_list
 * @brief Type alias for a vector storing contiguous @ref t_var items.
 *
 * @warning All variable-list functions assume this vector stores items of type
 *          @ref t_var with `item_size == sizeof(t_var)`.
 */
typedef t_vector	t_var_list;

/* ************************************************************************* */
/*                                   GROUPS                                  */
/* ************************************************************************* */

/** @defgroup var_pub Variable Module (public functions)
 *  @brief Public functions to set, get, edit and unset shell variables.
 */

/* ************************************************************************* */
/*                                 VAR (PUB)                                 */
/* ************************************************************************* */

/**
 * @ingroup var_pub
 * @brief Releases all variables stored in the list and frees the list storage.
 *
 * Calls @ref var_free on each stored @ref t_var, then releases the underlying
 * vector storage with `vector_free()`.
 *
 * @note This function clears every variable currently stored in @p variables.
 * @note After this call, `variables->data == NULL`, `variables->len == 0` and
 *       `variables->cap == 0`.
 *
 * @warning @p variables must NOT be NULL.
 * @warning @p variables must be an initialized @ref t_var_list.
 *
 * @param variables Variable list to clear and release (borrowed, must NOT be
 *                  NULL).
 */
void	var_free_all(t_var_list *variables);

/**
 * @ingroup var_pub
 * @brief Retrieves a borrowed pointer to a variable stored in the list.
 *
 * On success, `*dst_var` points directly to the matching @ref t_var stored
 * inside the contiguous storage owned by @p variables.
 *
 * @note The returned pointer is borrowed from @p variables.
 * @note Ownership remains with the @ref t_var_list; caller must NOT free the
 *       returned @ref t_var, nor its `name` or `value` fields.
 * @note On failure, `*dst_var` is left unmodified.
 *
 * @warning @p variables, @p var_name and @p dst_var must NOT be NULL.
 * @warning The returned pointer becomes potentially invalid after any mutation
 *          of the underlying vector, including @ref var_set,
 *          @ref var_unset, @ref var_set_export, @ref var_set_readonly, or any
 *          other operation on the same @ref t_var_list that can reorder items,
 *          remove items, or reallocate/move `variables->data`.
 *
 * @param variables Variable list to search (borrowed, must NOT be NULL).
 * @param var_name Variable name to look up (borrowed, must NOT be NULL).
 * @param dst_var Output pointer receiving the matching variable
 *                (borrowed from @p variables, must NOT be NULL).
 * @retval ERR_NO Variable was found and `*dst_var` was set.
 * @retval ERR_INVALID_POINTER @p variables, @p var_name or @p dst_var is NULL.
 * @retval ERR_VAR_NOT_FOUND No variable named @p var_name exists in the list.
 */
t_error	var_get(t_var_list *variables, const char *var_name, t_var **dst_var);

/**
 * @ingroup var_pub
 * @brief Initializes an empty variable list.
 *
 * Initializes @p variables as a vector of @ref t_var with zero initial
 * capacity.
 *
 * @note This function cannot fail with the current implementation because it
 *       delegates to `vector_init(..., 0)`.
 *
 * @warning variables must NOT be NULL.
 * @warning @p variables must NOT already own allocated storage. Free it first
 *          with @ref var_free_all before reinitializing it.
 *
 * @param variables Variable list to initialize (borrowed, must NOT be NULL).
 */
void	var_init(t_var_list *variables);

/**
 * @ingroup var_pub
 * @brief Loads environment variables from a NULL-terminated envp array.
 *
 * Each entry is split at the first `=` using @ref var_split. When the split
 * succeeds and the extracted name is valid according to
 * @ref var_name_is_valid, the variable is inserted with @ref var_set and then
 * marked as exported with @ref var_set_export.
 *
 * @note Invalid environment entries are skipped when splitting fails with
 *       @ref ERR_VAR_MISSING_EQUAL or when the extracted name is invalid.
 * @note If @p envp is NULL, this function does nothing and returns
 *       @ref ERR_NO.
 * @note Variables loaded from @p envp are marked as exported.
 *
 * @warning When @p envp is not NULL, variables must NOT be NULL.
 * @warning @p envp must be a valid NULL-terminated array of valid string
 *          pointers.
 * @warning On failure, variables successfully loaded before the error remain
 *          stored in @p variables; this function does NOT roll back partial
 *          progress.
 *
 * @param variables Variable list to populate (borrowed, must NOT be NULL when
 *                  @p envp is not NULL).
 * @param envp Environment array to import (borrowed, can be NULL).
 * @retval ERR_NO Environment was loaded successfully, or @p envp was NULL.
 * @retval ERR_INVALID_POINTER A NULL pointer was encountered in a required
 *                             internal call.
 * @retval ERR_OUT_OF_MEMORY Memory allocation failed while importing an entry.
 * @retval ERR_VAR_INVALID_NAME Propagated from an internal call.
 * @retval ERR_VAR_READ_ONLY Propagated from an internal call.
 */
t_error	var_load_env(t_var_list *variables, const char **envp);

/**
 * @ingroup var_pub
 * @brief Creates a new variable or updates the value of an existing one.
 *
 * If a variable named @p name already exists, only its value is updated.
 * Otherwise, a new non-exported, non-read-only variable is appended to the
 * list.
 *
 * @note The contents of @p name and @p value are duplicated internally; caller
 *       retains ownership of the input strings.
 * @note When updating an existing variable, the previous value is preserved if
 *       allocation of the new value fails.
 *
 * @warning @p variables, @p name and @p value must NOT be NULL.
 * @warning Any successful insertion may reallocate the underlying vector
 *          storage and invalidate borrowed pointers into the list.
 *
 * @param variables Variable list to mutate (borrowed, must NOT be NULL).
 * @param name Variable name (borrowed, must NOT be NULL).
 * @param value New variable value (borrowed, must NOT be NULL).
 * @retval ERR_NO Variable was created or updated successfully.
 * @retval ERR_INVALID_POINTER variables, name or value is NULL.
 * @retval ERR_VAR_INVALID_NAME name is not a valid variable name.
 * @retval ERR_VAR_READ_ONLY An existing variable with that name is read-only.
 * @retval ERR_OUT_OF_MEMORY Memory allocation failed.
 */
t_error	var_set(t_var_list *variables, const char *name, const char *value);

/**
 * @ingroup var_pub
 * @brief Sets or clears the export flag of a variable.
 *
 * If the variable already exists, only its `export` flag is updated.
 * If the variable does not exist and @p export is true, a new variable is
 * created with an empty value (`""`), `export == true`, and
 * `readonly == false`.
 *
 * @note The contents of @p name are duplicated internally only when a new
 *       variable must be created; caller retains ownership of the input
 *       string.
 * @note This function may modify the export flag of an existing read-only
 *       variable, because read-only only protects value removal/update.
 *
 * @warning @p variables and @p name must NOT be NULL.
 * @warning Any successful insertion may reallocate the underlying vector
 *          storage and invalidate borrowed pointers into the list.
 *
 * @param variables Variable list to mutate (borrowed, must NOT be NULL).
 * @param name Variable name (borrowed, must NOT be NULL).
 * @param export New export flag value.
 * @retval ERR_NO Export flag was updated successfully.
 * @retval ERR_INVALID_POINTER variables or name is NULL.
 * @retval ERR_VAR_INVALID_NAME name is not a valid variable name.
 * @retval ERR_VAR_NOT_FOUND No variable named @p name exists and @p export is
 *                           false.
 * @retval ERR_OUT_OF_MEMORY Memory allocation failed while creating a missing
 *                           variable.
 */
t_error	var_set_export(t_var_list *variables, const char *name, bool export);

/**
 * @ingroup var_pub
 * @brief Marks a variable as read-only.
 *
 * If the variable already exists, its `readonly` flag is set to true.
 * If the variable does not exist, a new variable is created with an empty
 * value (`""`), `export == false`, and `readonly == true`.
 *
 * @note The contents of @p name are duplicated internally only when a new
 *       variable must be created; caller retains ownership of the input
 *       string.
 * @note This operation is idempotent for an already read-only variable.
 *
 * @warning @p variables and @p name must NOT be NULL.
 * @warning Any successful insertion may reallocate the underlying vector
 *          storage and invalidate borrowed pointers into the list.
 *
 * @param variables Variable list to mutate (borrowed, must NOT be NULL).
 * @param name Variable name (borrowed, must NOT be NULL).
 * @retval ERR_NO Variable is now read-only.
 * @retval ERR_INVALID_POINTER @p variables or @p name is NULL.
 * @retval ERR_VAR_INVALID_NAME @p name is not a valid variable name.
 * @retval ERR_OUT_OF_MEMORY Memory allocation failed while creating a missing
 *                           variable.
 */
t_error	var_set_readonly(t_var_list *variables, const char *name);

/**
 * @ingroup var_pub
 * @brief Splits an assignment string into a newly allocated name/value pair.
 *
 * Splits @p src at the first `'='` character. The left part becomes
 * `*dst_name`, and the right part becomes `*dst_value`.
 *
 * @note Either resulting part may be empty.
 * @note This function does NOT validate the extracted variable name.
 * @note On entry validation failure, `*dst_name` and `*dst_value` are not
 *       accessed.
 * @note After parameter validation succeeds, both outputs are first set to
 *       NULL.
 *
 * @warning @p src, @p dst_name and @p dst_value must NOT be NULL.
 *
 * @param src Source assignment string to split (borrowed, must NOT be NULL).
 * @param dst_name Output pointer receiving the newly allocated name string
 *                 (owned by caller on success, must be freed with free()).
 * @param dst_value Output pointer receiving the newly allocated value string
 *                  (owned by caller on success, must be freed with free()).
 * @retval ERR_NO Split succeeded.
 * @retval ERR_INVALID_POINTER @p src, @p dst_name or @p dst_value is NULL.
 * @retval ERR_VAR_MISSING_EQUAL src does not contain `'='`.
 * @retval ERR_OUT_OF_MEMORY Memory allocation failed. On failure,
 *                           `*dst_name == NULL` and `*dst_value == NULL`.
 */
t_error	var_split(const char *src, char **dst_name, char **dst_value);

/**
 * @ingroup var_pub
 * @brief Removes a variable from the list unless it is read-only.
 *
 * If the variable exists and is not read-only, its owned strings are freed
 * first, then the entry is removed from the vector.
 *
 * @note If no variable named @p var_name exists, this function returns
 *       @ref ERR_NO.
 *
 * @warning variables and var_name must NOT be NULL.
 * @warning Removing an item shifts subsequent items left and may invalidate
 *          borrowed pointers into the list.
 *
 * @param variables Variable list to mutate (borrowed, must NOT be NULL).
 * @param var_name Variable name to remove (borrowed, must NOT be NULL).
 * @retval ERR_NO Variable was removed, or no such variable existed.
 * @retval ERR_INVALID_POINTER variables or var_name is NULL.
 * @retval ERR_VAR_READ_ONLY The matching variable is read-only.
 * @retval ERR_INDEX_OUT_OF_BOUND Internal removal from the vector failed.
 */
t_error	var_unset(t_var_list *variables, const char *var_name);

#endif
