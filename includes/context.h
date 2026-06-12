/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 17:01:23 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/11 18:55:22 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTEXT_H
# define CONTEXT_H

# include "error.h"
# include "libft.h"

/** @defgroup context Context API
 *  @brief Quoting and expansion contexts recognised while scanning input.
 *
 *  As the scanner walks the input it tracks the nested constructs currently
 *  open on a context stack (e.g. inside "...", $(...) or $((...))). Each
 *  context type exposes up to three predicates following a shared naming
 *  convention:
 *  - is_context_<x>_start(str): does @p str begin an <x> construct?
 *  - is_context_<x>_ending(c, arg): is @p c the closing delimiter of <x>?
 *  - is_in_context_<x>_whitelist(c): inside <x>, does @p c keep a special
 *    meaning (and therefore still need processing)?
 *
 *  Ending predicates share the signature bool(char, void *) so they can be
 *  held in a single function pointer; the void * carries optional state and
 *  is unused by every context except arithmetic (its nesting depth).
 */

/**
 * @ingroup context
 * @enum e_context
 * @brief A quoting or expansion construct the scanner can be inside of.
 */
typedef enum e_context
{
	NONE_,			/**< Top level, outside any quoting or expansion. */
	SQUOTE,			/**< Single quotes: '...'. */
	DQUOTE,			/**< Double quotes: "...". */
	DOLLAR_SQUOTE,	/**< ANSI-C quoting: $'...'. */
	BACKTICK,		/**< Backquote command substitution: `...`. */
	CMD_SUB,		/**< Command substitution: $(...). */
	ARITH,			/**< Arithmetic expansion: $((...)). */
	PARAM,			/**< Parameter expansion: ${...}. */
}	t_context;

/**
 * @ingroup context
 * @brief Stack of open contexts, innermost on top (a vector of t_context).
 */
typedef t_vector	t_context_stack;

/**
 * @ingroup context
 * @brief Initialises an empty context stack.
 *
 * @param stack Pointer to the stack to initialise (borrowed).
 */
void	context_stack_init(t_context_stack *stack);

/**
 * @ingroup context
 * @brief Frees the context stack (its elements are plain values).
 *
 * @param stack Pointer to the stack to free (borrowed).
 */
void	context_stack_free(t_context_stack *stack);

/**
 * @ingroup context
 * @brief Pops the innermost context off the stack.
 *
 * @param stack Pointer to the stack (borrowed).
 * @return ERR_NO on success, ERR_EMPTY_STACK if the stack is empty.
 */
t_error	context_stack_pop(t_context_stack *stack);

/**
 * @ingroup context
 * @brief Reads the innermost context without removing it.
 *
 * @param stack Pointer to the stack (borrowed).
 * @param item Out-parameter receiving the top context.
 * @return ERR_NO on success, ERR_EMPTY_STACK if the stack is empty.
 */
t_error	context_stack_get(t_context_stack *stack, t_context *item);

/**
 * @ingroup context
 * @brief Pushes a context, making it the new innermost one.
 *
 * @param stack Pointer to the stack (borrowed).
 * @param item Context to push.
 * @return ERR_NO on success, ERR_LIBC on allocation failure.
 */
t_error	context_stack_push(t_context_stack *stack, t_context item);

/**
 * @ingroup context
 * @brief Tests whether a character is a blank (space or tab).
 *
 * @param c Character to test.
 * @return true if @p c is a space or a tab.
 */
bool	is_blank(char c);

/**
 * @ingroup context
 * @brief Whitelist for the top-level context: every character is processed.
 *
 * @param c Character to test (ignored).
 * @return Always true.
 */
bool	is_in_context_none_whitelist(char c);

/**
 * @ingroup context
 * @brief Tests whether the top-level context ends at @p c.
 *
 * @param c Character to test.
 * @param _ Unused; present for the shared ending-predicate signature.
 * @return true at the end of input (NUL).
 */
bool	is_context_none_ending(char c, void *_);

/**
 * @ingroup context
 * @brief Tests whether @p str begins an arithmetic expansion ($((  ).
 *
 * @param str Input cursor to test.
 * @return true if @p str starts with "$((".
 */
bool	is_context_arith_start(char *str);

/**
 * @ingroup context
 * @brief Tests whether an arithmetic expansion ends at @p c.
 *
 * @param c Character to test.
 * @param nesting_depth Pointer to the current parenthesis depth (size_t *);
 *                      the context ends only at the outermost ')'.
 * @return true if @p c is ')' and the nesting depth is zero.
 */
bool	is_context_arith_ending(char c, void *nesting_depth);

/**
 * @ingroup context
 * @brief Tests whether @p str begins a backquote substitution (`).
 *
 * @param str Input cursor to test.
 * @return true if @p str starts with a backquote.
 */
bool	is_context_backtick_start(char *str);

/**
 * @ingroup context
 * @brief Whitelist of characters special inside a backquote substitution.
 *
 * @param c Character to test.
 * @return true for '\\', '$' and '`'.
 */
bool	is_in_context_backtick_whitelist(char c);

/**
 * @ingroup context
 * @brief Tests whether a backquote substitution ends at @p c.
 *
 * @param c Character to test.
 * @param _ Unused; present for the shared ending-predicate signature.
 * @return true if @p c is a backquote.
 */
