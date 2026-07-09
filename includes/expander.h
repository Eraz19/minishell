#ifndef EXPANDER_H
# define EXPANDER_H

# include "error.h"
# include "libft.h"
# include "token.h"

typedef enum e_exp_flags
{
	EXP_TILDE_NORMAL		= (1u << 0),
	EXP_TILDE_ASSIGNMENT	= (1u << 1),
	EXP_DOLLAR_SQUOTE		= (1u << 2),
	EXP_PARAM				= (1u << 3),
	EXP_CMD_SUB				= (1u << 4),
	EXP_ARITH				= (1u << 5),
	EXP_FIELD_SPLIT			= (1u << 6),
	EXP_PATH_NAME			= (1u << 7),
	EXP_QUOTE_REMOVAL		= (1u << 8),
}	t_exp_flag;

/**
 * @ingroup expander
 * @brief Result of a word expansion: a vector of t_string fields.
 *
 * Each element is an owned t_string (one expanded field); the vector owns its
 * elements and releases them with string_free on expansion_free().
 */
typedef t_vector	t_expansion;

t_error expansion_take(t_expansion *exp, size_t i, t_string *out);

/**
 * @ingroup expander
 * @brief Frees every field's buffer and the backing array.
 *
 * @param expansion Pointer to the expansion to free (borrowed).
 */
void	expansion_free(t_expansion *expansion);

void	expansion_free_void(void *expansion);

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
t_error	expansion_get(t_string *out, const t_expansion *expansion, size_t i);

t_error expand_str(t_expansion *out, const t_string *src, t_exp_flag flags);
t_error	expand_token(t_expansion *out, const t_token *src, t_exp_flag flags);
t_error	expand_heredoc(t_expansion *out, const t_string *src, t_exp_flag flags);


#endif
