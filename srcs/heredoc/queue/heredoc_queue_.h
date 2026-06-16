/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_queue_.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 16:14:23 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/12 17:58:20 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_QUEUE__H
# define HEREDOC_QUEUE__H

# include "heredoc.h"

/**
 * @ingroup heredoc
 * @brief Frees the owned fields of one queued heredoc item.
 *
 * Frees the item's path and delimiter, then zeroes the item. Used as the
 * per-element destructor when freeing the queue. The @c void* signature lets
 * it serve as the vector element-free callback.
 *
 * @param item Pointer to the t_heredoc_queue_item to release (borrowed shell,
 *             owned contents).
 */
void	heredoc_queue_item_free(void *item);

/**
 * @ingroup heredoc
 * @brief Initialises an empty heredoc queue.
 *
 * @param queue Pointer to the queue to initialise (borrowed).
 */
void	heredoc_queue_init(t_heredoc_queue *queue);

/**
 * @ingroup heredoc
 * @brief Frees a heredoc queue and every item it still holds.
 *
 * Releases each remaining item through heredoc_queue_item_free() and the queue
 * storage itself.
 *
 * @param queue Pointer to the queue to free (borrowed).
 */
void	heredoc_queue_free(t_heredoc_queue *queue);

/**
 * @ingroup heredoc
 * @brief Appends a heredoc item to the back of the queue.
 *
 * The item is copied into the queue by value; the queue thereby takes
 * ownership of the item's path and delimiter pointers.
 *
 * @param queue Pointer to the queue (borrowed).
 * @param item Item to enqueue (its owned pointers are transferred to the
 *             queue on success).
 * @return ERR_NO on success, or ERR_LIBC on allocation failure.
 */
t_error	heredoc_queue_push(t_heredoc_queue *queue, t_heredoc_queue_item item);

/**
 * @ingroup heredoc
 * @brief Removes the front heredoc item from the queue.
 *
 * Copies the oldest item into @p item and drops it from the queue, moving
 * ownership of its path and delimiter to the caller.
 *
 * @param queue Pointer to the queue (borrowed).
 * @param item Out-parameter receiving the dequeued item (its pointers become
 *             owned by the caller).
 * @return ERR_NO on success, ERR_EMPTY_STACK if the queue is empty, or
 *         ERR_LIBC on failure.
 */
t_error	heredoc_queue_pop(t_heredoc_queue *queue, t_heredoc_queue_item *item);

#endif
