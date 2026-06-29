#ifndef EXPANDER_H
# define EXPANDER_H

# include "error.h"
# include "token.h"

t_error	expander_expand_word(t_token *word, t_vector *out);

t_error	expander_expand_filename(t_token *filename, t_vector *out);

t_error	expander_expand_heredoc_delim(t_buff *heredoc_delim, t_buff *out);

t_error	expander_expand_heredoc_body(t_buff *heredoc_file_path);

t_error	expander_expand_assignment(t_token *assignment, t_buff *out);

#endif
