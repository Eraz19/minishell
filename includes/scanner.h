#ifndef SCANNER_H
# define SCANNER_H

# include "error.h"
# include "token.h"
# include "heredoc.h"
# include "lexer_.h"

/** @defgroup scanner Scanner API
 *  @brief Turns raw shell input into a POSIX token stream.
 *
 *  The scanner is the front end of the shell: it reads input incrementally
 *  (from a file, a command string or standard input), drives the lexer to
 *  recognise one token at a time following POSIX token recognition rules, and
 *  collects the here-documents the parser reports along the way. It also
 *  triggers alias expansion on word tokens by pushing the expansion back onto
 *  the lexer's input stack.
 *
 *  The lexer is held behind an opaque pointer (@ref t_lexer is incomplete
 *  here), so consumers of this header see only the scanner's public surface;
 *  the lexer internals stay private to the scanner module. The scanner owns
 *  its lexer and here-document state: scanner_init() allocates them and
 *  scanner_free() releases them.
 */

/**
 * @ingroup scanner
 * @enum e_scanner_mode
 * @brief Where the scanner reads its input from.
 */
typedef enum e_scanner_mode
{
	SCAN_NONE,		/**< Unset / not yet loaded. */
	SCAN_FILE,		/**< Read the whole input from a file path. */
	SCAN_STRING,	/**< Read the input from an in-memory command string. */
	SCAN_STDIN_TTY,	/**< Read input line-by-line from standard input, with a terminal. */
	SCAN_STDIN_PIPE	/**< Read input line-by-line from standard input. */
}	t_scanner_mode;

/**
 * @ingroup scanner
 * @struct s_scanner
 * @brief Aggregate state of the scanner module.
 *
 * @var s_scanner::err Last error recorded by the module.
 * @var s_scanner::mode Source the input is read from (file, stdin, string).
 * @var s_scanner::lexer Owned lexer state (opaque; allocated by scanner_init).
 * @var s_scanner::source Borrowed file path or command string for FILE/STRING
 *                        modes; unused for STDIN.
 */
typedef struct s_scanner
{
	t_error			err;
	t_scanner_mode	mode;
	t_lexer			lexer;
	const char		*source;
}	t_scanner;

t_error	scanner_init(t_scanner *state);

void	scanner_free(t_scanner *state);

t_error	scanner_load(t_scanner *state, const char *source);

t_error	scanner_reset(t_scanner *state);

t_error	scanner_get_next_token(t_token *token);

t_error	scanner_report_io_here(t_buff *path, char *delim, t_heredoc_mode mode);

t_error	scanner_heredoc_read(void);

t_error	scanner_read_continuation(char **res);

#endif
