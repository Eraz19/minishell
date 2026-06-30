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

t_error	expander_expand_word(t_token *word, t_vector *out);

t_error	expander_expand_filename(t_token *filename, t_vector *out);

t_error	expander_expand_heredoc_delim(t_string *heredoc_delim, t_string *out);

t_error	expander_expand_heredoc_body(t_string *heredoc_file_path);

t_error	expander_expand_assignment(t_token *assignment, t_string *out);

#endif
