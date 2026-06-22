#ifndef LEXER__H
# define LEXER__H

# include "token.h"
# include "error.h"
# include "context.h"
# include "input_stack_.h"

/**
 * @ingroup scanner
 * @struct s_lexer_backup
 * @brief Snapshot of the lexer used to roll back a speculative scan.
 *
 * Captures just enough state to undo a partial scan (used when an arithmetic
 * expansion turns out not to be one and must be retried as a command
 * substitution).
 *
 * @var s_lexer_backup::i Input cursor position to restore.
 * @var s_lexer_backup::token_type Token type to restore.
 * @var s_lexer_backup::context_len Context-stack depth to unwind back to.
 * @var s_lexer_backup::token_value_len Token value length to truncate back to.
 */
typedef struct s_lexer_backup
{
	size_t			i;
	t_token_type	token_type;
	size_t			context_len;
	size_t			token_value_len;
	size_t			token_contexts_len;
}	t_lexer_backup;

/**
 * @ingroup scanner
 * @struct s_lexer
 * @brief State of the lexer that recognises one token at a time.
 *
 * @var s_lexer::err Last error recorded by the lexer.
 * @var s_lexer::input Borrowed pointer to the current input item on top of the
 *                     stack (its string, cursor and per-input context stack).
 * @var s_lexer::token Borrowed pointer to the token currently being built.
 * @var s_lexer::is_stdin Whether input is streamed line-by-line from stdin
 *                        (interactive terminal or pipe), enabling line
 *                        continuation and here-document body reads.
 * @var s_lexer::input_stack Stack of inputs; alias expansions and line
 *                           continuations are pushed on top of the base input.
 * @var s_lexer::reached_EOI Set when end-of-input was reached with no token.
 * @var s_lexer::emited_token Set when a complete token has been delimited.
 */
typedef struct s_lexer
{
	t_error				err;
	t_input_stack_item	*input;
	t_token				*token;
	bool				is_stdin;
	t_input_stack		input_stack;
	bool				reached_EOI;
	bool				emited_token;
}	t_lexer;

/**
 * @ingroup scanner
 * @brief Releases the lexer's input stack and resets it to zero.
 * @param state Pointer to the lexer state (borrowed).
 */
void			lexer_free(t_lexer *state);

/**
 * @ingroup scanner
 * @brief Initialises the lexer to an empty, ready-to-use value.
 * @param state Pointer to the lexer state (borrowed).
 */
void			lexer_init(t_lexer *state);

/**
 * @ingroup scanner
 * @brief Records whether input is streamed line-by-line from stdin.
 * @param state Pointer to the lexer state (borrowed).
 * @param is_stdin true when reading incrementally from stdin (terminal/pipe).
 */
void			lexer_load(t_lexer *state, bool is_stdin);

/**
 * @ingroup scanner
 * @brief Snapshots the lexer for a possible later rollback.
 * @param state Pointer to the lexer state (borrowed).
 * @return A backup capturing cursor, token type/length and context depth.
 */
t_lexer_backup	lexer_backup(t_lexer *state);

/**
 * @ingroup scanner
 * @brief Marks the token currently being built as complete.
 * @param state Pointer to the lexer state (borrowed).
 */
void			lexer_delimit_token(t_lexer *state);

/**
 * @ingroup scanner
 * @brief Advances the input cursor by @p offset characters (no consumption).
 * @param state Pointer to the lexer state (borrowed).
 * @param offset Number of characters to skip.
 */
void			lexer_advance(t_lexer *state, size_t offset);

/**
 * @ingroup scanner
 * @brief Restores the lexer to a previously captured backup.
 *
 * Pops contexts back to the snapshot depth, then restores the cursor, token
 * type and token value length.
 *
 * @param state Pointer to the lexer state (borrowed).
 * @param backup Snapshot to restore.
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error			lexer_restore(t_lexer *state, t_lexer_backup backup);

/**
 * @ingroup scanner
 * @brief Appends @p iter input characters to the token and advances.
 *
 * Copies the next @p iter characters into the token value, tags the token with
 * @p type and advances the cursor by the same amount.
 *
 * @param state Pointer to the lexer state (borrowed).
 * @param type Token type to assign while consuming.
 * @param iter Number of characters to consume.
 * @return ERR_NO on success, ERR_LIBC on allocation failure.
 */
t_error			lexer_consume(t_lexer *state, t_token_type type, size_t iter);

/**
 * @ingroup scanner
 * @brief Tests whether the current character can extend/begin an operator.
 * @param state Pointer to the lexer state (borrowed).
 * @return true when the current character is part of an operator token.
 */
bool			is_operator_char(t_lexer *state);

/**
 * @ingroup scanner
 * @brief Consumes the current operator character into the token.
 *
 * Dispatches on the current character to the matching operator builder,
 * extending the operator token by one character.
 *
 * @param state Pointer to the lexer state (borrowed).
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error			lexer_add_char_into_token_operator(t_lexer *state);

/**
 * @ingroup scanner
 * @brief Scans a quoting or expansion construct of the given context.
 *
 * Dispatches to the matching context scanner (single/double/ANSI-C quotes,
 * parameter, arithmetic, backquote). Command substitution is not yet
 * implemented.
 *
 * @param state Pointer to the lexer state (borrowed).
 * @param context Context to scan.
 * @return ERR_NO on success, or the recorded error (e.g. ERR_NOT_IMPLEMENTED).
 */
t_error			lexer_context(t_lexer *state, t_context context);

/**
 * @ingroup scanner
 * @brief Applies one POSIX token-recognition rule to the current character.
 *
 * Tested in POSIX §2.3 order: end-of-input, operator-in-progress, quoting,
 * expansion, new operator, blank, in-word, comment, then new word.
 *
 * @param state Pointer to the lexer state (borrowed).
 * @param context Out-parameter receiving the detected context, if any.
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error			lexer_rules(t_lexer *state, t_context *context);

/**
 * @ingroup scanner
 * @brief Produces the next token from the top input on the stack.
 *
 * Reads the current input, initialises @p token, then applies recognition
 * rules until a token is delimited or end-of-input is reached; pops the input
 * on end-of-input.
 *
 * @param state Pointer to the lexer state (borrowed).
 * @param token Out-parameter receiving the produced token (borrowed).
 * @return ERR_NO on success, ERR_EMPTY_STACK if no input remains, or the
 *         recorded error on failure.
 */
t_error			lexer_next_token(t_lexer *state, t_token *token);

#endif
