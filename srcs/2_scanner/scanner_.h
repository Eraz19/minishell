#ifndef SCANNER__H
# define SCANNER__H

# include "scanner.h"

/**
 * @ingroup scanner
 * @brief Tests whether the input is fully consumed (non-STDIN modes).
 *
 * True when the lexer has reached end-of-input, the mode is not STDIN (which
 * keeps prompting for more) and no input remains on the lexer's input stack.
 *
 * @param state Pointer to the scanner state (borrowed).
 * @return true when no more tokens can be produced.
 */
bool		is_EOF(t_scanner *state);

/**
 * @ingroup scanner
 * @brief Reads the next chunk of input and pushes it on the lexer stack.
 *
 * Allocates an input item and fills it according to the mode (whole file,
 * duplicated command string, or one stdin line), then pushes it; on error the
 * item is freed and not pushed. Called only when the input stack is empty.
 *
 * @param state Pointer to the scanner state (borrowed).
 * @return ERR_NO on success, ERR_LIBC on allocation failure, or the reader's
 *         error.
 */
t_error		scanner_read_input(t_scanner *state);

/**
 * @ingroup scanner
 * @brief Collects the bodies of the here-documents pending after a newline.
 *
 * Reads the queued here-document bodies from the current input position,
 * advancing the input cursor past them.
 *
 * @param state Pointer to the scanner state (borrowed).
 * @return ERR_NO on success, or the here-document module's error.
 */
t_error		scanner_heredoc_store(t_scanner *state);

/**
 * @ingroup scanner
 * @brief Expands a word token's alias and re-lexes from the expansion.
 *
 * When @p token expands, pushes the expansion as a new input on the lexer
 * stack and re-runs the lexer so the next token comes from the expanded text;
 * otherwise leaves @p token unchanged.
 *
 * @param state Pointer to the scanner state (borrowed).
 * @param token Word token to expand and replace (borrowed).
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error		scanner_alias_expand(t_scanner *state, t_token *token);

#endif
