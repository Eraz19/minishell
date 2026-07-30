#ifndef ALIAS_OLD_H
# define ALIAS_OLD_H

# include "error.h"
# include "libft.h"
# include "parser_type.h"

/** @defgroup alias Alias API
 *  @brief Shell command aliases with recursion-guarded expansion
 *         (POSIX 2.3.1).
 *
 *  Maps alias names to their replacement text in a hash map and keeps full
 *  ownership of its data: names and values handed in are deep copied (the
 *  caller keeps its buffers) and the expansion handed out is a deep copy
 *  the caller takes ownership of, so no buffer is shared across the
 *  boundary. A stack of the aliases currently being expanded guards
 *  against infinite recursion.
 *
 *  ERROR CONTRACT
 *
 *  The module does NOT requalify its errors: both caller groups still
 *  need the specifics, so every type below crosses the API raw.
 *
 *  - Tokenization side (@ref alias_expand_token,
 *    @ref alias_on_expansion_end): driven by the scanner, whose endpoints
 *    requalify everything (unqualified errors become @c ERR_INTERNAL).
 *  - Builtin side (@ref alias_add, @ref alias_remove, @ref alias_print):
 *    the @c alias / @c unalias builtins need @c ERR_ALIAS_NOT_FOUND
 *    specific to write the POSIX diagnostic (they alone know the utility
 *    name for the prefix) and to exit non-zero; they requalify it as
 *    @c ERR_BUILTIN (see error.h). @c ERR_POSIX_WRITE from the print path
 *    is requalified by the caller, per its error.h annotation.
 *
 *  Recoverable errors (@c ERR_ALIAS_NOT_FOUND) are returned fresh and
 *  never stored in @ref s_alias::err: only hard failures are recorded, so
 *  one failed lookup cannot poison later calls through the sticky module
 *  error.
 *
 *  @warning The @c alias and @c unalias builtins are still stubs in
 *           @c TODO.c: the diagnostic and requalification described above
 *           are pending there.
 */

/**
 * @ingroup alias
 * @typedef t_alias_stack
 * @brief Recursion-guard stack: the names currently being expanded,
 *        backed by a @ref t_vector of owned C-strings.
 */
typedef t_vector	t_alias_stack;

/**
 * @ingroup alias
 * @struct s_alias
 * @brief Aggregate state of the alias module.
 *
 * @var s_alias::err Last hard failure recorded by the module (recoverable
 *                   errors are never stored here).
 * @var s_alias::map Name-to-value hash map; owns its keys and values.
 * @var s_alias::stack Names of the aliases currently being expanded,
 *                     managed by the alias_stack submodule.
 * @var s_alias::disable_position Whether the next word may expand
 *                                regardless of command position (set when
 *                                an expansion ends with a blank,
 *                                POSIX 2.3.1 trailing-blank rule).
 */
typedef struct s_alias
{
	t_error			err;
	t_hashmap		map;
	t_alias_stack	stack;
	t_parser		*parser;
	bool			disable_position;
}	t_alias;

/* ************************************************************************* */
/*                                LIFE_CYCLE                                 */
/* ************************************************************************* */

// TODO: doc
void	alias_init(t_alias *alias);

// TODO: doc
void	alias_clear(t_alias *alias);

/**
 * @ingroup alias
 * @brief Frees the expansion stack and the map (keys and values) of
 *        @p alias, then zeroes it.
 *
 * @param alias Already initialized alias state (borrowed).
 */
void	alias_free(t_alias *alias);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup alias
 * @brief Adds or replaces an alias.
 *
 * Associates @p name with @p value, replacing any existing entry. The key
 * is duplicated and the value is deep copied (a NULL value is stored as an
 * empty string), so the caller keeps ownership of both arguments. Does
 * nothing when @p name is NULL. Operates on the global shell alias state.
 *
 * @param name Alias name (borrowed, read-only).
 * @param value Replacement text, NULL means empty (borrowed, read-only).
 * @return @c ERR_SHELL_NOT_FOUND if the shell alias state is unavailable,
 *         @c ERR_LIBC on allocation failure, @c ERR_NO on success.
 */
