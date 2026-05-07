#ifndef FIRST_PRIV_H
# define FIRST_PRIV_H

# include <stdbool.h>

/* ************************************************************************* */
/*                                   GROUPS                                  */
/* ************************************************************************* */

/** @defgroup first_priv First module internal API
 *  @brief Internal helpers used to build and combine FIRST sets.
 *  @warning These functions must only be called by the @ref first module
 *           itself.
 *
 *  This private API is intended for the implementation of the @ref first
 *  module.
 */

/* ************************************************************************* */
/*                                  PRIVATE                                  */
/* ************************************************************************* */

/**
 * @ingroup first_priv
 * @brief Marks a terminal-entry slot as present in a FIRST set.
 *
 * This helper sets the boolean entry pointed to by @p dst to true.
 * When @p did_add is not NULL, it is also set to true if the entry pointed to
 * by @p dst was false before this call.
 *
 * @note This function never clears the flag pointed to by @p did_add.
 *
 * @warning @p dst must NOT be NULL.
 * @warning When @p did_add is not NULL, it must point to writable storage.
 * @warning This function performs no parameter validation.
 *
 * @param dst Destination FIRST-set entry to mark as present (borrowed, must
 *            NOT be NULL).
 * @param did_add Optional accumulator flag updated when a new entry is added
 *                (borrowed, can be NULL).
 */
void	first_add(bool *dst, bool *did_add);

/**
 * @ingroup first_priv
 * @brief Merges terminal entries from one FIRST set into another.
 *
 * For each terminal index in the range `[0, @ref SYM_TERMINAL_MAX]`, this
 * helper checks whether the corresponding entry in @p src is true and, if so,
 * marks the matching entry in @p dst by calling @ref first_add.
 *
 * @note When @p did_add is not NULL, it is used as an accumulator flag across
 *       all copied entries.
 *
 * @warning @p dst and @p src must NOT be NULL.
 * @warning @p dst and @p src must each reference an array of at least
 *          `@ref SYM_TERMINAL_MAX + 1` boolean entries.
 * @warning This function performs no parameter validation.
 *
 * @param dst Destination FIRST-set array receiving terminal entries
 *            (borrowed, must NOT be NULL).
 * @param src Source FIRST-set array to read from (borrowed, must NOT be NULL).
 * @param did_add Optional accumulator flag updated when at least one new entry
 *                is added to @p dst (borrowed, can be NULL).
 */
void	first_add_list(bool *dst, const bool *src, bool *did_add);

#endif
