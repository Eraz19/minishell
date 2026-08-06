/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:48:45 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/06 00:21:02 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER__H
# define EXPANDER__H

# include "field_.h"
# include "lexer.h"
# include "expander.h"

/** @defgroup expander_priv Expander internals
 *  @brief Engine state and pipeline behind the expander API.
 *
 *  The pipeline: the loader turns the raw value and its context stack
 *  into a word of annotated characters; @c substitutions rewrites every
 *  construct; field splitting, pathname expansion and quote removal then
 *  transform the fields when their flag is set.
 */

/**
 * @ingroup expander_priv
 * @struct s_expander_args
 * @brief Input of one expansion run.
 *
 * @var s_expander_args::ifs Resolved IFS of the run (see @ref get_ifs);
 *                           borrowed by the run, the caller keeps
 *                           ownership and frees it afterwards.
 * @var s_expander_args::value Raw text to expand (borrowed, read-only).
 * @var s_expander_args::flags Expansions to apply.
 * @var s_expander_args::contexts Quoting and construct spans of
 *                                @c value (borrowed, read-only).
 * @var s_expander_args::exit_status Destination for the exit status of
 *                                   the last command substitution
 *                                   (borrowed).
 * @var s_expander_args::assignment_offset Index of the @c '=' of an
 *                                         assignment word, @c -1
 *                                         otherwise.
 */
typedef struct s_expander_args
{
	t_string		ifs;
	t_string		value;
	t_exp_flag		flags;
	t_ast_vector	*ast_vec;
	t_context_stack	*contexts;
	int				*exit_status;
	ssize_t			assignment_offset;
}	t_expander_args;

typedef struct s_expander
{
	t_string		ifs;
	t_error			err;
	t_word			word;
	t_exp_flag		flags;
	size_t			ast_i;
	t_fields		fields;
	t_ast_vector	*ast_vec;
	t_word			word_exp;
	t_fields		fields_exp;
	bool			in_operand;
	int				*exit_status;
	ssize_t			assignment_offset;
}	t_expander;

/* ************************************************************************* */
/*                                LIFE_CYCLE                                 */
/* ************************************************************************* */

/**
 * @ingroup expander_priv
 * @brief Zeroes @p expander and initializes its fields container.
 *
 * @param expander Expander state initialized by the function (borrowed).
 */
void	expander_init(t_expander *expander);

/**
 * @ingroup expander_priv
 * @brief Loads the annotated word from @p args through the loader and
 *        stores it as the single initial field.
 *
 * @note The IFS of @p args is borrowed for the whole run: the caller
 *       resolves it (@ref get_ifs), keeps ownership and frees it after
 *       the run.
 * @param expander Already initialized expander state (borrowed).
 * @param args Input of the run (borrowed).
 * @return @c ERR_INTERNAL (printed by the env module) if the shell
 *         parameters are unavailable; @c ERR_LIBC on allocation
 *         failure; @c ERR_NO on success (context stack inconsistencies
 *         are caught by assertion).
 */
t_error	expander_load(t_expander *expander, t_expander_args *args);

/**
 * @ingroup expander_priv
 * @brief Frees both words and both field containers of @p expander,
 *        then zeroes it (the borrowed IFS is left to its owner).
 *
 * @param expander Already initialized expander state (borrowed).
 */
void	expander_free(t_expander *expander);

/**
 * @ingroup expander_priv
 * @brief Releases the resources of a raw-string run: the IFS, the value,
 *        the AST vector and the context stack of @p args, then zeroes
 *        it.
 *
 * @warning Only for @ref expand_str / @ref expand_str_merged, which own
 *          all four; the token endpoints borrow everything but the IFS
 *          from the token and must not use this.
 *
 * @param args Input of the run to release (borrowed).
 */
void	expander_args_free(t_expander_args *args);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup expander_priv
 * @brief Prepares a raw-string run: resolves the IFS and re-lexes
 *        @c args->value to recover its quoting and construct spans —
 *        with the here-document rules when @c EXP_HEREDOC is set in
 *        @p flags; the value is freed on failure.
 *
 * @param args Input of the run; its @c value must already be loaded
 *             (borrowed).
 * @param context_out Context stack initialized by the function
 *                    (borrowed).
 * @param ast_vec AST vector initialized by the function (borrowed).
 * @param flags Expansions the run will apply, stored into @p args.
 * @return @c ERR_INTERNAL (printed) if the shell is unavailable;
 *         @c ERR_LIBC on allocation failure; @c ERR_POSIX_SYNTAX
 *         (printed by the scanner) on malformed input; @c ERR_NO on
 *         success.
 */
