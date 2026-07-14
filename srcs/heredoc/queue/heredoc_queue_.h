#ifndef HEREDOC_QUEUE__H
# define HEREDOC_QUEUE__H

# include "heredoc.h"

/** @defgroup heredoc_queue Heredoc queue
 *  @brief FIFO of the here-documents registered on the current command
 *         line, waiting for their bodies.
 */

/* ************************************************************************* */
/*                                LIFE_CYCLE                                 */
/* ************************************************************************* */

/**
 * @ingroup heredoc_queue
 * @brief Initializes @p queue as an empty here-document queue.
 *
 * @param queue Queue initialized by the function (borrowed).
 */
void	heredoc_queue_init(t_heredoc_queue *queue);

// TODO: doc
void	heredoc_queue_clear(t_heredoc_queue *queue);

/**
 * @ingroup heredoc_queue
 * @brief Frees @p queue and the strings of every item it owns.
 *
 * @param queue Already initialized queue (borrowed).
 */
void	heredoc_queue_free(t_heredoc_queue *queue);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup heredoc_queue
 * @brief Frees the strings of one item and zeroes it (the item storage
 *        itself is not released).
 *
 * @note Signature matches the @c vector_free element destructor callback.
 * @param item Item to clean, as an untyped pointer (borrowed).
 */
void	heredoc_item_free(void *item);

/**
 * @ingroup heredoc_queue
 * @brief Loads the input text a body will be read from into @p item: a
 *        copy of @p src, or an empty string when @p src is NULL, and
 *        records the caller's read cursor.
 *
 * @param item Item receiving the input; its input string is initialized
 *             by the function (borrowed).
 * @param src Input text to copy, may be NULL (borrowed, read-only).
 * @param i Initial read cursor into the copied input; the body
 *          consumption advances the item's own copy of it.
 * @return @c ERR_LIBC on allocation failure, @c ERR_NO on success.
 */
t_error	heredoc_item_load(t_heredoc_item *item, const t_string *src, size_t i);

/**
 * @ingroup heredoc_queue
 * @brief Removes the oldest item of @p queue.
 *
 * @param queue Already initialized queue (borrowed).
 * @param item Set to the removed item; the caller becomes the owner of
 *             its strings and must release them with
 *             @ref heredoc_item_free (borrowed).
 * @return @c ERR_EMPTY_STACK if @p queue is empty, @c ERR_LIBC if the
 *         removal fails, @c ERR_NO on success.
 */
t_error	heredoc_queue_pop(t_heredoc_queue *queue, t_heredoc_item *item);

/**
 * @ingroup heredoc_queue
 * @brief Appends @p item at the end of @p queue (the struct is copied by
 *        value).
 *
 * @warning Ownership is conditional: the queue owns the item's strings on
 *          success, the caller keeps them on failure (and must release
 *          them, as @c heredoc_register does).
 * @param queue Already initialized queue (borrowed).
 * @param item Item to queue (ownership of its strings taken by @p queue
 *             on success only).
 * @return @c ERR_LIBC if the push fails, @c ERR_NO on success.
 */
// TODO: fix ownership
t_error	heredoc_queue_push(t_heredoc_queue *queue, t_heredoc_item item);

#endif
