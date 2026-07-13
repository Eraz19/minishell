#ifndef ALIAS__H
# define ALIAS__H

# include "alias.h"

/** @defgroup alias_priv Alias internals
 *  @brief Eligibility, position tracking and printing helpers behind the
 *         alias API.
 */

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup alias_priv
 * @brief Prints every alias in a NULL-terminated array as a reinput-able
 *        @c name='value' line, then frees the array.
 *
 * Stops at the first failing write; the pairs remain owned by the map.
 * Does nothing when @p pairs is NULL.
 *
 * @param pairs NULL-terminated array of pairs; the array itself is freed
 *              by the call, its pairs stay owned by the map (ownership
 *              taken by the function).
 * @return @c ERR_LIBC on allocation failure; @c ERR_POSIX_WRITE on a
 *         failed write (requalified by the caller per error.h);
 *         @c ERR_INTERRUPTED when a signal interrupts the write;
 *         @c ERR_NO on success.
 */
t_error	alias_print_all(const t_key_value **pairs);

/**
 * @ingroup alias_priv
 * @brief Prints the alias named @p name as a reinput-able
 *        @c name='value' line.
 *
 * @param alias Alias state (borrowed).
 * @param name Alias name to print (borrowed, read-only).
 * @return @c ERR_ALIAS_NOT_FOUND (unprinted, not recorded in the module
 *         state: the calling builtin owns the diagnostic and the exit
 *         status); @c ERR_LIBC on allocation failure; @c ERR_POSIX_WRITE
 *         on a failed write; @c ERR_INTERRUPTED when a signal interrupts
 *         the write; @c ERR_NO on success.
 */
t_error	alias_print_one(t_alias *alias, const char *name);

/**
 * @ingroup alias_priv
 * @brief Tests whether a token is eligible for alias expansion
 *        (POSIX 2.3.1).
 *
 * True when @p word is a valid unquoted alias name present in the map, is
 * not already being expanded (absent from the recursion-guard stack) and
 * stands in command position, unless a previous expansion's trailing
 * blank lifted the position requirement.
 *
 * @note A failure of the builder's command-position check is recorded in
 *       @c alias->err and the token is refused: callers returning
 *       @c alias->err on the not-eligible path propagate it.
 * @param alias Alias state (borrowed).
 * @param word Candidate token text, NUL-terminated C-string (borrowed,
 *             read-only).
 * @return True if the token should be expanded, false otherwise.
 */
bool	is_token_alias_expandable(t_alias *alias, char *word);

/**
 * @ingroup alias_priv
 * @brief Updates the position rule from a just-produced expansion.
 *
 * Sets @c alias->disable_position when @p expansion ends with a blank, so
 * the next word is expanded too (POSIX 2.3.1 trailing-blank rule).
 *
 * @param alias Alias state (borrowed).
 * @param expansion Expansion text just produced, may be NULL
 *                  (borrowed, read-only).
 */
void	set_position_for_next_word(t_alias *alias, t_string *expansion);

#endif
