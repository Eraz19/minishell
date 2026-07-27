#ifndef SHELL_H
# define SHELL_H

# include <stdint.h>
# include "alias.h"
# include "params.h"
# include "history.h"
# include "lr_machine_type.h"
# include "runner_type.h"

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
	bool			is_subshell;
	t_params		params;
	t_lr_machine	machine;
	t_runner		*runner;		// owned (linked)
	t_runner		*last_runner;	// borrowed
	t_history		history;		// TODO: move to params
	t_alias			alias;			// TODO: move to params
}	t_shell;

typedef enum e_subshell_mode
{
	SUBSHELL_NORMAL,
	SUBSHELL_CMD_SUB_TRAP_ONLY,	// Not used (not mandatory)
	SUBSHELL_ASYNC_AND_OR		// async AND-OR list
}	t_subshell_mode;

/* ************************************************************************* */
/*                                LIFE_CYCLE                                 */
/* ************************************************************************* */

// TODO: doc
void	shell_clear(void);

/**
 * @brief Frees the current global shell instance when one is registered.
 *
 * @note This is a no-op when @ref shell_get() returns @c NULL.
 */
void	shell_free_void(void);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

#define shell_get_new_lexer(out_lexer_ptr, mode, input) shell_get_new_lexer_priv(out_lexer_ptr, mode, input, __func__)
#define shell_get_new_scanner(out_scanner_ptr, mode, input) shell_get_new_scanner_priv(out_scanner_ptr, mode, input, __func__)
#define shell_get_new_parser(out_parser_ptr, mode, input) shell_get_new_parser_priv(out_parser_ptr, mode, input, __func__)
#define shell_get_new_runner(out_runner_ptr, mode, input) shell_get_new_runner_priv(out_runner_ptr, mode, input, __func__)
#define shell_destroy_last_instance() shell_destroy_last_instance_priv(__func__)

t_error	shell_get_new_lexer_priv(
			t_lexer **out_lexer_ptr,
			t_scan_mode mode,
			const char *input,
			const char *caller);
t_error	shell_get_new_scanner_priv(
			t_scanner **out_scanner_ptr,
			t_scan_mode mode,
			const char *input,
			const char *caller);
t_error	shell_get_new_parser_priv(
			t_parser **out_parser_ptr,
			t_scan_mode mode,
			const char *input,
			const char *caller);
t_error	shell_get_new_runner_priv(
			t_runner **out_runner_ptr,
			t_scan_mode mode,
			const char *input,
			const char *caller);
t_error	shell_destroy_last_instance_priv(const char *caller);

// TODO: doc
t_error	shell_init_subshell(t_subshell_mode mode);

// TODO: doc
t_error	shell_is_subshell(bool *out);

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
 * @brief Returns the history state stored in the global shell.
 *
 * @return History state managed by the history submodule, or NULL
 *         when the shell is unavailable. (borrowed)
 */
t_history	*shell_get_history(void);

// TODO: doc
const t_lr_machine	*shell_get_lr_machine(void);

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
 * @brief Allocates, runs and frees the global shell instance.
 *
 * @note The function allocates the shell state, initializes and loads all
 *       submodules, executes the startup @c ENV hook, runs
 *       @ref runner_run(), saves history, then frees the shell before
 *       returning.
 *
 * @param argc Argument count.
 * @param argv Argument array (borrowed, read-only).
 * @param envp Environment array (borrowed, read-only).
 * @param build_lr_tables Specifies if parser tables need to be built.
 * @return Integer form of the final error type, or @c ERR_NO on success.
 */
int			shell_run(int argc, char **argv, char **envp, bool build_parser_tables);

#endif
