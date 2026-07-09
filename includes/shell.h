#ifndef SHELL_H
# define SHELL_H

# include <stdint.h>
# include "alias.h"
# include "params.h"
# include "runner.h"
# include "history.h"
# include "scanner.h"
# include "heredoc.h"
# include "builder.h"

/**
 * @struct s_shell
 * @brief Aggregate state shared by the shell submodules.
 *
 * @var s_shell::alias Alias state managed by the alias submodule.
 * @var s_shell::builder Parser and AST builder state managed by the builder
 *                       submodule.
 * @var s_shell::heredoc Here-document state managed by the heredoc submodule.
 * @var s_shell::history Command history state managed by the history submodule.
 * @var s_shell::params Global parameter state managed by the params submodule.
 * @var s_shell::runner Command execution state managed by the runner submodule.
 * @var s_shell::scanner Input scanner state managed by the scanner submodule.
 */
typedef struct s_shell
{
	t_alias		alias;
	t_builder	builder;
	t_heredoc	heredoc;
	t_history	history;
	t_params	params;
	t_runner	runner;
	t_scanner	scanner;
}	t_shell;

/* ************************************************************************* */
/*                                LIFE_CYCLE                                 */
/* ************************************************************************* */

void	shell_free_void(void);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @brief Returns the current global shell instance.
 *
 * @return Shell state, or NULL when the shell is unavailable (borrowed).
 */
t_shell		*shell_get(void);

/**
 * @brief Returns the alias state stored in the global shell.
 *
 * @return Alias state managed by the alias submodule, or NULL when
 *         the shell is unavailable. (borrowed)
 */
t_alias		*shell_get_alias(void);

/**
 * @brief Returns the builder state stored in the global shell.
 *
 * @return Builder state managed by the builder submodule, or NULL
 *         when the shell is unavailable. (borrowed)
 */
t_builder	*shell_get_builder(void);

/**
 * @brief Returns the here-document state stored in the global shell.
 *
 * @return Heredoc state managed by the heredoc submodule, or NULL
 *         when the shell is unavailable. (borrowed)
 */
t_heredoc	*shell_get_heredoc(void);

/**
 * @brief Returns the history state stored in the global shell.
 *
 * @return History state managed by the history submodule, or NULL
 *         when the shell is unavailable. (borrowed)
 */
t_history	*shell_get_history(void);

/**
 * @brief Returns the shell name.
 *
 * @return Shell name, or the static default "minishell"
 *         when the shell is unavailable. (borrowed, read-only)
 */
const char	*shell_get_name(void);

/**
 * @brief Returns the parameter state stored in the global shell.
 *
 * @return Params state managed by the params submodule, or NULL when
 *         the shell is unavailable. (borrowed)
 */
t_params	*shell_get_params(void);

/**
 * @brief Returns the runner state stored in the global shell.
 *
 * @return Runner state managed by the runner submodule, or NULL
 *         when the shell is unavailable. (borrowed)
 */
t_runner	*shell_get_runner(void);

/**
 * @brief Returns the scanner state stored in the global shell.
 *
 * @return Sscanner state managed by the scanner submodule, or NULL
 *         when the shell is unavailable. (borrowed)
 */
t_scanner	*shell_get_scanner(void);

/**
 * @brief Creates, loads, runs and frees the shell.
 *
 * Allocates the shell state, initializes every submodule, loads parameters,
 * history, scanner and builder state, then runs the command loop and handle
 * errors and all data freeing.
 *
 * @param argc Argument count.
 * @param argv Argument array (borrowed, read-only).
 * @param envp Environment array (borrowed, read-only).
 */
int		shell_run(int argc, char **argv, char **envp);

/**
 * @brief Reports whether interactive EOF should terminate the shell.
 *
 * @return ERR_NO when EOF can be ignored, ERR_VEOF when interactive EOF
 *         should stop the shell, or ERR_SHELL_NOT_FOUND if options are
 *         unavailable.
 */
t_error		shell_should_exit_on_veof(void);

// TODO
/**
 * @brief Reports a pending interrupt.
 *
 * @note Placeholder implementation, always returns ERR_INTERRUPTED for now.
 * @return ERR_NO when interruption can be ignored Eor RR_INTERRUPTED when
 *		   interruption should stop the shell.
 */
t_error		shell_should_interrupt(void);

#endif
