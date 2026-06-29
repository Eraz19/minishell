#ifndef HISTORY_LIST__H
# define HISTORY_LIST__H

# include "error.h"
# include "libft.h"

/**
 * @ingroup history
 * @brief In-memory history entries, stored as a vector of owned strings.
 *
 * Each element is a heap-allocated, plain (non-serialised) entry string owned
 * by the list. Entries enter as owned pointers and leave only as deep copies.
 */
typedef t_vector	t_history_list;

/**
 * @ingroup history
 * @brief Frees one stored entry (vector element destructor).
 *
 * @param item Pointer to the stored entry string to free.
 */
void	history_list_clean(void *item);

/**
 * @ingroup history
 * @brief Initialises an empty entry list.
 *
 * @param list Pointer to the list to initialise (borrowed).
 */
void	history_list_init(t_history_list *list);

/**
 * @ingroup history
 * @brief Frees the list and every entry it owns.
 *
 * @param list Pointer to the list to free (borrowed).
 */
void	history_list_free(t_history_list *list);

/**
 * @ingroup history
 * @brief Appends an entry to the list, taking ownership of @p item.
 *
 * @param list Pointer to the list (borrowed).
 * @param item Entry string whose ownership is transferred to the list.
 * @return ERR_NO on success, ERR_LIBC on allocation failure.
 */
t_error	history_list_push(t_history_list *list, const t_string *item);

/**
 * @ingroup history
 * @brief Returns a fresh copy of the entry at index @p i.
 *
 * Duplicates the stored entry string; the returned *item is freshly
 * allocated and owned by the caller.
 *
 * @param list Pointer to the list (borrowed).
 * @param item Out-parameter receiving the freshly allocated copy.
 * @param i Index of the entry to read.
 * @return ERR_NO on success, ERR_EMPTY_STACK if the list is empty,
 *         ERR_INDEX_OUT_OF_BOUND if @p i is past the end, or ERR_LIBC on
 *         allocation failure.
 */
t_error	history_list_get(t_history_list *list, const t_string **item, size_t i);

#endif
