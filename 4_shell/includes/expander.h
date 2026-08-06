/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:23:18 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 18:33:05 by gastesan         ###   ########.fr       */
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
 *  No caller needs the specific expansion error types: every failure is
 *  printed AND requalified in place, where the context is richest, so
 *  the boundary mapping (@c requalify_expander_error — see the audit
 *  above its implementation, expander_error.c) is the identity:
 *
 *  - user-facing expansion failures (bad substitution, @c ${var?} on an
 *    unset parameter, @c set @c -u on an unset parameter, an
 *    unassignable name in @c ${var=v}) are printed at production and
 *    leave as @c ERR_POSIX_EXPANSION (POSIX 2.8.1 expansion error);
 *  - a readonly-variable assignment (@c ${RO:=v}) is printed by the env
 *    module and leaves as @c ERR_POSIX_ASSIGNMENT (POSIX 2.8.1
 *    assignment error);
 *  - the arithmetic evaluation stub and the env instance lookups print
 *    and leave as @c ERR_INTERNAL;
 *  - @c ERR_LIBC leaves raw and unprinted (the runner frontier prints
 *    it); internal inconsistencies are caught by assertions and never
 *    produce an error value.
 *
 *  The complete surface is therefore: @c ERR_NO,
 *  @c ERR_POSIX_EXPANSION, @c ERR_POSIX_ASSIGNMENT,
 *  @c ERR_POSIX_SYNTAX, @c ERR_INTERNAL and @c ERR_LIBC.
 *
 *  @c ${var?word} diagnostics are printed at production with the
 *  parameter name and the expanded message; @c ERR_QUOTED_TILDE is
 *  internal control flow and never escapes (a quoted tilde stays
 *  literal).
 *
 *  @warning An interactive shell shall not exit on
 *           @c ERR_POSIX_EXPANSION / @c ERR_POSIX_ASSIGNMENT
 *           (POSIX 2.8.1): the runner currently recovers only on
 *           @c ERR_POSIX_SYNTAX and must be extended (runner scope:
 *           route both types through @c runner_handle_syntax_errors in
 *           @c 2_runner_handle_errors.c).
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
void		fields_free(t_fields *fields);

/**
 * @ingroup expander
 * @brief Initializes @p expansions as an empty list of expansions (one
 *        per command word).
 *
 * @param expansions List initialized by the function (borrowed).
 */
void		cmd_expansions_init(t_expansions *expansions);

/**
 * @ingroup expander
 * @brief Frees every expansion of @p expansions and its backing storage.
 *
 * @param expansions Already initialized list (borrowed).
 */
void		cmd_expansions_free(t_expansions *expansions);

/* ************************************************************************* */
/*                                   FLAGS                                   */
/* ************************************************************************* */

/**
 * @ingroup expander
 * @brief Flags of a regular command word: every expansion and stage.
 */
t_exp_flag	expansion_flags_regular(void);

/**
 * @ingroup expander
 * @brief Flags of an assignment value: assignment-context tilde, no
 *        field splitting, no pathname expansion (POSIX 2.9.1).
 */
t_exp_flag	expansion_flags_assignment(void);

/**
 * @ingroup expander
 * @brief Flags of a @c case subject or pattern word: no field splitting,
 *        no pathname expansion (POSIX 2.9.4.3).
 */
t_exp_flag	expansion_flags_case(void);

/**
 * @ingroup expander
 * @brief Flags of a redirection target: no field splitting, no pathname
 *        expansion (POSIX 2.7).
 */
t_exp_flag	expansion_flags_redirection(void);

/**
 * @ingroup expander
 * @brief Flags of a here-document body: re-lexed with the here-document
 *        rules, parameter/command/arithmetic expansion only
 *        (POSIX 2.7.4).
 */
t_exp_flag	expansion_flags_heredoc_body(void);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup expander
 * @brief Expands a raw string like @ref expand_str, then joins the
 *        resulting fields with the first IFS character.
 *
 * @param out String receiving the joined expansion, initialized by the
 *            function (borrowed).
 * @param src Raw text to expand; empty yields an empty @p out (borrowed,
 *            read-only).
 * @param exit_status Destination for the exit status of the last command
 *                    substitution (borrowed).
 * @param flags Expansions to apply.
 * @return Same contract as @ref expand_str.
 */
t_error		expand_str_merged(
				t_string *out,
				const t_string *src,
				int *exit_status,
				t_exp_flag flags);

