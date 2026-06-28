#ifndef SHELL_PRIV_H
# define SHELL_PRIV_H

# include "shell.h"

/* ************************************************************************* */
/*                                LIFE_CYCLE                                 */
/* ************************************************************************* */

/**
 * @brief Initializes a shell state in place.
 *
 * @param shell Destination shell object initialized by the function (borrowed).
 */
void	shell_init(t_shell *shell);

/**
 * @brief Loads the shell runtime state from @p argc / @p argv / @p envp .
 *
 * @warning @p shell must already have been initialized with @ref shell_init().
 *
 * @param shell Shell state to populate in place (borrowed).
 * @param argc Argument count.
 * @param argv Argument vector (borrowed, read-only).
 * @param envp Environment vector (borrowed, read-only).
 * @return ERR_NO on success, ERR_LIBC on allocation or POSIX failure,
 *         ERR_SHELL_NOT_FOUND if options are unavailable, ERR_OPT_INVALID /
 *         ERR_OPT_MISSING_ARG / ERR_OPT_INVALID_ARG from option parsing,
 *         ERR_VAR_INVALID_NAME / ERR_VAR_READ_ONLY from variable loading,
 *         or ERR_LR_CONFLICT / ERR_LR_STATE_NOT_FOUND from builder setup.
 */
t_error	shell_load(t_shell *shell, int argc, char **argv, char **envp);

/**
 * @brief Releases the global shell state and clears the singleton.
 *
 * Does nothing when no shell is currently registered.
 */
void	shell_free(t_shell *shell);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @brief Handles the ENV startup hook for interactive stdin sessions.
 *
 * @note Non-interactive shells and shells without OPT_STDIN_INPUT active are
 *       skipped.
 * @return ERR_NO on success or no-op, ERR_SHELL_NOT_FOUND if options are
 *         unavailable, or ERR_LIBC on allocation or POSIX failure.
 */
t_error	shell_exec_env(void);

/**
 * @brief Registers the global shell singleton.
 *
 * @param addr Shell instance to register (borrowed, read-only), or NULL to
 *             clear the singleton.
 */
void	shell_set(t_shell *addr);

#endif