t_error	prepare_src(
			t_expander_args	*args,
			t_context_stack *context_out,
			t_ast_vector *ast_vec,
			t_exp_flag flags);

/**
 * @ingroup expander_priv
 * @brief Runs one full expansion and joins the resulting fields with the
 *        first IFS character of the run (no separator when IFS is null).
 *
 * @param out String receiving the joined fields, initialized by the
 *            function (borrowed).
 * @param args Input of the run (borrowed).
 * @return Same surface as @ref run_expansion, plus @c ERR_LIBC from
 *         the join; @c ERR_NO on success.
 */
t_error	run_and_merge_expansion(t_string *out, t_expander_args *args);

/**
 * @ingroup expander_priv
 * @brief Runs the expansion pipeline on the loaded fields:
 *        substitutions, then field splitting, pathname expansion and
 *        quote removal when their flag is set.
 *
 * @param expander Loaded expander state (borrowed).
 * @return The first stage error, raw (see @ref requalify_expander_error
 *         for the qualified surface); @c ERR_NO on success.
 */
t_error	expand_word(t_expander *expander);

/**
 * @ingroup expander_priv
 * @brief Matches the first @p len characters of @p str against the whole
 *        POSIX shell pattern @p pattern (POSIX 2.13.1): @c * and @c ?
 *        wildcards, @c \ escapes, bracket expressions (@c ! or @c ^
 *        negation, ranges, character classes, collating symbols and
 *        equivalence classes).
 *
 * @note Only the first @p len characters of @p str are read, so @p str
 *       need not be NUL-terminated; the whole slice must match the whole
 *       @p pattern. Quoting is expressed with @c \ escapes: render an
 *       annotated word with @ref pattern_from_word first.
 * @param pattern NUL-terminated pattern C-string (borrowed, read-only).
 * @param str Characters to match, at least @p len long (borrowed,
 *            read-only).
 * @param len Number of characters of @p str to match.
 */
bool	match_pattern(const char *pattern, const char *str, size_t len);

/**
 * @ingroup expander_priv
 * @brief Renders the annotated word @p pattern into the
 *        @ref match_pattern dialect: a metacharacter that is quoted or
 *        escaped (POSIX 2.13.1) is backslash-escaped so it matches
 *        literally, an unquoted one stays active — including in
 *        unquoted expansion results.
 *
 * @param out String receiving the rendered pattern, initialized by the
 *            function and freed on failure (borrowed).
 * @param pattern Annotated pattern word (borrowed, read-only).
 * @param res_quoted Whether a quoted expansion result renders literally
 *                   (case words) instead of following the local quoting
 *                   (${x#pat} operands, POSIX 2.6.2).
 * @return @c ERR_LIBC on allocation failure; @c ERR_NO on success.
 */
t_error	pattern_from_word(
			t_string *out,
			const t_word *pattern,
			bool res_quoted);

/**
 * @ingroup expander_priv
 * @brief Runs one full expansion: loads the annotated word from @p args,
 *        applies the substitutions and the flagged stages, and stores
 *        the resulting fields in @p expansion.
 *
 * @note On failure @p expansion is left empty: releasing it is safe but
 *       not required.
 * @param expansion Expansion initialized by the function; the caller
 *                  owns it and must release it with @c expansion_free
 *                  (borrowed).
 * @param args Input of the run; its IFS stays owned by the caller
 *             (borrowed).
 * @return Errors requalified in place at their production sites (see
 *         the audit above @ref requalify_expander_error,
 *         expander_error.c): @c ERR_POSIX_EXPANSION (printed) on a
 *         user-facing expansion failure; @c ERR_POSIX_ASSIGNMENT
 *         (printed by the env module) on a readonly ${var=w}
 *         assignment; @c ERR_INTERNAL (printed) from the arithmetic
 *         evaluation stub; @c ERR_LIBC raw and unprinted; @c ERR_NO
 *         on success (internal inconsistencies are caught by
 *         assertion).
 */
t_error	run_expansion(t_expansion *expansion, t_expander_args *args);

/**
 * @ingroup expander_priv
 * @brief Runs one full expansion like @ref run_expansion but hands the
 *        resulting fields over as annotated words (quoting metadata
 *        preserved), moving the storage out of the engine.
 *
 * @param word Fields initialized by the function; the caller owns them
 *             and must release them with @ref fields_free (borrowed).
 * @param args Input of the run (borrowed).
 * @return Same raw surface as @ref run_expansion.
 */
t_error	run_expansion_word(t_fields *word, t_expander_args *args);