/**
 * @ingroup expander
 * @brief Expands a raw string: the text is first re-lexed to recover its
 *        quoting and construct spans (with the here-document rules when
 *        @c EXP_HEREDOC is set), then expanded like @ref expand_token.
 *
 * @param out Expansion initialized by the function; the caller owns it
 *            and must release it with @ref expansion_free (borrowed).
 * @param src Raw text to expand; empty yields an empty expansion
 *            (borrowed, read-only).
 * @param exit_status Destination for the exit status of the last command
 *                    substitution (borrowed).
 * @param flags Expansions to apply.
 * @return @c ERR_NO on success; @c ERR_POSIX_EXPANSION,
 *         @c ERR_POSIX_ASSIGNMENT, @c ERR_POSIX_SYNTAX or
 *         @c ERR_INTERNAL (printed at production) or @c ERR_LIBC
 *         (unprinted) per the module error contract above.
 */
t_error		expand_str(
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
 *                    substitution (borrowed).
 * @param flags Expansions to apply.
 * @return Same contract as @ref expand_str.
 */
t_error		expand_token(
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
 *                    substitution (borrowed).
 * @param flags Expansions to apply.
 * @return Same contract as @ref expand_str.
 */
t_error		expand_token_merged(
				t_string *out,
				t_token *src,
				int *exit_status,
				t_exp_flag flags);

/**
 * @ingroup expander
 * @brief Expands a word token like @ref expand_token but keeps the
 *        resulting fields as annotated words (quoting metadata
 *        preserved), for consumers that match rather than execute —
 *        @c case patterns through @ref word_match_pattern.
 *
 * @param out Fields initialized by the function; the caller owns them
 *            and must release them with @ref fields_free (borrowed).
 * @param src Token to expand (borrowed, read-only).
 * @param exit_status Destination for the exit status of the last command
 *                    substitution (borrowed).
 * @param flags Expansions to apply.
 * @return Same contract as @ref expand_str.
 */
t_error		expand_token_word(
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
 * @return @c ERR_LIBC (unprinted) on allocation failure; @c ERR_NO on
 *         success.
 */
t_error		word_match_pattern(
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
void		expansion_free(t_expansion *expansion);

/**
 * @ingroup expander
 * @brief Frees the expansion pointed to by @p expansion, as
 *        @ref expansion_free does.
 *
 * @note Signature matches the @c vector_free element destructor callback.
 * @param expansion Expansion to free, as an untyped pointer (borrowed).
 */
void		expansion_free_void(void *expansion);

/**
 * @ingroup expander
 * @brief Sets @p out to a view of field @p i of @p expansion.
 *
 * @warning @p out is a shallow copy aiming into the expansion storage:
 *          it must not be freed and dies with the next mutation of
 *          @p expansion. @p i must be below @c expansion->len
 *          (asserted).
 * @param out Receives the view (borrowed).
 * @param expansion Already initialized, non-empty expansion (borrowed,
 *                  read-only).
 * @param i Field index.
 */
void		expansion_get(
				t_string *out,
				const t_expansion *expansion,
				size_t i);

/**
 * @ingroup expander
 * @brief Merges the fields of @p src into one string separated by the
 *        first IFS character (a space when IFS is unset, nothing when
 *        IFS is null), converting zero fields into an empty string;
 *        both unusual shapes print an unspecified-behaviour notice
 *        citing @p posix_citation. @p src is freed in every case.
 *
 * @param raw_value Original text of the word, for the notice (borrowed,
 *                  read-only).
 * @param posix_citation POSIX clause the notice cites (borrowed,
 *                       read-only).
 * @param src Expansion to consume (borrowed, freed by the call).
 * @param out String receiving the merge, initialized by the function
 *            (borrowed).
 * @return @c ERR_LIBC (printed) on allocation failure; @c ERR_INTERNAL
 *         (printed by the env module) if the shell parameters are
 *         unavailable; @c ERR_NO on success.
 */
t_error		expansion_merge(
				const char *raw_value,
				const char *posix_citation,
				t_expansion *src,
				t_string *out);

/**
 * @ingroup expander
 * @brief Moves field @p i of @p exp into @p out and removes it from the
 *        expansion.
 *
 * @warning @p i must be below @c exp->len (asserted).
 * @param exp Already initialized expansion (borrowed).
 * @param i Field index.
 * @param out Receives the field; the caller owns it and releases it
 *            with @c string_free (borrowed).
 */
void		expansion_take(t_expansion *exp, size_t i, t_string *out);

#endif
