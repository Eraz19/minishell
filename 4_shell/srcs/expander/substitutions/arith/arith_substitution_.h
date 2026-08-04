/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arith_substitution_.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:46:18 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 17:46:19 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARITH_SUBSTITUTION__H
# define ARITH_SUBSTITUTION__H

# include "expander_.h"

/** @defgroup expander_arith Arithmetic expansion
 *  @brief POSIX 2.6.4: @c $((expression)), expanded then evaluated.
 *
 *  The expression is extracted and expanded (parameter and command
 *  substitution) by a nested expander run; its evaluation
 *  (@c compute_arith_expression) is a stub reporting
 *  @c ERR_NOT_IMPLEMENTED (printed) until the arithmetic parser is
 *  implemented.
 */

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup expander_arith
 * @brief Expands then evaluates one arithmetic construct.
 *
 * @warning Evaluation is a stub: the call always ends with
 *          @c ERR_NOT_IMPLEMENTED (printed) after the expression's own
 *          expansion; the expander qualifier turns it into
 *          @c ERR_INTERNAL.
 * @param expander Expander state (borrowed).
 * @return @c ERR_NOT_IMPLEMENTED (printed); before evaluation:
 *         @c ERR_LIBC, @c ERR_EMPTY_STACK, @c ERR_INDEX_OUT_OF_BOUND, or
 *         any raw error of the nested expansion run.
 */
t_error	arith_substitution(t_expander *expander);

/**
 * @ingroup expander_arith
 * @brief Tells whether the current item starts an arithmetic construct
 *        and @c EXP_ARITH is set.
 *
 * @param current_item Item at the current position (borrowed, read-only).
 * @param flags Active expansion flags.
 */
bool	is_arith_substitution(t_word_item *current_item, uint flags);

#endif
