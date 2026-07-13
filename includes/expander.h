#ifndef EXPANDER_H
# define EXPANDER_H

# include "error.h"
# include "libft.h"
# include "token.h"

/** @defgroup expander Expander API
 *  @brief POSIX word expansions (XCU 2.6): tilde, parameter, command and
 *         arithmetic expansion, field splitting, pathname expansion and
 *         quote removal, applied in that order.
 *
 *  The caller selects the expansions with a @ref t_exp_flag bitset and
 *  receives a @ref t_expansion: the resulting fields in order. The word's
 *  quoting and construct spans come from the token's context stack (or
 *  are re-lexed for raw strings and here-document bodies).
 *
 *  ERROR CONTRACT
 *
 *  No caller needs the specific expansion error types, so every endpoint
 *  (@ref expand_token, @ref expand_str, @ref expand_heredoc) requalifies
 *  through @c expander_error_qualify (see expander_.h) before returning:
 *
 *  - user-facing expansion failures (bad substitution, @c ${var?} on an
 *    unset parameter, an unassignable name in @c ${var=v}, an
 *    unterminated construct discovered at expansion time) are printed
 *    and become @c ERR_POSIX_EXPANSION (POSIX 2.8.1 expansion error);
 *  - a readonly-variable assignment (@c ${RO:=v}) is printed and becomes
 *    @c ERR_POSIX_ASSIGNMENT (POSIX 2.8.1 assignment error);
 *  - internal inconsistencies and unimplemented substitutions (command,
 *    backquote and arithmetic evaluation are stubs that report
 *    @c ERR_NOT_IMPLEMENTED, printed with the function name) become
 *    @c ERR_INTERNAL;
 *  - @c ERR_LIBC is printed and kept; fully qualified errors pass
 *    through untouched.
 *
 *  @c ${var?word} diagnostics are printed at production with the
 *  parameter name and the expanded message; @c ERR_QUOTED_TILDE is
 *  internal control flow and never escapes (a quoted tilde stays
 *  literal).
 *
 *  @warning An interactive shell shall not exit on
 *           @c ERR_POSIX_EXPANSION / @c ERR_POSIX_ASSIGNMENT
 *           (POSIX 2.8.1): the runner currently recovers only on
 *           @c ERR_POSIX_SYNTAX and must be extended.
 */

/**
 * @ingroup expander
 * @enum e_exp_flags
 * @brief Expansions to apply, combined as a bitset.
 */
typedef enum e_exp_flags
{
	EXP_TILDE_NORMAL		= (1u << 0),	/**< Tilde prefix of the word. */
	EXP_TILDE_ASSIGNMENT	= (1u << 1),	/**< Tilde after '=' and ':' in
												 an assignment value. */
	EXP_DOLLAR_SQUOTE		= (1u << 2),	/**< ANSI-C quoting $'...'. */
	EXP_PARAM				= (1u << 3),	/**< Parameter expansion. */
	EXP_CMD_SUB				= (1u << 4),	/**< Command and backquote
												 substitution. */
	EXP_ARITH				= (1u << 5),	/**< Arithmetic expansion. */
	EXP_FIELD_SPLIT			= (1u << 6),	/**< IFS field splitting. */
	EXP_PATH_NAME			= (1u << 7),	/**< Pathname expansion. */
	EXP_QUOTE_REMOVAL		= (1u << 8),	/**< Quote removal. */
}	t_exp_flag;

/**
 * @ingroup expander
 * @typedef t_expansion
 * @brief Result of a word expansion: the fields in order, backed by a
 *        @ref t_vector of @ref t_string values owned by the expansion.
 */
typedef t_vector	t_expansion;

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup expander
 * @brief Expands a here-document body or any raw text: the string is
 *        re-lexed with here-document semantics to find its constructs,
 *        then expanded with @p flags.
 *
 * @note An empty (or NULL-buffered) @p src expands to a single empty
 *       field, per POSIX.
 * @param out Expansion initialized by the function; the caller owns it
 *            and must release it with @ref expansion_free (borrowed).
 * @param src Text to expand (borrowed, read-only).
 * @param flags Expansions to apply.
 * @return @c ERR_POSIX_EXPANSION (printed) on a user-facing expansion
 *         failure; @c ERR_POSIX_ASSIGNMENT (printed) on a readonly
 *         assignment; @c ERR_INTERRUPTED when a signal interrupts the
 *         work; @c ERR_LIBC (printed) on system failure; @c ERR_INTERNAL
 *         (printed) on internal inconsistency or unimplemented
 *         substitution; @c ERR_NO on success.
 */
t_error	expand_heredoc(t_expansion *out, const t_string *src, t_exp_flag flags);

/**
 * @ingroup expander
 * @brief Expands a raw C-string value (prompts, any text that is not a
 *        token); alias of @ref expand_heredoc.
 *
 * @param out Expansion initialized by the function; the caller owns it
 *            and must release it with @ref expansion_free (borrowed).
 * @param src Text to expand (borrowed, read-only).
 * @param flags Expansions to apply.
 * @return Same contract as @ref expand_heredoc.
 */
t_error expand_str(t_expansion *out, const t_string *src, t_exp_flag flags);

/**
 * @ingroup expander
 * @brief Expands a word token, using the quoting and construct spans
 *        recorded in its context stack during tokenization.
 *
 * @param out Expansion initialized by the function; the caller owns it
 *            and must release it with @ref expansion_free (borrowed).
 * @param src Token to expand (borrowed, read-only).
 * @param flags Expansions to apply.
 * @return Same contract as @ref expand_heredoc.
 */
t_error	expand_token(t_expansion *out, const t_token *src, t_exp_flag flags);

/* ************************************************************************* */
/*                              EXPANSION OPS                                */
/* ************************************************************************* */

/**
 * @ingroup expander
 * @brief Frees every field of @p expansion and its backing storage.
 *
 * @param expansion Already initialized expansion (borrowed).
 */
void	expansion_free(t_expansion *expansion);

/**
 * @ingroup expander
 * @brief Frees the expansion pointed to by @p expansion, as
 *        @ref expansion_free does.
 *
 * @note Signature matches the @c vector_free element destructor callback.
 * @param expansion Expansion to free, as an untyped pointer (borrowed).
 */
void	expansion_free_void(void *expansion);

/**
 * @ingroup expander
 * @brief Reads the field at index @p i without removing it.
 *
 * @param out Set to a shallow copy of the field; its text is still owned
 *            by @p expansion, do not free it (borrowed).
 * @param expansion Already initialized expansion (borrowed, read-only).
 * @param i Position of the field to read.
 * @return @c ERR_INDEX_OUT_OF_BOUND if @p i is past the last field,
 *         @c ERR_NO on success.
 */
t_error	expansion_get(t_string *out, const t_expansion *expansion, size_t i);

/**
 * @ingroup expander
 * @brief Removes the field at index @p i and hands it to the caller.
 *
 * @param exp Already initialized expansion (borrowed).
 * @param i Position of the field to take.
 * @param out Set to the removed field; the caller becomes the owner of
 *            its text and must release it with @c string_free (borrowed).
 * @return @c ERR_INDEX_OUT_OF_BOUND if @p i is past the last field,
 *         @c ERR_NO on success.
 */
t_error expansion_take(t_expansion *exp, size_t i, t_string *out);

#endif
