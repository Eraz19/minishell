#ifndef TOKENS_H
# define TOKENS_H

# include "libft.h"
# include "error.h"
# include "token.h"

// vector of t_token* (borrowed)
typedef t_vector	t_tokens;

t_error	tokens_get(t_tokens *tokens, size_t i, t_token **out_token_ptr);

#endif
