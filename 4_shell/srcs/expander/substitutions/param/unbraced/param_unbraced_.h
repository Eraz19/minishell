/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_unbraced_.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:47:44 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 17:47:45 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARAM_UNBRACED__H
# define PARAM_UNBRACED__H

# include "expander_.h"

/** @defgroup expander_param_unbraced Expander unbraced parameter expansion
 *  @brief The brace-less form of parameter expansion: $name, single-digit
 *         positionals and the special parameters.
 */

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup expander_param_unbraced
 * @brief Entry point for a brace-less parameter expansion: strips the
 *        leading '$', then expands either the whole positional list
 *        ($@ / $*) or a single parameter.
 *
 * A single parameter is a name run ('_' or alpha, then '_' or alnum), one
 * digit ($0..$9) or one special character ($?, $#, $-, $$, $!). An unset
 * parameter expands to an empty result. Every produced item is stamped
 * @c is_expand_res so it is never rescanned for substitution.
 *
 * @note $@ emits each positional parameter as its own field; $* joins
 *       them with the first IFS character. Inside a braced-parameter
 *       operand (@c expander->in_operand), $@ joins like $*.
 *
 * @param expander Expander state positioned on the '$' item (borrowed).
 * @return @c ERR_POSIX_EXPANSION (printed) on a nounset violation or
 *         an invalid parameter name; @c ERR_INTERNAL (printed by the
 *         env module) when the shell parameters are unavailable;
 *         @c ERR_LIBC on allocation failure; @c ERR_NO on success.
 */
t_error	expand_unbraced(t_expander *expander);

#endif
