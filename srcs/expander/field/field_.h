#ifndef FIELD__H
# define FIELD__H

# include "error.h"
# include "libft.h"
# include "word_.h"

/** @defgroup expander_field Expander fields
 *  @brief Ordered container of the words an expansion stage produces.
 */

/**
 * @ingroup expander_field
 * @typedef t_fields
 * @brief Fields in order, backed by a @ref t_vector of @ref t_word
 *        values; the container owns its words.
 */
typedef t_vector	t_fields;

/* ************************************************************************* */
/*                                LIFE_CYCLE                                 */
/* ************************************************************************* */

/**
 * @ingroup expander_field
 * @brief Initializes @p fields as an empty container.
 *
 * @param fields Container initialized by the function (borrowed).
 */
void	fields_init(t_fields *fields);

/**
 * @ingroup expander_field
 * @brief Frees @p fields and every word it owns.
 *
 * @param fields Already initialized container (borrowed).
 */
void	fields_free(t_fields *fields);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup expander_field
 * @brief Removes the first field of @p fields and hands it to the caller.
 *
 * @param out Set to the removed word; the caller becomes its owner and
 *            must release it with @c word_free (borrowed).
 * @param fields Already initialized container (borrowed).
 * @return @c ERR_EMPTY_STACK if @p fields is empty, @c ERR_LIBC if the
 *         removal fails, @c ERR_NO on success.
 */
t_error	fields_fpop(t_word *out, t_fields *fields);

/**
 * @ingroup expander_field
 * @brief Appends @p item at the end of @p fields (the word struct is
 *        copied by value).
 *
 * @warning Ownership is conditional: on success @p fields owns the
 *          word's storage and the caller must not free its copy (double
 *          free); on failure the caller keeps ownership and must release
 *          it with @c word_free (leak otherwise). Callers pushing a word
 *          that a persistent field still aliases (e.g.
 *          @c expander->word_exp) must re-initialize that field after a
 *          SUCCESSFUL push instead of freeing.
 * @param fields Already initialized container (borrowed).
 * @param item Word to append (ownership of its storage taken by
 *             @p fields on success only).
 * @return @c ERR_LIBC if the push fails, @c ERR_NO on success.
 */
// TODO: fix ownership
t_error	fields_push(t_fields *fields, t_word item);

#endif
