#ifndef CMD_RESOLVER_H
# define CMD_RESOLVER_H

# include "error.h"
# include "cmd_type.h"
# include "token.h"

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @brief Expand command words and classify the resulting command kind.
 *
 * The resolver expands every word from @p words, appends the resulting fields
 * to @p cmd->argv, chooses declaration-utility expansion rules when needed, and
 * classifies the first resulting field as a special builtin, shell function,
 * intrinsic builtin or external command.
 *
 * @note @p cmd must already be initialized by the caller.
 * @note On success, @p cmd->argv is NULL-terminated and the caller owns the
 *       resources stored in @p cmd until @ref cmd_free().
 *
 * @param cmd Destination command object already initialized by the caller
 *            (borrowed).
 * @param functions Shell function table used for function lookup
 *                  (borrowed, read-only).
 * @param words Command words to resolve (borrowed).
 * @return @c ERR_NO, @c ERR_INDEX_OUT_OF_BOUND, @c ERR_SHELL_NOT_FOUND,
 *         @c ERR_VAR_INVALID_NAME, @c ERR_VAR_NOT_FOUND,
 *         @c ERR_PARAM_BAD_SUBSTITUTION, @c ERR_PARAM_NULL_OR_UNSET,
 *         @c ERR_NOT_IMPLEMENTED, @c ERR_INCOHERENT_STATE,
 *         @c ERR_QUOTED_TILDE, @c ERR_EMPTY_STACK or @c ERR_LIBC.
 */
t_error	cmd_resolve(t_cmd *cmd, const t_token_pool *words);

#endif
