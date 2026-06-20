/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 16:05:23 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/20 15:35:56 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	SCAN_STDIN,		/**< Read input line-by-line from standard input. */
	SCAN_STRING		/**< Read the input from an in-memory command string. */
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
 * @var s_scanner::heredoc Owned here-document collector for the pending queue.
 */
typedef struct s_scanner
{
	t_error			err;
	t_scanner_mode	mode;
	t_lexer			lexer;
	const char		*source;
	t_heredoc		heredoc;
}	t_scanner;

/**
 * @ingroup scanner
 * @brief Initialises a scanner to an empty, ready-to-use value.
 *
 * Zeroes the structure, allocates and initialises the lexer, and initialises
 * the here-document collector. Must be called before scanner_load() or
 * scanner_next_token().
 *
 * @param state Pointer to the scanner state to initialise (borrowed).
 * @return ERR_NO on success, ERR_LIBC if the lexer allocation fails.
 */
t_error	scanner_init(t_scanner *state);

/**
 * @ingroup scanner
 * @brief Releases every resource held by a scanner state.
 *
 * Frees the lexer (its contents and the allocation itself) and the
 * here-document collector, then resets the structure to zero.
 *
 * @param state Pointer to the scanner state to free (borrowed).
 */
void	scanner_free(t_scanner *state);

/**
 * @ingroup scanner
 * @brief Selects the input source for the next scan.
 *
 * Records the mode and, for FILE/STRING modes, the borrowed source string,
 * and propagates the interactivity flag to the lexer and the here-document
 * collector (true only for STDIN mode).
 *
 * @param state Pointer to the scanner state (borrowed).
 * @param mode Where to read input from.
 * @param source File path (FILE) or command string (STRING), borrowed; unused
 *               for STDIN.
 * @return The error currently recorded on the scanner.
 */
t_error	scanner_load(t_scanner *state, t_scanner_mode mode, const char *source);

/**
 * @ingroup scanner
 * @brief Produces the next token from the input.
 *
 * Reads more input when the current input is exhausted, asks the lexer for one
 * token, and on the way: stores pending here-document bodies after a newline,
 * and expands aliases on word tokens. Yields a token of type EOF_ once the
 * input is fully consumed. Operates on the global shell scanner state.
 *
 * @warning @p token must have been initialised (and any previous value freed)
 *          with token_init() before this call.
 *
 * @param token Out-parameter receiving the produced token (borrowed; the
 *              caller owns its value buffer).
 * @return ERR_NO on success, ERR_SHELL_NOT_FOUND if the shell scanner state is
 *         unavailable, or the recorded error on failure.
 */
t_error	scanner_next_token(t_token *token);

/**
 * @ingroup scanner
 * @brief Queues a here-document read reported by the parser.
 *
 * Enqueues a here-document with its target path, delimiter and mode so its
 * body is collected when the current line's newline is reached. Operates on
 * the global shell scanner state.
 *
 * @param path Out/in-parameter for the here-document target path (borrowed).
 * @param delim Here-document delimiter word (borrowed).
 * @param mode Here-document mode (e.g. tab-stripping for <<-).
 * @return ERR_NO on success, ERR_SHELL_NOT_FOUND if the shell scanner state is
 *         unavailable, or the recorded error on failure.
 */
t_error	scanner_report_io_here(char **path, char *delim, t_heredoc_mode mode);

#endif
