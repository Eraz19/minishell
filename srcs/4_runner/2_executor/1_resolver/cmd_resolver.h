#ifndef CMD_RESOLVER_H
# define CMD_RESOLVER_H

# include "error.h"
# include "cmd_resolution_type.h"
# include "tokens.h"

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @brief Expand command words and classify the resulting command kind.
 *
 * The resolver expands every word, detects declaration utilities, builtins and
 * shell functions, and fills @p out_resolution accordingly.
 *
 * @note @p out_resolution is initialized by the function.
 * @note On success, the caller owns the resources stored in @p out_resolution
 *       and must later release them with @ref cmd_resolution_free().
 *
 * @param functions Shell function table used for function lookup (borrowed).
 * @param words Command words to resolve (borrowed).
 * @param out_resolution Destination resolution initialized by the function
 *                       (borrowed).
 * @return @c ERR_NO, @c ERR_INDEX_OUT_OF_BOUND, @c ERR_SHELL_NOT_FOUND,
 *         @c ERR_VAR_INVALID_NAME, @c ERR_VAR_NOT_FOUND,
 *         @c ERR_PARAM_BAD_SUBSTITUTION, @c ERR_PARAM_NULL_OR_UNSET,
 *         @c ERR_NOT_IMPLEMENTED, @c ERR_INCOHERENT_STATE,
 *         @c ERR_QUOTED_TILDE or @c ERR_LIBC.
 */
t_error	cmd_resolve(
			t_functions *functions,
			t_tokens *words,
			t_cmd_resolution *out_resolution);

#endif
