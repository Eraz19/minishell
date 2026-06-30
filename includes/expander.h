#ifndef EXPANDER_H
# define EXPANDER_H

# include "error.h"
# include "token.h"

/* ---------------------- TMP ---------------------- */

#define EXP_TILDE		(1 << 0)
#define EXP_PARAM		(1 << 1)
#define EXP_CMD_SUB		(1 << 2)
#define EXP_ARITHM_SUB	(1 << 3)
#define EXP_FIELDS		(1 << 4)
#define EXP_PATHNAME	(1 << 5)
#define EXP_QUOTE		(1 << 6)

typedef t_vector	t_expansion;

t_error	heredoc_expand(t_string *path);
t_error	expander_expand(t_token *token, int flags, t_expansion *out);

/**
 * @ingroup expander
 * @brief Reads the field at @p index without removing it.
 *
 * @p str receives a shallow copy whose buffer is still owned by the
 * expansion; do not free it.
 *
 * @param expansion Pointer to the expansion (borrowed).
 * @param index Position to read.
 * @param str Out-parameter receiving the borrowed field.
 * @return ERR_NO on success, ERR_INDEX_OUT_OF_BOUND if @p index is past the
 *         last field.
 */
t_error	expansion_get(
			const t_expansion *expansion,
			size_t index,
			t_string *str);

t_error expansion_take(t_expansion *exp, size_t i, t_string *out);

/* ------------------------------------------------- */

/**
 * @ingroup expander
 * @brief Result of a word expansion: a vector of t_string fields.
 *
 * Each element is an owned t_string (one expanded field); the vector owns its
 * elements and releases them with string_free on expansion_free().
 */
typedef t_vector	t_expansion;

/**
 * @ingroup expander
 * @brief Frees every field's buffer and the backing array.
 *
 * @param expansion Pointer to the expansion to free (borrowed).
 */
void	expansion_free(t_expansion *expansion);

t_error	expander_expand_word(const t_token *word, t_expansion *out);

t_error	expander_expand_filename(const t_token *filename, t_expansion *out);

t_error	expander_expand_heredoc_delim(
			const t_string *heredoc_delim,
			t_string *out);

t_error	expander_expand_heredoc_body(const t_string *heredoc_file_path);

t_error	expander_expand_assignment(const t_token *assignment, t_string *out);

#endif
