#ifndef ERROR_H
# define ERROR_H

#include <stdbool.h>

# define ERR_POSIX_SIGNAL_BASE_CODE	128

typedef enum e_error_type
{
	// Success
	ERR_NO,
	/* -------------------- UNQUALIFIED ERRORS -------------------- */
	// Failures
	ERR_ASSIGNMENT_MISSING_NAME,
	ERR_EOF,
	ERR_FD_INVALID,
	ERR_FORMAT_INVALID,
	ERR_HOOK_INVALID_RHS_LEN,
	ERR_INDEX_OUT_OF_BOUND,
	ERR_LR_CONFLICT,
	ERR_LR_STATE_NOT_FOUND,
	ERR_PARSER_EMPTY_GOTO,
	ERR_PARSER_INVALID_FUNCTION_NAME,
	ERR_PARSER_INVALID_STATE,
	ERR_SHELL_NOT_FOUND,
	ERR_SHIFT_INVALID_VALUE,
	ERR_SIZE_MAX_REACHED,
	ERR_VAR_INVALID_NAME,
	ERR_VAR_MISSING_EQUAL,
	ERR_VAR_NOT_FOUND,
	ERR_VAR_READ_ONLY,
	// Lexer failures
	ERR_CMD_SUB_CLOSING_NOT_FOUND,			// [SCANNER]	Requalified as ERR_POSIX_SYNTAX (printed)
	ERR_CTX_END_NOT_FOUND,					// [SCANNER]	Requalified as ERR_POSIX_SYNTAX (printed)
	ERR_EMPTY_STACK,
	ERR_HEREDOC_MAX_ID_REACHED,
	ERR_HISTORY_DISABLED,
	ERR_INCOHERENT_STATE,
	ERR_NO_DELIM,							// [SCANNER]	Requalified as ERR_POSIX_SYNTAX (printed)
	ERR_NOT_IMPLEMENTED,
	ERR_UNEXPECTED_EOI,						// [SCANNER]	Requalified as ERR_POSIX_SYNTAX (printed)
	ERR_VEOF,								// [RUNNER]		Top-level end of input: exit decision belongs to the shell loop (never printed). Mid-construct: requalified as ERR_POSIX_SYNTAX by [SCANNER] (printed)
	ERR_NO_INPUT_TO_LEX,
	ERR_EXP_RESULT_INCOHERENT,
	ERR_QUOTED_TILDE,						// [EXPANDER]	Internal control flow, never escapes: a quoted tilde stays literal
	ERR_PARAM_NULL_OR_UNSET,				// [EXPANDER]	Requalified as ERR_POSIX_EXPANSION (printed at production with the parameter name)
	ERR_PARAM_BAD_SUBSTITUTION,				// [EXPANDER]	Requalified as ERR_POSIX_EXPANSION (printed)
	ERR_BAD_SUBSTITUTION,					// [EXPANDER]	Requalified as ERR_POSIX_EXPANSION (printed); currently produced nowhere
	ERR_ALIAS_NOT_FOUND,					// [BUILTINS]	alias/unalias: requalified as ERR_BUILTIN, printed there with the utility name
	// FT_GETOPT
	ERR_OPT_INVALID,						// [FT_GETOPT]	Requalified as ERR_INVALID_USAGE (printed)
	ERR_OPT_INVALID_ARG,					// [FT_GETOPT]	Requalified as ERR_INVALID_USAGE (printed)
	ERR_OPT_MISSING_ARG,					// [FT_GETOPT]	Requalified as ERR_INVALID_USAGE (printed)
	/* -------------------- PARTIALLY QUALIFIED ERRORS -------------------- */
	// posix_write()
	ERR_POSIX_WRITE,						// [CALLER]		write error (special POSIX treatment required)
	// OPTIONS (produced by ft_getopt() + posix_open*())
	ERR_INVALID_USAGE,						// [CALLER]		Options and / or arguments are invalid
	// REDIRECTOR (+ GENERIC ERRORS)
	ERR_REDIRECTION,						// [EXECUTOR]	Requalified as ERR_REDIRECTION_SPECIAL / ERR_REDIRECTION_OTHER. Unterminated here-document: requalified as ERR_POSIX_SYNTAX by [SCANNER] (printed by heredoc)
	// BUILTINS EXIT CODES (+ GENERIC ERRORS)
	ERR_BUILTIN,							// [EXECUTOR]	Requalified as ERR_POSIX_BUILTIN_SPECIAL / ERR_POSIX_UTILITY
	/* -------------------- FULLY QUALIFIED ERRORS -------------------- */
	// GENERIC ERRORS (can be returned by any module or builtin)
	ERR_INTERRUPTED = 115,					// [-]			[Y-Y-?] Shell interrupted by signal
	ERR_UB = 116,							// [-]			[?-?-Y]	Undefined behaviour
	ERR_INTERNAL = 117,						// [-]			[Y-Y-Y]	Shell internal error
	ERR_LIBC = 118,							// [-]			[Y-Y-Y]	System or libc error
	// POSIX EXIT CODES
	ERR_POSIX_SYNTAX = 119,					// [-]			[Y-N-Y] Shell language syntax error
	ERR_POSIX_BUILTIN_SPECIAL = 120,		// [-]			[Y-N-N] Special built-in utility error (⚠️ do NOT exit if executed via `command`)
	ERR_POSIX_UTILITY = 121,				// [-]			[N-N-N] Other utility error
	ERR_REDIRECTION_SPECIAL = 122,			// [-]			[Y-N-Y] Redirection error with special built-in utilities
	ERR_REDIRECTION_OTHER = 123,			// [-]			[N-N-Y] Redirection error with non-special built-in utilities
	ERR_POSIX_ASSIGNMENT = 124,				// [-]			[Y-N-Y] Variable assignment error
	ERR_POSIX_EXPANSION = 125,				// [-]			[Y-N-Y] Expansion error
	ERR_POSIX_CMD_NOT_EXECUTABLE = 126,		// [-]			???
	ERR_POSIX_CMD_NOT_FOUND = 127,			// [-]			[?-N-Y] Command not found
	ERR_POSIX_READ = 128,					// [-]			[Y-Y-Y] Unrecoverable read error when reading commands
	// POSIX SIGNAL CODES (128 + signal code)
}	t_error_type;
/*
Legend:
	[<module>]	=> module in charge of error requalification ("-" means fully qualified)
	[A-B-C]		=> A = shall exit (non-interactive) | B = shall exit (interactive) | C = shall print diagnostic
	Errors should be printed as they are requalified to avoid losing diagnostic precision
	Only final error codes are set to specific values => they are the exit status of the shell itself
*/

