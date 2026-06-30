#ifndef EXPANDER_EXPANSION__H
# define EXPANDER_EXPANSION__H

# include "expander.h"

/** @ingroup expander
 *  @brief Vector of owned t_string fields produced by an expansion.
 *
 *  Mirrors the other vector-backed stacks of the project (context stack,
 *  input stack): a thin set of init/free/utils helpers over a t_vector whose
 *  items are t_string values. The vector owns each field's buffer and frees it
 *  with string_free on expansion_free().
 */

/**
 * @ingroup expander
 * @brief Initialises an empty expansion (a vector of t_string items).
 *
 * @param expansion Pointer to the expansion to initialise (borrowed).
 */
void	expansion_init(t_expansion *expansion);

/**
 * @ingroup expander
 * @brief Appends a field to the expansion.
 *
 * The t_string is stored by value and the expansion takes ownership of its
 * buffer; on success the caller must not free @p str.
 *
 * @param expansion Pointer to the expansion (borrowed).
 * @param str Field to append (its buffer's ownership is transferred).
 * @return ERR_NO on success, ERR_LIBC on allocation failure.
 */
t_error	expansion_push(t_expansion *expansion, t_string *str);

/**
 * @ingroup expander
 * @brief Removes the last field of the expansion into @p str.
 *
 * Ownership of the popped field's buffer passes to the caller.
 *
 * @param expansion Pointer to the expansion (borrowed).
 * @param str Out-parameter receiving the removed field.
 * @return ERR_NO on success, ERR_EMPTY_STACK if the expansion is empty.
 */
t_error	expansion_pop(t_expansion *expansion, t_string *str);

#endif