t_error	alias_add(const char *name, const char *value);

// TODO: doc
t_error	alias_expand_token(
			t_parser *parser,
			t_string *expansion,
			bool *expanded,
			const t_string *token_value);

/**
 * @ingroup alias
 * @brief Tests whether @p name is a valid alias name (XBD 3.10).
 *
 * Accepts words made only of portable-character-set alphanumerics and
 * '_', '!', '%', ',', '-', '@'. NULL and the empty string are invalid.
 * Single source of truth for both sides of the module: the alias/unalias
 * builtins (operand validation) and the expansion eligibility check use
 * this predicate, so a definable name is always an expandable name.
 *
 * @param name Candidate name (borrowed, read-only), may be NULL.
 * @return true when @p name is a valid alias name.
 */
bool	alias_is_valid_name(const char *name);

/**
 * @ingroup alias
 * @brief Marks the end of the current alias expansion.
 *
 * Pops and frees the most recent name off the recursion-guard stack,
 * allowing that alias to expand again later. Does nothing when the stack
 * is empty. Operates on the global shell alias state.
 *
 * @return @c ERR_SHELL_NOT_FOUND if the shell alias state is unavailable,
 *         @c ERR_NO otherwise.
 */
t_error	alias_on_expansion_end(void);

/**
 * @ingroup alias
 * @brief Prints one alias, or every alias, as a reinput-able
 *        @c name='value' line on standard output.
 *
 * Prints the alias named @p name, or all stored aliases when @p name is
 * NULL. Values are single-quote escaped so the output can be fed back to
 * the shell (POSIX alias output format). Operates on the global shell
 * alias state.
 *
 * @param name Alias to print (borrowed, read-only), or NULL to print them
 *             all.
 * @return @c ERR_ALIAS_NOT_FOUND (unprinted) when @p name has no
 *         definition: the calling builtin owns the diagnostic and the
 *         exit status; @c ERR_POSIX_WRITE on a failed write (requalified
 *         by the caller per error.h); @c ERR_INTERRUPTED when a signal
 *         interrupts the write; @c ERR_LIBC on allocation failure;
 *         @c ERR_SHELL_NOT_FOUND if the shell alias state is unavailable;
 *         @c ERR_NO on success.
 */
t_error	alias_print(const char *name);

/**
 * @ingroup alias
 * @brief Removes an alias by name.
 *
 * Removes the alias named @p name and frees the module's copies of its
 * key and value. Does nothing when @p name is NULL. The caller keeps
 * ownership of @p name. Operates on the global shell alias state.
 *
 * @param name Alias to remove (borrowed, read-only).
 * @return @c ERR_ALIAS_NOT_FOUND (unprinted) when @p name has no
 *         definition: the calling builtin owns the diagnostic and the
 *         exit status (POSIX unalias); @c ERR_SHELL_NOT_FOUND if the
 *         shell alias state is unavailable; @c ERR_NO on success.
 */
t_error	alias_remove(const char *name);

/**
 * @ingroup alias
 * @brief Removes every alias definition (POSIX @c unalias @c -a).
 *
 * Empties the definition map and frees the module's copies of all keys
 * and values. Removing zero definitions is a success. Operates on the
 * global shell alias state.
 *
 * @warning Clears the MAP ONLY — unlike @ref alias_clear, the
 *          recursion-guard stack is left intact: an in-flight expansion
 *          (e.g. @c alias @c ua='unalias @c -a'; @c ua) must keep its
 *          guard entries until its own expansion end.
 * @return @c ERR_SHELL_NOT_FOUND if the shell alias state is
 *         unavailable, @c ERR_NO otherwise.
 */
t_error	alias_remove_all(void);

#endif