bool	is_context_backtick_ending(char c, void *_);

/**
 * @ingroup context
 * @brief Extended special set for backquotes nested inside double quotes.
 *
 * @param c Character to test.
 * @return true for '$', '`', '"' and '\\'.
 */
bool	is_in_context_backtick_special_whitelist(char c);

/**
 * @ingroup context
 * @brief Tests whether @p str begins a command substitution ($(  ).
 *
 * @param str Input cursor to test.
 * @return true if @p str starts with "$(".
 */
bool	is_context_cmd_sub_start(char *str);

/**
 * @ingroup context
 * @brief Tests whether @p str begins a parameter expansion (${  ).
 *
 * @param str Input cursor to test.
 * @return true if @p str starts with "${".
 */
bool	is_context_param_start(char *str);

/**
 * @ingroup context
 * @brief Whitelist for a parameter expansion: every character is processed.
 *
 * @param c Character to test (ignored).
 * @return Always true.
 */
bool	is_in_context_param_whitelist(char c);

/**
 * @ingroup context
 * @brief Tests whether a parameter expansion ends at @p c.
 *
 * @param c Character to test.
 * @param _ Unused; present for the shared ending-predicate signature.
 * @return true if @p c is '}'.
 */
bool	is_context_param_ending(char c, void *_);

/**
 * @ingroup context
 * @brief Detects which expansion construct, if any, @p str begins.
 *
 * Tested in priority order: parameter, arithmetic, command substitution,
 * backquote.
 *
 * @param str Input cursor to test.
 * @param context Out-parameter receiving the detected context on a match.
 * @return true if @p str begins an expansion (and @p context was set).
 */
bool	is_expansion_context(char *str, t_context *context);

/**
 * @ingroup context
 * @brief Tests whether @p str begins ANSI-C quoting ($'  ).
 *
 * @param str Input cursor to test.
 * @return true if @p str starts with "$'".
 */
bool	is_context_dollar_squote_start(char *str);

/**
 * @ingroup context
 * @brief Whitelist for ANSI-C quoting: every character is processed.
 *
 * @param c Character to test (ignored).
 * @return Always true.
 */
bool	is_in_context_dollar_squote_whitelist(char c);

/**
 * @ingroup context
 * @brief Tests whether ANSI-C quoting ends at @p c.
 *
 * @param c Character to test.
 * @param _ Unused; present for the shared ending-predicate signature.
 * @return true if @p c is a single quote.
 */
bool	is_context_dollar_squote_ending(char c, void *_);

/**
 * @ingroup context
 * @brief Tests whether @p str begins a double-quoted section (").
 *
 * @param str Input cursor to test.
 * @return true if @p str starts with a double quote.
 */
bool	is_context_dquote_start(char *str);

/**
 * @ingroup context
 * @brief Whitelist of characters special inside double quotes.
 *
 * @param c Character to test.
 * @return true for '$', '`', '\\' and '"'.
 */
bool	is_in_context_dquote_whitelist(char c);

/**
 * @ingroup context
 * @brief Tests whether a double-quoted section ends at @p c.
 *
 * @param c Character to test.
 * @param _ Unused; present for the shared ending-predicate signature.
 * @return true if @p c is a double quote.
 */
bool	is_context_dquote_ending(char c, void *_);

/**
 * @ingroup context
 * @brief Tests whether @p str begins a single-quoted section (').
 *
 * @param str Input cursor to test.
 * @return true if @p str starts with a single quote.
 */
bool	is_context_squote_start(char *str);

/**
 * @ingroup context
 * @brief Whitelist for single quotes: nothing is special inside them.
 *
 * @param c Character to test (ignored).
 * @return Always false.
 */
bool	is_in_context_squote_whitelist(char c);

/**
 * @ingroup context
 * @brief Tests whether a single-quoted section ends at @p c.
 *
 * @param c Character to test.
 * @param _ Unused; present for the shared ending-predicate signature.
 * @return true if @p c is a single quote.
 */
bool	is_context_squote_ending(char c, void *_);

/**
 * @ingroup context
 * @brief Tests whether @p c closes the given quoting context.
 *
 * Dispatches to the matching is_context_<x>_ending() for SQUOTE, DQUOTE and
 * DOLLAR_SQUOTE.
 *
 * @param c Character to test.
 * @param context Quoting context to test against.
 * @return true if @p c closes @p context, false for non-quoting contexts.
 */
bool	is_quoting_ending(char c, t_context context);

/**
 * @ingroup context
 * @brief Detects which quoting construct, if any, @p str begins.
 *
 * Tested in priority order: single quote, ANSI-C quote, double quote.
 *
 * @param str Input cursor to test.
 * @param context Out-parameter receiving the detected context on a match.
 * @return true if @p str begins a quoting context (and @p context was set).
 */
bool	is_quoting_context(char *str, t_context *context);

/**
 * @ingroup context
 * @brief Tests @p c against the whitelist of the given quoting context.
 *
 * Dispatches to the matching is_in_context_<x>_whitelist() for NONE_, SQUOTE,
 * DQUOTE and DOLLAR_SQUOTE.
 *
 * @param c Character to test.
 * @param context Quoting context whose whitelist to use.
 * @return true if @p c is special within @p context.
 */
bool	is_in_quoting_whitelist(char c, t_context context);

#endif
