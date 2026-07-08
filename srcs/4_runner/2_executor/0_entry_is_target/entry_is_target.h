#ifndef ENTRY_IS_TARGET_H
# define ENTRY_IS_TARGET_H

# include <stdbool.h>

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @brief Test whether an environment entry matches a target variable name.
 *
 * The comparison succeeds when @p entry starts with @p target and both strings
 * end or continue with the same character at the first differing position,
 * which makes the helper suitable for matching @c NAME=... entries.
 *
 * @param target Variable name to match (borrowed, read-only).
 * @param entry Full environment entry to inspect (borrowed, read-only).
 * @return True when @p entry targets @p target, false otherwise.
 */
bool	cmd_entry_is_target(const char *target, const char *entry);

#endif
