/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_matches_.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:45:33 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 17:45:34 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_MATCHES__H
# define PATH_MATCHES__H

# include "error.h"
# include "libft.h"
# include "path_comps_.h"

/** @defgroup expander_path_matches Expander path matches
 *  @brief Candidate paths grown component by component during the
 *         globbing walk; the survivors are the matched paths.
 */

/**
 * @ingroup expander_path_matches
 * @typedef t_path_matches
 * @brief Candidate paths in order, backed by a @ref t_vector of
 *        @ref t_string values; the container owns its strings.
 */
typedef t_vector	t_path_matches;

/* ************************************************************************* */
/*                                LIFE_CYCLE                                 */
/* ************************************************************************* */

/**
 * @ingroup expander_path_matches
 * @brief Initializes @p matches as an empty container.
 *
 * @param matches Container initialized by the function (borrowed).
 */
void	path_matches_init(t_path_matches *matches);

/**
 * @ingroup expander_path_matches
 * @brief Frees @p matches and every string it owns.
 *
 * @param matches Already initialized container (borrowed).
 */
void	path_matches_free(t_path_matches *matches);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup expander_path_matches
 * @brief Reads the directory named by @p match and appends one new
 *        candidate @c match/entry (@c match empty: @c . is read when
 *        @p first, @c / otherwise) to @p out per entry matching the
 *        pattern of @p comp.
 *
 * @note Hidden-entry rule: an entry starting with @c . only matches a
 *       pattern that starts with @c . (possibly escaped); @c . and
 *       @c .. never match. A directory that cannot be opened yields no
 *       candidates and no error.
 * @param out Already initialized container receiving the new candidates
 *            (borrowed).
 * @param match Candidate path naming the directory to read
 *              (borrowed, read-only).
 * @param comp Special component to match entries against
 *             (borrowed, read-only).
 * @param first Whether @p comp is the first component of the word (no
 *              @c / separator is inserted before the entry name).
 * @return @c ERR_LIBC if building or pushing a candidate fails,
 *         @c ERR_NO on success.
 */
t_error	add_lookup_dir_matching(
			t_path_matches *out,
			t_string *match,
			t_path_comp *comp,
			bool first);

/**
 * @ingroup expander_path_matches
 * @brief Applies the literal component @p src: appends @c / (unless
 *        @p first) then its unescaped text to every candidate of
 *        @p out, in place and without touching the filesystem.
 *
 * @param out Already initialized container (borrowed).
 * @param src Literal component to append (borrowed, read-only).
 * @param first Whether @p src is the first component of the word.
 * @return @c ERR_EMPTY_STACK or @c ERR_INDEX_OUT_OF_BOUND on a
 *         candidate read inconsistency, @c ERR_LIBC if an append fails,
 *         @c ERR_NO on success.
 */
t_error	add_path_comp(t_path_matches *out, t_path_comp *src, bool first);

/**
 * @ingroup expander_path_matches
 * @brief Applies the special component @p src: replaces the candidates
 *        of @p out with the matching directory entries of each of them
 *        (see @ref add_lookup_dir_matching); the old candidates are
 *        freed. Candidates whose directory cannot be opened are
 *        dropped silently; @p out may end up empty.
 *
 * @param out Already initialized container (borrowed).
 * @param src Special component to match (borrowed, read-only).
 * @param first Whether @p src is the first component of the word.
 * @return @c ERR_EMPTY_STACK or @c ERR_INDEX_OUT_OF_BOUND on a
 *         candidate read inconsistency, @c ERR_LIBC if building a
 *         candidate fails, @c ERR_NO on success.
 */
t_error	add_path_comp_lookup(t_path_matches *out, t_path_comp *src, bool first);

/**
 * @ingroup expander_path_matches
 * @brief Appends @p pattern to @p cand with its backslash escapes
 *        removed (each @c \\ emits only the character it protects),
 *        turning a @ref match_pattern rendering back into literal path
 *        text.
 *
 * @param cand Already initialized string (borrowed).
 * @param pattern Pattern C-string to unescape; NULL for an empty
 *                component (the pattern of an absolute path's leading
 *                component): nothing is appended (borrowed, read-only).
 * @return @c ERR_LIBC if an append fails, @c ERR_NO on success.
 */
t_error	path_match_append(t_string *cand, const char *pattern);

/**
 * @ingroup expander_path_matches
 * @brief Reads the candidate at @p i without removing it.
 *
 * @warning @p out is set to a pointer into the storage of @p matches:
 *          it is invalidated by any later push, sort or free.
 * @param out Set to the stored string (borrowed).
 * @param matches Already initialized container (borrowed).
 * @param i Position of the candidate to read.
 * @return @c ERR_EMPTY_STACK if @p matches is empty,
 *         @c ERR_INDEX_OUT_OF_BOUND if @p i is past the last candidate,
 *         @c ERR_NO on success.
 */
t_error	path_matches_get(t_string **out, t_path_matches *matches, size_t i);

/**
 * @ingroup expander_path_matches
 * @brief Appends @p match at the end of @p matches (the string struct
 *        is copied by value).
 *
 * @warning Ownership is conditional: on success @p matches owns the
 *          string's storage and the caller must not free its copy
 *          (double free); on failure the caller keeps ownership and
 *          must release it with @ref string_free (leak otherwise).
 * @param matches Already initialized container (borrowed).
 * @param match String to append (ownership of its storage taken by
 *              @p matches on success only).
 * @return @c ERR_LIBC if the push fails, @c ERR_NO on success.
 */
// TODO: fix ownership
t_error	path_matches_push(t_path_matches *matches, t_string *match);

/**
 * @ingroup expander_path_matches
 * @brief Sorts the candidates of @p matches in place, in ascending
 *        bytewise order (insertion sort over @ref str_cmp).
 *
 * @param matches Already initialized container (borrowed).
 */
void	path_matches_sort(t_path_matches *matches);

#endif
