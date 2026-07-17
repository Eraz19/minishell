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
 *                                   the last command substitution;
 *                                   unused until command substitution is
 *                                   implemented (borrowed).
 * @var s_expander_args::assignment_offset Index of the @c '=' of an
 *                                         assignment word, @c -1
 *                                         otherwise.
 */
typedef	struct s_expander_args
{
	t_string				ifs;
	t_string				value;
	t_exp_flag				flags;
	const t_context_stack	*contexts;
	int						*exit_status;
	ssize_t					assignment_offset;
}	t_expander_args;

typedef struct s_expander
{
	t_string	ifs;
	t_error		err;
	t_word		word;
	t_exp_flag	flags;
	t_fields	fields;
	t_word		word_exp;
	t_fields	fields_exp;
	bool		in_operand;
	int			*exit_status;
	ssize_t		assignment_offset;
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
 * @return @c ERR_SHELL_NOT_FOUND if the shell parameters are unavailable;
 *         @c ERR_LIBC on allocation failure; @c ERR_INCOHERENT_STATE,
 *         @c ERR_EMPTY_STACK or @c ERR_INDEX_OUT_OF_BOUND on a context
 *         stack inconsistency; @c ERR_NO on success.
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

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup expander_priv
 * @brief Runs the expansion pipeline on the loaded fields:
 *        substitutions, then field splitting, pathname expansion and
 *        quote removal when their flag is set.
 *
 * @param expander Loaded expander state (borrowed).
 * @return The first stage error, raw (see @ref expander_error_qualify
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
 * @return @c ERR_LIBC on allocation failure; @c ERR_INDEX_OUT_OF_BOUND
 *         on an internal inconsistency; @c ERR_NO on success.
 */
t_error	pattern_from_word(t_string *out, const t_word *pattern);

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
 * @return Raw errors, requalified by the API endpoints: @c ERR_LIBC;
 *         @c ERR_SHELL_NOT_FOUND; @c ERR_EMPTY_STACK,
 *         @c ERR_INDEX_OUT_OF_BOUND or @c ERR_INCOHERENT_STATE on an
 *         internal inconsistency; @c ERR_NOT_IMPLEMENTED (printed) from
 *         the command, backquote and arithmetic evaluation stubs;
 *         @c ERR_PARAM_BAD_SUBSTITUTION (printed),
 *         @c ERR_PARAM_NULL_OR_UNSET (printed),
 *         @c ERR_VAR_INVALID_NAME (printed) or @c ERR_VAR_READ_ONLY
 *         (printed) on a user-facing expansion failure; @c ERR_NO on
 *         success.
 */
t_error	run_expansion(t_expansion *expansion, t_expander_args *args);

/**
 * @ingroup expander_priv
 * @brief Runs one full expansion like @ref run_expansion, but returns
 *        the single resulting field as an annotated word instead of
 *        degrading it to a string: the quoting metadata survives for
 *        pattern matching.
 *
 * @warning Meant for flag sets without @c EXP_FIELD_SPLIT: only the
 *          first resulting field is returned.
 * @param word Word receiving the field; initialized by the function, the
 *             caller owns it and must release it with @c word_free
 *             (borrowed).
 * @param args Input of the run; its IFS stays owned by the caller
 *             (borrowed).
 * @return Same contract as @ref run_expansion, plus @c ERR_EMPTY_STACK
 *         if the run produces no field.
 */
t_error	run_expansion_word(t_word *word, t_expander_args *args);

/**
 * @ingroup expander_priv
 * @brief Requalifies an error escaping the expander API (@c expand_token,
 *        @c expand_token_merged, @c expand_str): no caller needs the
 *        specific expansion error types.
 *
 * Prints the specific diagnostic at the moment precision is lost, then
 * requalifies (POSIX 2.8.1): user-facing expansion failures
 * (@c ERR_PARAM_BAD_SUBSTITUTION, @c ERR_BAD_SUBSTITUTION,
 * @c ERR_PARAM_NULL_OR_UNSET, @c ERR_VAR_INVALID_NAME, and an unexpected
 * end of input inside a construct discovered at expansion time) become
 * @c ERR_POSIX_EXPANSION; a readonly-variable assignment
 * (@c ERR_VAR_READ_ONLY, e.g. @c ${RO:=v}) becomes
 * @c ERR_POSIX_ASSIGNMENT; any other unqualified error becomes
 * @c ERR_INTERNAL. @c ERR_LIBC is printed with the expander context and
 * kept, fully qualified errors (>= @c ERR_INTERRUPTED) pass through
 * untouched.
 *
 * @note @c ERR_QUOTED_TILDE never reaches the qualifier: it is internal
 *       control flow, consumed by the tilde submodule (a quoted tilde
 *       stays literal).
 *
 * @param err Error to requalify.
 * @return The requalified (and printed) error.
 */
t_error	expander_error_qualify(t_error err);

/**
 * @ingroup expander_priv
 * @brief Tells whether @p flag is set in @p bitset.
 *
 * @param bitset Flag bitset to test.
 * @param flag Flag to look for.
 */
bool    flag_is_active(uint bitset, uint flag);

/**
 * @ingroup expander_priv
 * @brief Moves the first item of @p word to the end of @p word_exp.
 *
 * @param word_exp Destination word (borrowed).
 * @param word Source word (borrowed).
 * @return @c ERR_EMPTY_STACK if @p word is empty, @c ERR_LIBC if the
 *         push fails, @c ERR_NO on success.
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
 * @return @c ERR_SHELL_NOT_FOUND if the shell parameters are
 *         unavailable; @c ERR_LIBC on allocation failure; @c ERR_NO on
 *         success.
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
 * @return @c ERR_LIBC on allocation failure; @c ERR_EMPTY_STACK or
 *         @c ERR_INDEX_OUT_OF_BOUND on an internal inconsistency;
 *         @c ERR_NO on success.
 */
t_error	join_expansion(t_string *out, t_expansion *in, t_string *ifs);

/**
 * @ingroup expander_priv
 * @brief Lexes a raw string for expansion: removes escaped newlines from
 *        @p src, then records its quoting and expansion constructs into
 *        @p out using @ref str_context_rules.
 *
 * @param out Destination stack, already initialized by the caller; the
 *            recorded contexts are appended (borrowed).
 * @param src Text to prepare, rewritten without its escaped newlines
 *            (borrowed).
 * @return @c ERR_LIBC on allocation failure; @c ERR_UNEXPECTED_EOI
 *         (printed) on an unterminated construct; @c ERR_NOT_IMPLEMENTED
 *         (printed) from the command substitution stub;
 *         @c ERR_EMPTY_STACK, @c ERR_NO_INPUT_TO_LEX,
 *         @c ERR_INDEX_OUT_OF_BOUND or @c ERR_INCOHERENT_STATE on an
 *         internal inconsistency; @c ERR_NO on success.
 */
t_error	prepare_str_for_expansion(t_context_stack *out, t_string *src);

/* ************************************************************************* */
/*                                LEXER RULES                                */
/* ************************************************************************* */

/**
 * @ingroup expander_priv
 * @brief Builds the lexer configuration of a raw-string scan (a string
 *        that never went through tokenization, e.g. a prompt): quoting
 *        and expansions detected, top-level escape rules, end at NUL.
 *
 * The string is scanned as an unquoted word: quotes open quoting
 * contexts (POSIX 2.2.2, 2.2.3) and a backslash escapes any following
 * character (POSIX 2.2.1), unlike the here-document rules
 * (@c body_context_rules) where quotes stay literal and the escape set
 * is limited to @c $, @c ` and @c \ (POSIX 2.7.4).
 *
 * @note DOCUMENTED CHOICE for @c PS1 -like values: POSIX 2.5.3 only
 *       mandates parameter expansion on @c PS1 and leaves quoting
 *       unspecified. Under these rules a single-quoted span in the
 *       value suppresses expansion, quote removal applies when
 *       @c EXP_QUOTE_REMOVAL is set, and an unmatched quote reports
 *       @c ERR_UNEXPECTED_EOI (printed); bash instead treats quotes in
 *       the prompt as plain characters and expands through them. To
 *       switch to the bash behaviour, set @c quoting and @c is_quoting
 *       to @c NULL below: quotes then stay literal and only the
 *       expansion constructs are detected. To also mimic the
 *       here-document escape set, swap @ref str_escape for a wrapper
 *       whose whitelist is @c is_in_context_heredoc_whitelist instead
 *       of @ref is_in_context_none_whitelist.
 *
 * @return The scan configuration; the context tag, delimiter lengths and
 *         stack item are left for the lexer entry point to fill in.
 */
t_lexer_context_args	str_context_rules(void);

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