/**
 * @ingroup expander_priv
 * @brief Boundary mapping of the errors leaving the module — the
 *        identity, final: every failure is printed and requalified in
 *        place at its production site, so only the allowed surface
 *        (@c ERR_NO, @c ERR_POSIX_EXPANSION, @c ERR_POSIX_ASSIGNMENT,
 *        @c ERR_POSIX_SYNTAX, @c ERR_INTERNAL, @c ERR_LIBC) can arrive
 *        here; the full bubble-up audit lives above the implementation
 *        (expander_error.c).
 *
 * @note Every module function returning a @c t_error to an external
 *       caller (@ref expand_str, @ref expand_str_merged,
 *       @ref expand_token, @ref expand_token_merged,
 *       @ref expand_token_word, @ref word_match_pattern and
 *       @ref expansion_merge) routes its result through this function.
 *
 * @param err Raw error to requalify.
 * @return @p err unchanged.
 */
t_error	requalify_expander_error(t_error err);

/**
 * @ingroup expander_priv
 * @brief Tells whether @p flag is set in @p bitset.
 *
 * @param bitset Flag bitset to test.
 * @param flag Flag to look for.
 */
bool	flag_is_active(uint bitset, uint flag);

/**
 * @ingroup expander_priv
 * @brief Moves the first item of @p word to the end of @p word_exp.
 *
 * @param word_exp Destination word (borrowed).
 * @param word Source word (borrowed).
 * @return @c ERR_LIBC if the push fails, @c ERR_NO on success (an
 *         empty @p word is caught by assertion).
 */
t_error	forward_word_item(t_word *word_exp, t_word *word);

/**
 * @ingroup expander_priv
 * @brief Resolves the IFS of a run: the @c IFS variable when set, the
 *        POSIX default @c " \t\n" when unset, an allocated empty string
 *        when set but null.
 *
 * @param ifs String receiving the separators, initialized by the
 *            function and freed on failure (borrowed).
 * @return @c ERR_INTERNAL (printed by the env module) if the shell
 *         parameters are unavailable; @c ERR_LIBC on allocation
 *         failure; @c ERR_NO on success.
 */
t_error	get_ifs(t_string *ifs);

/**
 * @ingroup expander_priv
 * @brief Concatenates the fields of @p in into @p out, separated by the
 *        first character of @p ifs; @p in is emptied as it is consumed.
 *
 * @param out String receiving the joined fields, initialized by the
 *            function and freed on failure (borrowed).
 * @param in Expansion to consume; its fields are popped (borrowed).
 * @param ifs Separators of the run; only the first character is used
 *            (borrowed, read-only).
 * @return @c ERR_LIBC on allocation failure; @c ERR_NO on success.
 */
t_error	join_expansion(t_string *out, t_expansion *in, t_string *ifs);

/**
 * @ingroup expander_priv
 * @brief Re-lexes the raw text @p src through a throwaway string-mode
 *        scanner to recover its quoting and construct spans, replacing
 *        @p src with the scanned value.
 *
 * @param out Context stack of the scanned word, initialized by the
 *            function (borrowed).
 * @param ats_vec_out AST vector of the embedded command substitutions,
 *                    initialized by the function (borrowed).
 * @param src Text to scan; replaced by the scanned value on success,
 *            left untouched on failure (borrowed).
 * @return @c ERR_LIBC on allocation failure; the scanner's raw lexing
 *         errors on malformed input (unterminated construct in string
 *         mode); @c ERR_NO on success.
 */
t_error	prepare_str_for_expansion(
			t_context_stack *out,
			t_ast_vector *ats_vec_out,
			t_string *src);

/* ************************************************************************* */
/*                                LEXER RULES                                */
/* ************************************************************************* */

/**
 * @ingroup expander_priv
 * @brief Handles a backslash in a raw-string scan: line continuation,
 *        and the POSIX 2.2.1 unquoted escape set (any character).
 *
 * @param lexer Lexer state (borrowed).
 * @return @c ERR_LIBC on allocation failure; @c ERR_UNEXPECTED_EOI
 *         (printed) when the input ends on the escape; @c ERR_NO on
 *         success.
 */
t_error	str_escape(t_lexer *lexer);

/**
 * @ingroup expander_priv
 * @brief Consumes one plain raw-string character.
 *
 * @param lexer Lexer state (borrowed).
 * @param _ Unused (borrowed, read-only).
 * @return @c ERR_LIBC on allocation failure; @c ERR_UNEXPECTED_EOI
 *         (printed) at end of input; @c ERR_NO on success.
 */
t_error	str_unescape(t_lexer *lexer, void *_);

#endif
