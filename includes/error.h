#ifndef ERROR_H
# define ERROR_H

#include <stdbool.h>

# define ERR_POSIX_SIGNAL_BASE_CODE	128

typedef enum e_error_type
{
	// Success
	ERR_NO,									// [ 0]
	/* -------------------- UNQUALIFIED ERRORS -------------------- */
	// Failures
	ERR_ASSIGNMENT_MISSING_NAME,			// [ 1]
	ERR_FD_INVALID,							// [ 1]
	ERR_FORMAT_INVALID,						// [ 1]
	ERR_HOOK_INVALID_RHS_LEN,				// [ 1]
	ERR_INDEX_OUT_OF_BOUND,					// [ 1]
	ERR_LR_CONFLICT,						// [ 1]
	ERR_LR_STATE_NOT_FOUND,					// [ 1]
	ERR_PARSER_EMPTY_GOTO,					// [ 1]
	ERR_PARSER_INVALID_FUNCTION_NAME,		// [ 1]
	ERR_PARSER_INVALID_STATE,				// [ 1]
	ERR_SHELL_NOT_FOUND,					// [ 1]
	ERR_SHIFT_INVALID_VALUE,				// [ 1]
	ERR_SIZE_MAX_REACHED,					// [ 1]
	ERR_VAR_INVALID_NAME,					// [ 1]
	ERR_VAR_MISSING_EQUAL,					// [ 1]
	ERR_VAR_NOT_FOUND,						// [ 1]
	ERR_VAR_READ_ONLY,						// [ 1]
	// Lexer failures
	ERR_CTX_END_NOT_FOUND,					// [ 1] [SCANNER]		Internal signal: $(( did not close as arithmetic; absorbed by the cmd_sub rescan inside the lexer (qualify retype to ERR_POSIX_SYNTAX = safety net only)
	ERR_EMPTY_STACK,						// [ 1]
	ERR_HISTORY_DISABLED,					// [ 1]
	ERR_NO_DELIM,							// [ 1] [SCANNER]		Missing here-doc delimiter, printed at production by the heredoc; requalified as ERR_NO at the scanner exit (documented benign choice, POSIX 2.7.4 "should, but need not, treat this as a redirection error")
	ERR_NOT_IMPLEMENTED,					// [ 1] 
	ERR_NO_INPUT_TO_LEX,					// [ 1] 
	ERR_EXP_RESULT_INCOHERENT,				// [ 1] 
	ERR_QUOTED_TILDE,						// [ 1] [EXPANDER]		Internal control flow, never escapes: a quoted tilde stays literal
	ERR_PARAM_NULL_OR_UNSET,				// [ 1] [EXPANDER]		Requalified as ERR_POSIX_EXPANSION (printed at production with the parameter name)
	ERR_PARAM_BAD_SUBSTITUTION,				// [ 1] [EXPANDER]		Requalified as ERR_POSIX_EXPANSION (printed)
	ERR_ALIAS_NOT_FOUND,					// [ 1] [BUILTINS]		alias/unalias: requalified as ERR_BUILTIN, printed there with the utility name
	ERR_ALIAS_INVALID_NAME,					// [ 1] [BUILTINS]
	ERR_SIG_WAS_IGNORED_ON_ENTRY,			// [ 1] [TRAP]			Absorbed by trap special builtin
	// BUILTIN_WAIT
	ERR_PID_INVALID,						// [ 1]	[WAIT]			Absorbed by wait builtin
	// UTILS (file_search() and file_check())
	ERR_FILE_NOT_FOUND,						// [ 1]	[CALLER]		Requalified as ERR_POSIX_CMD_NOT_FOUND / ERR_SPECIAL_BUITLIN or absorbed
	ERR_FILE_NOT_EXECUTABLE,				// [ 1]	[CALLER]		Requalified as ERR_POSIX_CMD_NOT_EXECUTABLE or absorbed
	ERR_FILE_NOT_READABLE,					// [ 1]	[CALLER]		Requalified as ERR_SPECIAL_BUITLIN or absorbed
	// FT_GETOPT
	ERR_OPT_INVALID,						// [ 1] [FT_GETOPT]		Requalified as ERR_INVALID_USAGE (printed)
	ERR_OPT_INVALID_ARG,					// [ 1] [FT_GETOPT]		Requalified as ERR_INVALID_USAGE (printed)
	ERR_OPT_MISSING_ARG,					// [ 1] [FT_GETOPT]		Requalified as ERR_INVALID_USAGE (printed)
	/* -------------------- PARTIALLY QUALIFIED ERRORS -------------------- */
	// posix_write()
	ERR_POSIX_WRITE = 90,					// [ 4] [CALLER]		Requalified as ??? (special POSIX treatment required)
	// OPTIONS (produced by ft_getopt() + posix_open*())
	ERR_INVALID_USAGE = 91,					// [ 4] [CALLER]		Requalified as ???
	// REDIRECTOR (+ GENERIC ERRORS)
	ERR_REDIRECTION = 92,					// [ 4] [EXECUTOR]		Requalified as ERR_POSIX_REDIR_SPECIAL or dropped
	// BUILTINS EXIT CODES (+ GENERIC ERRORS)
	ERR_BUILTIN = 93,						// [ 4] [EXECUTOR]		Requalified as ERR_POSIX_BUILTIN_SPECIAL or absorbed
	/* -------------------- FLOW CONTROL ERRORS -------------------- */
	ERR_VEOF = 100,							// [ 2]	[RUNNER]		"CTRL+D" received: Absorbed (may exit with $? status)
	ERR_EOF = 101,							// [ 2]	[RUNNER]		End of input reached: Absorbed (may exit with $? status)
	ERR_CONTINUE = 102,						// [ 5] [LOOP WALKER]	Absorbed by targeted loop (or external one)
	ERR_BREAK = 103,						// [ 5] [LOOP WALKER]	Absorbed by targeted loop (or external one)
	ERR_RETURN = 104,						// [ 5] [FUNC WALKER]	Absorbed (exit status is produced by the builtin)
	ERR_EXIT_WITH_CURRENT_STATUS = 105,		// [ 5] [SIG / PIPE]	Requalified as ERR_EXIT after setting $? properly
	ERR_EXIT = 106,							// [ 5] [-]				Exit builtin has been called with n as argument or ERR_EXIT_WITH_CURRENT_STATUS has been requalified
	ERR_INTERRUPTED = 107,					// [ 5] [WAIT]			Absorbed by wait builtin
	/* -------------------- FULLY QUALIFIED ERRORS -------------------- */
	// INTERNAL ERRORS (can be returned by any module or builtin)
	ERR_UB = 108,							// [ 5] [-]				[?-?-Y]	Always fatal
	ERR_INTERNAL = 110,						// [ 9] [-]				[Y-Y-Y]	Always fatal
	ERR_LIBC = 111,							// [10] [-]				[Y-Y-Y]	Always fatal
	// POSIX EXIT CODES
	ERR_POSIX_SYNTAX = 121,					// [ 6] [RUNNER]		[Y-N-Y] Absorbed / bubbled up
	ERR_POSIX_BUILTIN_SPECIAL = 122,		// [ 6] [SCMD WALKER]	[Y-N-N] Absorbed / bubbled up
	ERR_POSIX_REDIR_SPECIAL = 123,			// [ 6] [SCMD WALKER]	[Y-N-Y] Absorbed / bubbled up (walk_scmd / walk_command / walk_function)
	ERR_POSIX_ASSIGNMENT = 124,				// [ 6] [SCMD WALKER]	[Y-N-Y] Absorbed / bubbled up
	ERR_POSIX_EXPANSION = 125,				// [ 6] [WALKERS]		[Y-N-Y] Absorbed / bubbled up (TODO: which walkers)
	ERR_POSIX_CMD_NOT_EXECUTABLE = 126,		// [ 6] [SCMD WALKER]	[N-N-N] Absorbed / bubbled up
	ERR_POSIX_CMD_NOT_FOUND = 127,			// [ 6] [SCMD WALKER]	[N-N-Y] Absorbed / bubbled up
	ERR_POSIX_READ = 128,					// [ 6] [-]				[Y-Y-Y] Always fatal
	// POSIX SIGNAL CODES (128 + signal)	// [ 6] [-]				TODO: signal management
}	t_error_type;
/*
Legend:
	[n]			=> error priority => the error with the highest priority wins in error_priorize()
	[<module>]	=> module in charge of error frontier
	[A-B-C]		=> A = shall exit (non-interactive) | B = shall exit (interactive) | C = shall print diagnostic
	Errors should be printed as they are requalified to avoid losing diagnostic precision
	Only final error codes are set to specific values => they are the exit status of the shell itself
*/

// TODO: ⚠️ In all of the cases shown in the table where an interactive shell is required not to exit and a non-interactive shell is required to exit, an interactive shell shall not perform any further processing of the command in which the error occurred.

#define error(type) error_priv(type, __FILE__, __LINE__, __func__)	//DEBUG
#define error_sys() error_sys_priv(__FILE__, __LINE__, __func__)	//DEBUG

typedef struct s_error
{
	t_error_type	type;
	int				saved_errno;
	bool			printed;
}	t_error;

t_error		error_priv(t_error_type type, const char *file, int line, const char *caller);	// DEBUG
t_error		error_sys_priv(const char *file, int line, const char *caller);	// DEBUG
t_error		error_print(t_error err, ...);
t_error		error_priorize(t_error previous, t_error new);
const char	*error_to_string(t_error err);
t_error		undefined_behaviour(const char *message);
void		print_unspecified_behaviour(
				const char *optional_prefix,
				const char *posix_citation,
				const char *implemented_as);
t_error		error_drop_non_fatal(t_error err);
bool		error_is_flow_control(t_error err);
t_error		err_infinite_loop(void);

#endif
