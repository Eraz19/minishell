#ifndef SIG_H
# define SIG_H

# include "sig_priv.h"
# include "params.h"
# include "error.h"
# include <stdbool.h>

/* ************************************************************************* */
/*                                LIFE CYCLE                                 */
/* ************************************************************************* */

/**
 * @brief Initialize the global signal module state.
 */
void	sig_init(void);

/**
 * @brief Load signal state from the process entry state and shell parameters.
 *
 * @param sig_state Signal state to populate (borrowed).
 * @param params Shell parameters used to detect interactive mode (borrowed,
 *               read-only).
 * @return @c ERR_NO, @c ERR_INTERNAL or @c ERR_LIBC.
 */
t_error	sig_load(t_sig_state *sig_state, t_params *params);

/**
 * @brief Release all resources owned by the global signal module state.
 */
void	sig_free(void);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @brief Clear transient signal module state without uninstalling handlers.
 *
 * @note This is currently a no-op because signal state owns no transient
 *       allocation and pending signal tracking must remain intact.
 */
void	sig_clear(void);

/**
 * @brief Report whether a trapped signal is pending.
 *
 * @param out_signo Destination receiving the first pending trapped signal
 *                  number when the function returns @c true (borrowed).
 * @return @c true when a trapped signal is pending, otherwise @c false.
 */
bool	sig_has_pending_trap(int *out_signo);

/**
 * @brief Reset trapped signal handlers to defaults for a subshell.
 *
 * @return @c ERR_NO, @c ERR_INTERNAL or @c ERR_LIBC.
 */
t_error	sig_init_subshell(void);

/**
 * @brief Print all signal actions in @c trap @c -p format.
 *
 * @return @c ERR_NO, @c ERR_LIBC or @c ERR_POSIX_WRITE.
 */
t_error	sig_print_all(void);

/**
 * @brief Print every non-default signal action in @c trap format.
 *
 * @return @c ERR_NO, @c ERR_LIBC or @c ERR_POSIX_WRITE.
 */
t_error	sig_print_all_except_default(void);

// TODO: doc
// @ret ERR_NO / ERR_POSIX_WRITE / ERR_LIBC
t_error	sig_print_conditions(
			const char *builtin_name,
			char **conditions,
			int *exit_status);

/**
 * @brief Run pending trapped signal commands, preserving the saved status.
 *
 * @return @c ERR_NO, @c ERR_INTERNAL or @c ERR_LIBC.
 */
t_error	sig_process(void);

/**
 * @brief Run the @c EXIT / @c 0 trap command, when one is installed.
 *
 * @return @c ERR_NO, @c ERR_INTERNAL or @c ERR_LIBC.
 */
t_error	sig_process_exit(void);

/**
 * @brief Set a trap condition back to its default action.
 *
 * @param sig_name Trap condition without the @c SIG prefix, or supported
 *                 numeric signal C-string (borrowed, read-only).
 * @return @c ERR_NO, @c ERR_VAR_INVALID_NAME,
 *         @c ERR_SIG_WAS_IGNORED_ON_ENTRY, @c ERR_INTERNAL or @c ERR_LIBC.
 */
t_error	sig_set_default(const char *sig_name);

/**
 * @brief Set a trap condition to be ignored.
 *
 * @param sig_name Trap condition without the @c SIG prefix, or supported
 *                 numeric signal C-string (borrowed, read-only).
 * @return @c ERR_NO, @c ERR_VAR_INVALID_NAME or @c ERR_LIBC.
 */
t_error	sig_set_ignore(const char *sig_name);

/**
 * @brief Install @p cmd as the trap command for a condition.
 *
 * @param sig_name Trap condition without the @c SIG prefix, @c EXIT, @c 0, or
 *                 supported numeric signal C-string (borrowed, read-only).
 * @param cmd Trap command C-string copied by the function (borrowed,
 *            read-only).
 * @return @c ERR_NO, @c ERR_VAR_INVALID_NAME,
 *         @c ERR_SIG_WAS_IGNORED_ON_ENTRY or @c ERR_LIBC.
 */
t_error	sig_set_trap(const char *sig_name, const char *cmd);

#endif
