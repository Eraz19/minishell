/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expansion_.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:47:52 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 17:47:53 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARAM_EXPANSION__H
# define PARAM_EXPANSION__H

# include "expander_.h"

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup expander_priv
 * @brief Closes the field being built for the @c i-th positional of a
 *        @c $@ expansion and merges @p word_exp as the start of the next
 *        one; when the expansion is double-quoted, synthetic @c "
 *        delimiters (see @ref simple_dquote_item) wrap the boundary so
 *        empty positionals survive field splitting.
 *
 * @param expander Expander state receiving the fields (borrowed).
 * @param word_exp Items of the @c i-th positional, merged by shallow
 *                 copy; the caller frees the container afterwards
 *                 (borrowed).
 * @param opt Metadata of the @c $@ construct.
 * @param i Index of the positional; @c 0 merges without closing a field.
 * @return @c ERR_LIBC on allocation failure, @c ERR_NO on success.
 */
t_error		append_param_as_field(
				t_expander *expander,
				t_word word_exp,
				t_word_item_opt opt,
				size_t i);

/**
 * @ingroup expander_priv
 * @brief Drops the quoted-null of a @c "$@" with zero positionals: when
 *        the word-head construct is directly wrapped by a source @c "
 *        pair (tail of @c word_exp, second item of @c word), both quote
 *        items are removed so the expansion yields zero fields
 *        (POSIX 2.5.2).
 *
 * @param expander Expander state (borrowed).
 * @return @c ERR_NO, including when the quotes are not adjacent;
 *         asserts on an internal inconsistency.
 */
t_error		drop_quoted_null_at(t_expander *expander);

/**
 * @ingroup expander_priv
 * @brief Emits the positional parameters: one field per positional for
 *        @c @, joined with the first IFS character for @c * — and for
 *        @c @ inside an operand that flattens its result
 *        (@c expander->in_operand).
 *
 * @param expander Expander state receiving the result (borrowed).
 * @param c Positional symbol, @c '@' or @c '*'.
 * @param opt Metadata stamped onto the produced items.
 * @return @c ERR_LIBC on allocation failure; @c ERR_INTERNAL (printed
 *         by the env module) if
 *         the shell parameters are unavailable; @c ERR_NO on success.
 */
t_error		emit_positionals(t_expander *expander, char c, t_word_item_opt opt);

/**
 * @ingroup expander_priv
 * @brief Extracts the parameter name at the word head and consumes it:
 *        a name run for alphabetic/underscore starts, a digit run for
 *        braced positionals, a single character otherwise (specials).
 *
 * @param expander Expander state whose word is consumed (borrowed).
 * @param param_name Name extracted, initialized by the function
 *                   (borrowed).
 * @param braced Whether the @c ${...} form is being parsed (multi-digit
 *               positionals are only recognized there).
 * @return @c ERR_LIBC on allocation failure; asserts
 *         on an internal inconsistency; @c ERR_NO on success.
 */
t_error		get_param_name(
				t_expander *expander,
				t_string *param_name,
				bool braced);

/**
 * @ingroup expander_priv
 * @brief Tells whether the word head starts a parameter expansion:
 *        @c EXP_PARAM active, an unquoted unescaped @c $ outside foreign
 *        constructs, followed by @c { or a valid parameter character.
 *
 * @param expander Expander state (borrowed).
 * @param current_item Item at the word head (borrowed, read-only).
 */
bool		is_param_expansion(t_expander *expander, t_word_item *current_item);

/**
 * @ingroup expander_priv
 * @brief Substitutes the parameter expansion at the word head, routing
 *        @c ${...} to the braced handler and @c $name / @c $N / specials
 *        to the unbraced one.
 *
 * @param expander Expander state (borrowed).
 * @return Raw braced/unbraced errors: @c ERR_LIBC,
 *         @c ERR_PARAM_BAD_SUBSTITUTION, @c ERR_PARAM_NULL_OR_UNSET,
 *         @c ERR_VAR_INVALID_NAME, @c ERR_POSIX_ASSIGNMENT (printed by
 *         the env module) or @c ERR_INTERNAL (printed by the env
 *         module); @c ERR_NO on
 *         success.
 */
t_error		param_expansion(t_expander *expander);

/**
 * @ingroup expander_priv
 * @brief Raises the @c set @c -u (nounset) error for an unset parameter:
 *        no-op returning @c ERR_NO when the option is off or @p name is
 *        @c @ or @c * (exempt per POSIX).
 *
 * @param expander Expander state; its @c err receives the result
 *                 (borrowed).
 * @param name Name of the unset parameter (borrowed, read-only).
 * @return @c ERR_POSIX_EXPANSION (printed with @p name, requalified in
 *         place) when nounset is active; @c ERR_INTERNAL (printed by
 *         the env module) if the
 *         options are unavailable; @c ERR_NO otherwise.
 */
t_error		param_nounset_error(t_expander *expander, const char *name);

/**
 * @ingroup expander_priv
 * @brief Builds a synthetic @c " item from @p opt with
 *        @c is_expand_res cleared, so the final quote removal strips it
 *        like a source quote.
 *
 * @param opt Metadata of the construct the item belongs to.
 * @return The synthetic double-quote item.
 */
t_word_item	simple_dquote_item(t_word_item_opt opt);

#endif
