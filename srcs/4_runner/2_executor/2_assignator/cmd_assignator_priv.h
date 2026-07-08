#ifndef CMD_ASSIGNATOR_PRIV_H
# define CMD_ASSIGNATOR_PRIV_H

# include "error.h"
# include "token.h"
# include "expander.h"
# include "cmd_type.h"

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @brief Reject an assignment targeting a read-only shell variable.
 *
 * @param token Assignment token to validate (borrowed, read-only).
 * @return @c ERR_NO, @c ERR_VAR_READ_ONLY or @c ERR_SHELL_NOT_FOUND.
 */
t_error	cmd_assignment_check(const t_token *token);

/**
 * @brief Expand one assignment token into a single owned string.
 *
 * @note @p out_expanded is initialized by the function on success.
 *
 * @param token Assignment token to expand (borrowed, read-only).
 * @param flags Expansion flags to apply.
 * @param out_expanded Destination string initialized by the function
 *                     (borrowed).
 * @return @c ERR_NO, @c ERR_INDEX_OUT_OF_BOUND, @c ERR_VAR_INVALID_NAME,
 *         @c ERR_VAR_NOT_FOUND, @c ERR_PARAM_BAD_SUBSTITUTION,
 *         @c ERR_PARAM_NULL_OR_UNSET, @c ERR_NOT_IMPLEMENTED,
 *         @c ERR_INCOHERENT_STATE, @c ERR_QUOTED_TILDE or @c ERR_LIBC.
 */
t_error	cmd_assignment_expand(
			const t_token *token,
			t_exp_flag flags,
			t_string *out_expanded);

/**
 * @brief Apply one expanded assignment according to the command kind.
 *
 * For @c CMD_NONE, special builtins and functions, the assignment updates the
 * shell variable store. Otherwise, it is merged into @p cmd->envp and may mark
 * @p cmd->path_is_temporary when it overrides @c PATH.
 *
 * @note @p expanded is consumed by the function whether it succeeds or fails.
 * @note @p cmd->envp must already be initialized by the caller.
 *
 * @param cmd Command receiving the assignment (borrowed).
 * @param token Original assignment token (borrowed, read-only).
 * @param expanded Expanded assignment string consumed by the function
 *                 (ownership taken by @c cmd_assignment_process).
 * @return @c ERR_NO, @c ERR_SHELL_NOT_FOUND, @c ERR_VAR_INVALID_NAME,
 *         @c ERR_VAR_READ_ONLY or @c ERR_LIBC.
 */
t_error	cmd_assignment_process(
			t_cmd *cmd,
			const t_token *token,
			t_string *expanded);

#endif
