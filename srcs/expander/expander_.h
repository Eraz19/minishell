#ifndef EXPANDER__H
# define EXPANDER__H

# include "field_.h"
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
 * @var s_expander_args::value Raw text to expand, a @ref t_string whose
 *                             ownership stays with the caller.
 * @var s_expander_args::flags Expansions to apply.
 * @var s_expander_args::contexts Quoting/expansion spans of the value
 *                                (borrowed, read-only).
 * @var s_expander_args::assignment_offset Offset of the @c '=' when the
 *                                         value is an assignment word,
 *                                         @c -1 otherwise (drives tilde
 *                                         expansion after @c = and
 *                                         @c :).
 */
typedef	struct s_expander_args
{
	t_string				value;
	t_exp_flag				flags;
	const t_context_stack	*contexts;
	ssize_t					assignment_offset;
}	t_expander_args;

/**
 * @ingroup expander_priv
 * @struct s_expander
 * @brief State of one expansion run.
 *
 * @var s_expander::ifs Field separators (@c $IFS or the default
 *                      space/tab/newline), a @ref t_string owned by the
 *                      expander.
 * @var s_expander::err Last error recorded by the run.
 * @var s_expander::flags Expansions to apply.
 * @var s_expander::word Word currently being rewritten, managed by the
 *                       word submodule.
 * @var s_expander::fields Fields being consumed by the current stage,
 *                         managed by the field submodule.
 * @var s_expander::word_exp Rewritten word under construction, managed by
 *                           the word submodule.
 * @var s_expander::fields_exp Fields produced by the current stage,
 *                             managed by the field submodule.
 * @var s_expander::in_operand Whether a braced-parameter operand is being
 *                             expanded.
 * @var s_expander::assignment_offset Offset of the @c '=' of an
 *                                    assignment word, @c -1 otherwise.
 */
typedef struct s_expander
{
	t_string	ifs;
	t_error		err;
	t_exp_flag	flags;
	t_word		word;
	t_fields	fields;
	t_word		word_exp;
	t_fields	fields_exp;
	bool		in_operand;
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
 * @brief Resolves the IFS, then loads the annotated word from @p args
 *        through the loader and stores it as the single initial field.
 *
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
 * @brief Frees the IFS, both words and both field containers of
 *        @p expander, then zeroes it.
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
 * @brief Requalifies an error escaping the expander API (@c expand_token,
 *        @c expand_str, @c expand_heredoc): no caller needs the specific
 *        expansion error types.
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
 * @brief Resolves the field separators: @c $IFS when set, the default
 *        space/tab/newline when unset, empty when set to empty.
 *
 * @param expander Expander state (borrowed).
 * @param ifs String receiving the separators, initialized by the
 *            function and freed on failure (borrowed).
 * @return @c ERR_SHELL_NOT_FOUND if the shell parameters are unavailable,
 *         @c ERR_LIBC on allocation failure, @c ERR_NO on success.
 */
t_error	get_ifs(t_expander *expander, t_string	*ifs);

#endif
