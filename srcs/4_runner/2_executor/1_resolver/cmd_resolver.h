#ifndef CMD_RESOLVER_H
# define CMD_RESOLVER_H

# include "error.h"
# include "cmd_type.h"
# include "tokens.h"

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @brief Expand command words and classify the resulting command kind.
 *
 * The resolver expands every word, detects declaration utilities, builtins and
 * shell functions, and fills @p cmd accordingly.
 *
 * @note @p cmd must already be initialized by the caller.
 * @note On success, the caller owns the resources stored in @p cmd and must
 *       later release them with @ref cmd_free().
 *
 * @param functions Shell function table used for function lookup
 *                  (borrowed, read-only).
 * @param words Command words to resolve (borrowed).
 * @param cmd Destination command object already initialized by the caller
 *            (borrowed).
 * @return @c ERR_NO, @c ERR_INDEX_OUT_OF_BOUND, @c ERR_SHELL_NOT_FOUND,
 *         @c ERR_VAR_INVALID_NAME, @c ERR_VAR_NOT_FOUND,
 *         @c ERR_PARAM_BAD_SUBSTITUTION, @c ERR_PARAM_NULL_OR_UNSET,
 *         @c ERR_NOT_IMPLEMENTED, @c ERR_INCOHERENT_STATE,
 *         @c ERR_QUOTED_TILDE or @c ERR_LIBC.
 */
t_error	cmd_resolve(
			t_cmd *cmd,
			const t_functions *functions,
			const t_tokens *words);

#endif