// ⚠️ In all of the cases shown in the table where an interactive shell is required not to exit and a non-interactive shell is required to exit, an interactive shell shall not perform any further processing of the command in which the error occurred.

#define error(type) error_priv(type, __FILE__, __LINE__, __func__)	//DEBUG
#define error_sys() error_sys_priv(__FILE__, __LINE__, __func__)	//DEBUG

typedef struct s_error
{
	t_error_type	type;
	int				saved_errno;
	bool			printed;
}	t_error;

/**
 * @brief Builds an error descriptor from an internal error type.
 *
 * The saved errno value is set to 0.
 *
 * @warning Use error_sys() instead when the error comes from a failed libc or
 * POSIX call and errno must be preserved.
 *
 * @param type Error type to store.
 * @return Error descriptor containing type and no saved errno.
 */
t_error	error_priv(t_error_type type, const char *file, int line, const char *caller);	// DEBUG

/**
 * @brief Builds a libc error descriptor and saves the current errno value.
 *
 * This function must be called immediately after a failed libc or POSIX call,
 * before any other call can overwrite errno.
 *
 * @return Error descriptor containing ERR_LIBC and the current errno value.
 */
t_error	error_sys_priv(const char *file, int line, const char *caller);	// DEBUG

/**
 * @brief Prints a formatted shell error message to stderr.
 *
 * The shell name prefix is printed automatically by this function, since its value
 * depends on the current shell context. Additional prefixes passed by the caller
 * are printed after it, in order, and separated with ": ".
 *
 * The variadic argument list must follow this exact layout:
 * prefixes..., NULL, fstring, fstring arguments...
 *
 * The NULL separator marks the end of the caller-provided prefix list. If fstring
 * is not NULL, it is used as a printf-like format string and must be followed by
 * the matching arguments. If fstring is NULL, no format arguments are read.
 *
 * Example:
 * error_print(error(ERR_OPT_INVALID), "export", "-x", NULL, "%i", my_integer);
 *
 * @warning The caller-provided prefix list must always be terminated by NULL.
 * @warning fstring arguments must match the conversion specifiers used by fstring.
 *
 * @param error Error descriptor to print and return.
 * @param ... Additional prefixes, NULL separator, optional format string, optional arguments.
 * @return The error descriptor received as argument.
 */
t_error	error_print(t_error err, ...);

const char	*error_to_string(t_error err);

// @ret ERR_UB
t_error	undefined_behaviour(const char *message);

void	print_unspecified_behaviour(
			const char *posix_citation,
			const char *implemented_as);

#endif
