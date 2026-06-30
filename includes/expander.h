#ifndef EXPANDER_H
# define EXPANDER_H

# include "error.h"
# include "libft.h"
# include "context.h"

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

typedef enum e_expander_flags
{
	EXP_TILDE			= (1u << 0),
	EXP_PARAM			= (1u << 1),
	EXP_CMD_SUB			= (1u << 2),
	EXP_ARITH			= (1u << 3),
	EXP_FIELD_SPLIT		= (1u << 4),
	EXP_PATH_NAME		= (1u << 5),
	EXP_QUOTE_REMOVAL	= (1u << 6),
}	t_expander_flags;

typedef	struct s_expander_args
{
	t_string				value;
	t_expander_flags		flags;
	const t_context_stack	*contexts;
	ssize_t					assignment_offset;
}	t_expander_args;


/**
 * @ingroup expander
 * @brief Frees every field's buffer and the backing array.
 *
 * @param expansion Pointer to the expansion to free (borrowed).
 */
void	expansion_free(t_expansion *expansion);

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


t_error	expander_expand(t_expansion *expansion, t_expander_args *args);

#endif
