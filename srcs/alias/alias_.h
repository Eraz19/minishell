#ifndef ALIAS__H
# define ALIAS__H

# include "alias.h"

/**
 * @ingroup alias
 * @brief Prints every alias in a NULL-terminated array, then frees it.
 *
 * Prints each pair via alias_print_one() and frees the @p pairs array itself
 * (the pairs remain owned by the map). Does nothing when @p pairs is NULL.
 *
 * @param pairs NULL-terminated array of pairs (owned; freed by this call).
 */
void	alias_print_all(t_key_value **pairs);

/**
 * @ingroup alias
 * @brief Updates the position rule from a just-produced expansion.
 *
 * Sets state->disable_position when @p expansion ends with a blank, so the
 * next word is expanded too (mirroring the shell's trailing-blank rule).
 *
 * @param state Pointer to the alias state (borrowed).
 * @param expansion Expansion text just produced (borrowed), may be NULL.
 */
void	set_position_for_next_word(t_alias *state, char *expansion);

/**
 * @ingroup alias
 * @brief Tests whether a token is eligible for alias expansion.
 *
 * True when @p word is a valid unquoted alias name present in the map, is not
 * already being expanded (absent from the recursion-guard stack) and stands
 * in command position, unless a previous expansion's trailing blank lifted
 * the position requirement.
 *
 * @param state Pointer to the alias state (borrowed).
 * @param word Candidate token text (borrowed).
 * @return true if the token should be expanded, false otherwise.
 */
bool	is_token_alias_expandable(t_alias *state, char *word);

#endif
