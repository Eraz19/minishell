#ifndef EXPANDER_H
# define EXPANDER_H

# include "error.h"
# include "token.h"

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
