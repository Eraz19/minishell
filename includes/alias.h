#ifndef ALIAS_H
# define ALIAS_H

# include "error.h"
# include "libft.h"

/** @defgroup alias Alias API
 *  @brief Shell command aliases with recursion-guarded expansion.
 *
 *  Maps alias names to their replacement text in a hash map and keeps full
 *  ownership of its data: names and values handed in are deep copied (the
 *  caller keeps its buffers) and the expansion handed out is a deep copy the
 *  caller takes ownership of, so no buffer is shared across the boundary. A
 *  stack of the aliases currently being expanded guards against infinite
 *  recursion.
 */

typedef t_vector	t_alias_stack;

/**
 * @ingroup alias
 * @struct s_alias
 * @brief Aggregate state of the alias module.
 *
 * @var s_alias::err Last error recorded by the module.
 * @var s_alias::map Name-to-value hash map (owns its keys and values).
 * @var s_alias::stack Names of the aliases currently being expanded.
 * @var s_alias::disable_position Whether the next word may expand regardless
 *                                of command position (set when an expansion
 *                                ends with a blank).
 */
typedef struct s_alias
{
	t_error			err;
	t_hashmap		map;
	t_alias_stack	stack;
	bool			disable_position;
}	t_alias;

/**
 * @ingroup alias
 * @brief Initialises an alias state to an empty, ready-to-use value.
 *
 * Zeroes the structure then initialises the expansion stack and the
 * name-to-value map, whose values are released with free() on removal.
 *
 * @param state Pointer to the alias state to initialise (borrowed).
 */
void	alias_init(t_alias *state);

/**
 * @ingroup alias
 * @brief Releases every resource held by an alias state.
 *
 * Frees the expansion stack and the map (keys and values), then resets the
 * structure to zero.
 *
 * @param state Pointer to the alias state to free (borrowed).
 */
void	alias_free(t_alias *state);

/**
 * @ingroup alias
 * @brief Marks the end of the current alias expansion.
 *
 * Pops the most recent name off the recursion-guard stack, allowing that
 * alias to expand again later. Does nothing when the stack is empty.
 * Operates on the global shell alias state.
 *
 * @return ERR_NO on success, ERR_SHELL_NOT_FOUND if the shell alias state is
 *         unavailable, or the recorded error on failure.
 */
t_error	alias_on_expansion_end(void);

/**
 * @ingroup alias
 * @brief Prints one alias, or every alias, as `name='value'`.
 *
 * Prints the alias named @p name, or all stored aliases when @p name is
 * NULL. A missing name prints nothing. Operates on the global shell alias
 * state.
 *
 * @param name Alias to print (borrowed), or NULL to print them all.
 * @return ERR_NO on success, ERR_SHELL_NOT_FOUND if the shell alias state is
 *         unavailable, or the recorded error on failure.
 */
t_error	alias_print(const char *name);

/**
 * @ingroup alias
 * @brief Removes an alias by name.
 *
 * Removes the alias named @p name and frees the module's copies of its key
 * and value. Does nothing when @p name is NULL or absent. The caller keeps
 * ownership of @p name. Operates on the global shell alias state.
 *
 * @param name Alias to remove (borrowed).
 * @return ERR_NO on success, ERR_SHELL_NOT_FOUND if the shell alias state is
 *         unavailable, or the recorded error on failure.
 */
t_error	alias_remove(const char *name);

/**
 * @ingroup alias
 * @brief Adds or replaces an alias.
 *
 * Associates @p name with @p value, replacing any existing entry. The key is
 * duplicated and the value is deep copied (a NULL value is stored as an empty
 * string), so the caller keeps ownership of both arguments. Operates on the
 * global shell alias state.
 *
 * @param name Alias name (borrowed; duplicated internally).
 * @param value Replacement text (borrowed; deep copied, NULL means empty).
 * @return ERR_NO on success, ERR_SHELL_NOT_FOUND if the shell alias state is
 *         unavailable, or ERR_LIBC on allocation failure.
 */
t_error	alias_add(const char *name, const char *value);

/**
 * @ingroup alias
 * @brief Expands a token to its alias value when eligible.
 *
 * Reads the token text from @p token_value and, when it names an alias
 * eligible for expansion (valid unquoted name, not already being expanded,
 * and in command position unless a previous expansion lifted that rule),
 * pushes the name onto the recursion-guard stack and returns a freshly
 * allocated copy of its value through @p expansion. When the token is not
 * eligible, @p expansion is left untouched.
 *
 * @note On a successful expansion, ownership of *expansion passes to the
 *       caller.
 * @warning *expansion is written only when the token expands; initialise it
 *          to NULL before the call (or test the return value) so the
 *          no-expansion case stays distinguishable.
 *
 * @param expansion Out-parameter receiving the freshly allocated expansion
 *                  string (owned by the caller) on a successful expansion.
 * @param token_value t_string holding the token text to test (borrowed).
 * @return ERR_NO on success (whether or not the token expanded),
 *         ERR_SHELL_NOT_FOUND if the shell alias state is unavailable, or
 *         ERR_LIBC on allocation failure.
 */
t_error	alias_expand_token(char **expansion, t_string *token_value);

#endif
