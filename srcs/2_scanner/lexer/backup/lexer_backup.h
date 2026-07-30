#ifndef LEXER_BACKUP_H
# define LEXER_BACKUP_H

# include "token.h"
# include "lexer.h"

/* ************************************************************************* */
/*                                  TYPES                                    */
/* ************************************************************************* */

/**
 * @ingroup lexer
 * @struct s_lexer_backup
 * @brief Snapshot of the lexer used to roll back a speculative scan.
 *
 * @var s_lexer_backup::i Saved read cursor.
 * @var s_lexer_backup::token_type Saved type of the token in progress.
 * @var s_lexer_backup::token_value_len Saved length of the token value.
 * @var s_lexer_backup::token_contexts_len Saved depth of the token context
 *                                         stack.
 */
typedef struct s_lexer_backup
{
	size_t			i;
	t_token_type	token_type;
	size_t			token_value_len;
	size_t			token_contexts_len;
}	t_lexer_backup;

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup lexer
 * @brief Snapshots the lexer for a possible later @ref lexer_restore.
 *
 * @param lexer Already initialized lexer (borrowed, read-only).
 * @return The snapshot value.
 */
t_lexer_backup	lexer_backup(t_lexer *lexer);

/**
 * @ingroup lexer
 * @brief Restores the lexer to a previously captured @p backup: pops the
 *        contexts pushed since the snapshot, truncates the token value and
 *        rewinds the read cursor and token type.
 *
 * @param lexer Already initialized lexer (borrowed).
 * @param backup Snapshot captured by @ref lexer_backup.
 * @return The current @c lexer->err, unchanged: the unwind itself cannot
 *         fail with the current context-stack API.
 */
t_error			lexer_restore(t_lexer *lexer, t_lexer_backup backup);

#endif
