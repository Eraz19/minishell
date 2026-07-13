#ifndef LOADER_CONTEXT__H
# define LOADER_CONTEXT__H

# include "context.h"
# include "loader_.h"

/** @defgroup expander_loader_context Expander loader contexts
 *  @brief Pending-context detection and the open-substitution stack of
 *         the loader.
 *
 *  The next context to enter is the bottom item of the loader's pending
 *  stack; entering a substitution moves that item onto the loading
 *  stack, whose top stays exposed as @c loader->context_item until the
 *  span is left.
 */

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup expander_loader_context
 * @brief Tells whether the read offset is at the start of the next
 *        pending context (the bottom item of @c loader->stack) and, when
 *        the stack is not empty, exposes that item.
 *
 * @note A lookup failure is recorded in @c loader->err and reported as
 *       @c false, not returned.
 * @param loader Loader state (borrowed).
 * @param item Set to the bottom pending item when the stack is not
 *             empty, untouched otherwise; @c loader->stack keeps
 *             ownership (borrowed).
 */
bool	is_context_start(t_loader *loader, t_context_stack_item **item);

/**
 * @ingroup expander_loader_context
 * @brief Tells whether the read offset starts a pending span loaded as
 *        quoting (see @ref is_quoting_type).
 *
 * @param loader Loader state (borrowed).
 */
bool	is_quoting_start(t_loader *loader);

/**
 * @ingroup expander_loader_context
 * @brief Tells whether @p context is loaded as quoting:
 *        @c CONTEXT_SQUOTE, @c CONTEXT_DQUOTE, @c CONTEXT_DOLLAR_SQUOTE
 *        or @c CONTEXT_HEREDOC.
 *
 * @note Unlike @ref is_context_quoting, this includes
 *       @c CONTEXT_HEREDOC: the loader tags here-document bodies as
 *       quoted.
 * @param context Context to classify.
 */
bool	is_quoting_type(t_context context);

/**
 * @ingroup expander_loader_context
 * @brief Tells whether the read offset starts a pending substitution
 *        span (any pending context @ref is_quoting_type rejects).
 *
 * @param loader Loader state (borrowed).
 */
bool	is_substitution_start(t_loader *loader);

/**
 * @ingroup expander_loader_context
 * @brief Leaves the innermost open substitution: pops and frees the top
 *        of the loading stack, then re-aims @c loader->context_item at
 *        the new top, or @c NULL when none is left.
 *
 * @param loader Loader state (borrowed).
 * @return @c ERR_EMPTY_STACK if the loading stack is empty, @c ERR_LIBC
 *         if the removal fails, @c ERR_INDEX_OUT_OF_BOUND if the new
 *         top lookup fails, @c ERR_NO on success.
 */
t_error	loader_pop_context(t_loader *loader);

/**
 * @ingroup expander_loader_context
 * @brief Enters the next pending substitution: moves the bottom item of
 *        the pending stack onto the loading stack (which takes its
 *        ownership) and aims @c loader->context_item at it.
 *
 * @warning A no-op when the pending stack is empty: the current
 *          @c loader->err is returned and @c context_item is left
 *          unchanged. On a failed push the moved item is freed.
 * @param loader Loader state (borrowed).
 * @return @c ERR_LIBC if the pop or the push fails, otherwise the
 *         current @c loader->err (@c ERR_NO in a healthy run).
 */
t_error	loader_push_context(t_loader *loader);

#endif
