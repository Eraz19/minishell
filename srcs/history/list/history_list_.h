#ifndef HISTORY_LIST__H
# define HISTORY_LIST__H

# include "error.h"
# include "libft.h"

/** @defgroup history_list History entry list
 *  @brief In-memory history entries in chronological order.
 */

/**
 * @ingroup history_list
 * @typedef t_history_list
 * @brief Entry list, backed by a @ref t_vector of @ref t_string values;
 *        the list owns every entry's text.
 */
typedef t_vector	t_history_list;

/* ************************************************************************* */
/*                                LIFE_CYCLE                                 */
/* ************************************************************************* */

/**
 * @ingroup history_list
 * @brief Initializes @p list as an empty entry list.
 *
 * @param list List initialized by the function (borrowed).
 */
void	history_list_init(t_history_list *list);

/**
 * @ingroup history_list
 * @brief Frees @p list and the text of every entry it owns.
 *
 * @param list Already initialized list (borrowed).
 */
void	history_list_free(t_history_list *list);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup history_list
 * @brief Frees the text of one stored entry.
 *
 * @note Signature matches the @c vector_free element destructor callback.
 * @param item Entry to clean, as an untyped pointer (borrowed).
 */
void	history_list_clean(void *item);

/**
 * @ingroup history_list
 * @brief Fetches the entry stored at index @p i without removing it.
 *
 * @param list Already initialized list (borrowed, read-only).
 * @param item Set to the stored entry; @p list keeps ownership
 *             (borrowed).
 * @param i Index of the entry, @c 0 being the oldest.
 * @return @c ERR_EMPTY_STACK if @p list is empty,
 *         @c ERR_INDEX_OUT_OF_BOUND if @p i is past the last entry,
 *         @c ERR_NO on success.
 */
t_error	history_list_get(t_history_list *list, const t_string **item, size_t i);

/**
 * @ingroup history_list
 * @brief Appends an entry to @p list (the string struct is copied
 *        shallowly).
 *
 * @warning Ownership is conditional: on success the list owns the entry's
 *          text and the caller must relinquish its copy of the struct
 *          (re-initialize or zero it, as @c history_save_entry and
 *          @c history_file_load do) to avoid a double free; on failure
 *          the caller keeps ownership and must release the entry with
 *          @c string_free, or keep it reachable for a later free (leak
 *          otherwise).
 * @param list Already initialized list (borrowed).
 * @param item Entry to append (ownership of its text taken by @p list on
 *             success only).
 * @return @c ERR_LIBC if the push fails, @c ERR_NO on success.
 */
// TODO: fix ownership
t_error	history_list_push(t_history_list *list, const t_string *item);

#endif
