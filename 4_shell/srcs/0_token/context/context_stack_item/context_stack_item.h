/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context_stack_item.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 15:25:29 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 15:25:30 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTEXT_STACK_ITEM_H
# define CONTEXT_STACK_ITEM_H

# include <stddef.h>
# include "error.h"

/* ************************************************************************* */
/*                                  TYPES                                    */
/* ************************************************************************* */

/**
 * @ingroup lexer
 * @enum e_context
 * @brief Kind of quoting or expansion construct a context span covers.
 *
 * @note @c CONTEXT_NONE is the scan-word baseline template: it never
 *       enters a token's context stack.
 */
typedef enum e_context
{
	CONTEXT_NONE,
	CONTEXT_SQUOTE,
	CONTEXT_DQUOTE,
	CONTEXT_DOLLAR_SQUOTE,
	CONTEXT_BACKTICK,
	CONTEXT_CMD_SUB,
	CONTEXT_ARITH,
	CONTEXT_PARAM,
	CONTEXT_HEREDOC,
}	t_context;

/**
 * @ingroup lexer
 * @struct s_context_stack_item
 * @brief One construct span inside a token's value: which construct and
 *        the inclusive index range it covers. Closed spans stay in the
 *        token's context stack for the expander.
 *
 * @warning @c end doubles as the open/closed marker: @ref
 *          context_stack_item_init sets it to the @c SIZE_MAX sentinel
 *          ("still open") and the closing scan stamps the real index.
 *          Every successful scan path MUST stamp @c end before the token
 *          reaches the expander — its span walk is inclusive
 *          (@c i @c <= @c end), so a leftover sentinel walks out of
 *          bounds. A legitimate stamp can never collide with the
 *          sentinel: offsets are bounded by the token value length,
 *          itself strictly below the 128*2^k buffer capacities.
 *
 * @var s_context_stack_item::end Index of the last character of the span
 *      in the token value, stamped at closing; @c SIZE_MAX while the
 *      construct is still open.
 * @var s_context_stack_item::start Index of the first character of the
 *      span in the token value.
 * @var s_context_stack_item::context Construct kind of the span.
 */
typedef struct s_context_stack_item
{
	size_t		end;
	size_t		start;
	t_context	context;
}	t_context_stack_item;

/* ************************************************************************* */
/*                                LIFE_CYCLE                                 */
/* ************************************************************************* */

/**
 * @ingroup lexer
 * @brief Allocates a zeroed item marked open: @p context set and @c end
 *        initialized to the @c SIZE_MAX open sentinel.
 *
 * @param item Receives the allocated item; initialized by the function
 *             (ownership taken by the caller).
 * @param context Construct kind of the new span.
 * @return @c ERR_NO on success, @c ERR_LIBC on allocation failure.
 */
t_error	context_stack_item_init(t_context_stack_item **item, t_context context);

/**
 * @ingroup lexer
 * @brief Frees the item pointed to by @p item.
 *
 * @param item Pointer to the @ref t_context_stack_item pointer to free,
 *             as stored in a context stack slot (borrowed).
 */
void	context_stack_item_free(void *item);

#endif
