#ifndef PATH_COMPS__H
# define PATH_COMPS__H

# include "libft.h"
# include "error.h"
# include "word_.h"

/** @defgroup expander_path_comps Expander path components
 *  @brief The quote-removed word split on @c / into per-directory
 *         patterns, rendered in the @ref match_pattern dialect.
 */

/**
 * @ingroup expander_path_comps
 * @typedef t_path_comps
 * @brief Path components in order, backed by a @ref t_vector of
 *        @ref s_path_comp values; the container owns its components.
 */
typedef t_vector	t_path_comps;

/**
 * @ingroup expander_path_comps
 * @struct s_path_comp
 * @brief One path component (the text between two @c / separators;
 *        empty for leading, doubled or trailing separators).
 *
 * @var s_path_comp::special Whether the pattern holds an unescaped
 *                           @c *, @c ? or valid bracket expression and
 *                           must be matched against directory entries
 *                           (a literal component is appended without a
 *                           directory lookup).
 * @var s_path_comp::pattern Component text as a string in the
 *                           @ref match_pattern dialect: quoted or
 *                           escaped metacharacters are kept
 *                           backslash-escaped so they stay literal
 *                           (owned by the component).
 */
typedef struct s_path_comp
{
	bool		special;
	t_string	pattern;
}	t_path_comp;

/* ************************************************************************* */
/*                                LIFE_CYCLE                                 */
/* ************************************************************************* */

/**
 * @ingroup expander_path_comps
 * @brief Initializes @p comp as a non-special component with an empty
 *        pattern.
 *
 * @param comp Component initialized by the function (borrowed).
 */
void	path_comp_init(t_path_comp *comp);

/**
 * @ingroup expander_path_comps
 * @brief Frees the pattern of @p comp and zeroes it.
 *
 * @param comp Already initialized component (borrowed).
 */
void	path_comp_free(t_path_comp *comp);

/**
 * @ingroup expander_path_comps
 * @brief Initializes @p comps as an empty container.
 *
 * @param comps Container initialized by the function (borrowed).
 */
void	path_comps_init(t_path_comps *comps);

/**
 * @ingroup expander_path_comps
 * @brief Splits the quote-removed word @p src on @c / into components:
 *        every @c / emits the pending component and the trailing text
 *        emits one final component, so a word with N separators yields
 *        N+1 components (an empty word yields one empty component).
 *        Characters are rendered through @ref path_comp_push.
 *
 * @warning On failure @p comps is freed (its components included).
 * @param comps Components container (@ref t_path_comps), initialized by
 *              the function (borrowed).
 * @param src Word to split (borrowed, read-only).
 * @return @c ERR_EMPTY_STACK or @c ERR_INDEX_OUT_OF_BOUND on a word
 *         read inconsistency, @c ERR_LIBC on allocation failure,
 *         @c ERR_NO on success.
 */
t_error	path_comps_load(t_path_comps *comps, const t_word *src);

/**
 * @ingroup expander_path_comps
 * @brief Frees @p comps and every component it owns.
 *
 * @param comps Already initialized container (borrowed).
 */
void	path_comps_free(t_path_comps *comps);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup expander_path_comps
 * @brief Finalizes @p comp (computes its @c special flag from its
 *        pattern), appends it to @p comps and re-initializes @p comp
 *        empty for the next component.
 *
 * @note On success the pattern storage moves into @p comps and @p comp
 *       is re-initialized, on failure @p comp keeps its pattern: a
 *       @ref path_comp_free of @p comp stays safe in both outcomes.
 * @param comps Already initialized container (borrowed).
 * @param comp Component to emit (borrowed).
 * @return @c ERR_LIBC if the push fails, @c ERR_NO on success.
 */
t_error	path_comp_emit(t_path_comps *comps, t_path_comp *comp);

/**
 * @ingroup expander_path_comps
 * @brief Tells whether @p pattern needs directory matching: it holds an
 *        unescaped @c * or @c ?, or a valid bracket expression (see
 *        @ref valid_bracket_exp_len); backslash-escaped characters are
 *        skipped.
 *
 * @param pattern Pattern C-string; @c NULL yields false
 *                (borrowed, read-only).
 * @return True when @p pattern contains at least one active
 *         metacharacter.
 */
bool	path_comp_is_special(const char *pattern);

/**
 * @ingroup expander_path_comps
 * @brief Appends the character of @p item to the pattern of @p comp,
 *        prefixing a backslash when the character was quoted or escaped
 *        and is a @ref match_pattern metacharacter (one of @c *, @c ?,
 *        @c [, @c ], @c !, @c ^, @c - or @c \\) so it stays literal.
 *
 * @param comp Already initialized component (borrowed).
 * @param item Word character to render (copied by value).
 * @return @c ERR_LIBC if an append fails, @c ERR_NO on success.
 */
t_error	path_comp_push(t_path_comp *comp, t_word_item item);

/**
 * @ingroup expander_path_comps
 * @brief Reads the component at @p i without removing it.
 *
 * @warning @p out is a shallow copy: its pattern aliases the stored
 *          string; do not free it.
 * @param out Set to a copy of the component (borrowed).
 * @param src Already initialized container (borrowed, read-only).
 * @param i Position of the component to read.
 * @return @c ERR_EMPTY_STACK if @p src is empty,
 *         @c ERR_INDEX_OUT_OF_BOUND if @p i is past the last component,
 *         @c ERR_NO on success.
 */
t_error	path_comps_get(t_path_comp *out, const t_path_comps *src, size_t i);

/**
 * @ingroup expander_path_comps
 * @brief Tells whether at least one component of @p comps is special
 *        (globbing is skipped for the word otherwise).
 *
 * @param comps Already initialized container (borrowed, read-only).
 * @return True when a special component exists.
 */
bool	path_comps_have_special(const t_path_comps *comps);

/**
 * @ingroup expander_path_comps
 * @brief Appends @p comp at the end of @p comps (the component struct
 *        is copied by value).
 *
 * @warning Ownership is conditional: on success @p comps owns the
 *          component's pattern storage and the caller must not free its
 *          copy (double free); on failure the caller keeps ownership
 *          and must release it with @ref path_comp_free (leak
 *          otherwise). Prefer @ref path_comp_emit, which re-initializes
 *          the source component on success.
 * @param comps Already initialized container (borrowed).
 * @param comp Component to append (ownership of its pattern storage
 *             taken by @p comps on success only).
 * @return @c ERR_LIBC if the push fails, @c ERR_NO on success.
 */
// TODO: fix ownership
t_error	path_comps_push(t_path_comps *comps, t_path_comp comp);

#endif
