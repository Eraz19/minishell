/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:23:18 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 12:23:19 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "error.h"
# include "libft.h"
# include "token.h"
# include "word_.h"

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
 *  (@ref expand_token, @ref expand_token_merged, @ref expand_str)
 *  requalifies
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

	EXP_HEREDOC				= (1u << 9),	/**< Re-lex the raw string of
												 @ref expand_str with the
												 here-document rules
												 (POSIX 2.7.4). */
}	t_exp_flag;

/**
 * @ingroup expander
 * @typedef t_expansion
 * @brief Result of a word expansion: the fields in order, backed by a
 *        @ref t_vector of @ref t_string values owned by the expansion.
 */
typedef t_vector	t_expansion;

// vector of t_expansion
typedef t_vector	t_expansions;

/* ************************************************************************* */
/*                                LIFE CYCLE                                 */
/* ************************************************************************* */

/**
 * @ingroup expander_field
 * @brief Frees @p fields and every word it owns.
 *
 * @param fields Already initialized container (borrowed).
 */
void	fields_free(t_fields *fields);

void	cmd_expansions_init(t_expansions *expansions);
void	cmd_expansions_free(t_expansions *expansions);

/* ************************************************************************* */
/*                                   FLAGS                                   */
/* ************************************************************************* */

t_exp_flag	expansion_flags_regular(void);
t_exp_flag	expansion_flags_assignment(void);
t_exp_flag	expansion_flags_case(void);
t_exp_flag	expansion_flags_redirection(void);
t_exp_flag	expansion_flags_heredoc_body(void);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

t_error expand_str_merged(
			t_string *out,
			const t_string *src,
			int *exit_status,
			t_exp_flag flags);

t_error expand_str(
			t_expansion *out,
			const t_string *src,
			int *exit_status,
			t_exp_flag flags);

/**
 * @ingroup expander
 * @brief Expands a word token, using the quoting and construct spans
 *        recorded in its context stack during tokenization.
 *
 * @param out Expansion initialized by the function; the caller owns it
 *            and must release it with @ref expansion_free (borrowed).
 * @param src Token to expand (borrowed, read-only).
 * @param exit_status Destination for the exit status of the last command
 *                    substitution; unused until command substitution is
 *                    implemented (borrowed).
 * @param flags Expansions to apply.
 * @return Same contract as @ref expand_str.
 */
t_error	expand_token(
			t_expansion *out,
			t_token *src,
			int *exit_status,
			t_exp_flag flags);

/**
 * @ingroup expander
 * @brief Expands a word token like @ref expand_token, then joins the
 *        resulting fields with the first IFS character.
 *
 * @param out String receiving the joined expansion, initialized by the
 *            function (borrowed).
 * @param src Token to expand (borrowed, read-only).
 * @param exit_status Destination for the exit status of the last command
 *                    substitution; unused until command substitution is
 *                    implemented (borrowed).
 * @param flags Expansions to apply.
 * @return Same contract as @ref expand_str.
 */
t_error	expand_token_merged(
			t_string *out,
			t_token *src,
			int *exit_status,
			t_exp_flag flags);

// TODO: doc
t_error	expand_token_word(
			t_fields *out,
			t_token *src,
			int *exit_status,
			t_exp_flag flags);

/**
 * @ingroup expander
 * @brief Matches the first @p len characters of @p str against the
 *        annotated pattern word @p pattern (POSIX 2.13.1): a
 *        metacharacter that is quoted or escaped matches literally, an
 *        unquoted one — including in unquoted expansion results — is
 *        active.
 *
 * @note Only the first @p len characters of @p str are read, so @p str
 *       need not be NUL-terminated; the whole slice must match the whole
 *       @p pattern.
 * @param match Set to the match outcome; @c false on error (borrowed).
 * @param pattern Annotated pattern word, typically from
 *                @ref expand_token_word (borrowed, read-only).
 * @param str Characters to match, at least @p len long (borrowed,
 *            read-only).
 * @param len Number of characters of @p str to match.
 * @return @c ERR_LIBC (printed) on system failure; @c ERR_INTERNAL
 *         (printed) on internal inconsistency; @c ERR_NO on success.
 */
t_error	word_match_pattern(
			bool *match,
			const t_word *pattern,
			const char *str,
			size_t len);

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

t_error	expansion_get(t_string *out, const t_expansion *expansion, size_t i);

// TODO: doc (frees src anyway)
// @ret ERR_INTERNAL / ERR_LIBC
t_error	expansion_merge(
			const char *raw_value,
			const char *posix_citation,
			t_expansion *src,
			t_string *out);
			
t_error expansion_take(t_expansion *exp, size_t i, t_string *out);

#endif
