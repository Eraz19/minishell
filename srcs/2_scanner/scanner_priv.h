#ifndef SCANNER_PRIV_H
# define SCANNER_PRIV_H

# include "scanner.h"

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup scanner
 * @brief Replaces the word token @p out with the tokens lexed from its
 *        alias expansion: consults the parser for the position check,
 *        fetches the alias value, frees @p out and pushes the expansion
 *        as the new lexer input.
 *
 * @warning Depends on @c env_get_alias, currently an unresolved symbol
 *          (defined in the env branch, resolves at merge): the merge
 *          contract is a borrowed value and @c ERR_VAR_NOT_FOUND on
 *          lookup miss — the miss lane below relies on that type.
 *
 * @note A lookup miss (@c ERR_VAR_NOT_FOUND) is absorbed to @c ERR_NO
 *       with @p out kept as a plain word.
 * @note Eligibility gate (POSIX 2.3.1): the word must be unquoted AND
 *       either sit in a command-word position (LR check through
 *       @ref parser_can_next_token_be_a_cmd_name_or_word) or follow an
 *       alias expansion whose value ended in a blank
 *       (@c alias_position_exempt, consumed by the check). Ineligible
 *       words are kept untouched and report @c ERR_NO.
 *
 * @param scanner Already loaded scanner (borrowed).
 * @param out Word token to expand; kept on lookup miss, freed and
 *            replaced by the first token of the expansion on success
 *            (borrowed).
 * @return Through @ref scanner_requalify_error: @c ERR_NO on success or
 *         lookup miss, @c ERR_POSIX_SYNTAX (printed, relex hit an
 *         unterminated construct) or @c ERR_LIBC (printed; module
 *         allocation failure) on module-produced failure.
 *         Module-external errors (alias lookup, parser position check)
 *         bubble through the qualification unlisted.
 */
t_error	expand_alias(t_scanner *scanner, t_token *out);

/**
 * @ingroup scanner
 * @brief Grows the current lexer input with one PS2 continuation line
 *        when @p scanner's mode allows it (@c SCAN_MODE_CMD_SUB or
 *        @c SCAN_MODE_STDIN), then appends the same continuation text to
 *        the current input of every ancestor scanner: their input stacks
 *        are private copies (@ref lexer_input_stack_dup at fork), so the
 *        forwarding keeps the text — and later cursor advances past the
 *        construct — aligned across the chain.
 *
 * @note @c ERR_NO guarantees at least one character was appended to the
 *       current input (@ref reader_read_PS2 contract); callers rely on
 *       this to tell "input grew" from "no more input".
 * @note Forwarding targets each ancestor's CURRENT input and relies on
 *       the mirrored-stack invariant: a construct-scan continuation is
 *       only requested with the root input current
 *       (@ref on_context_scan_EOI pops stacked aliases first), and the
 *       blocked ancestors hold the same stack shape as the child at
 *       fork. The parser-driven lane can target an alias input when the
 *       alias value embeds a newline — benign: the appended text is
 *       lexed to exhaustion before the alias pops, on both sides of the
 *       mirror.
 * @note Errors leave RAW on purpose: @c scanner->err is mirrored but no
 *       qualification or printing happens here. The lexer end-of-input
 *       handler converts the @c ERR_POSIX_SYNTAX report into the named
 *       unterminated diagnostic and the heredoc converts both reports
 *       into the missing-delimiter one; other callers must qualify
 *       themselves.
 *
 * @param scanner Already loaded scanner (borrowed).
 * @return @c ERR_NO on success; @c ERR_POSIX_SYNTAX (unprinted: mode
 *         without continuations or shell not interactive — no
 *         continuation is possible, converted or frontier-printed
 *         downstream), @c ERR_VEOF (interactive end of input: @c CTRL+D
 *         or ignored-EOF budget exhausted) or @c ERR_LIBC (module
 *         allocation / libc failure) on module-produced failure — raw
 *         and unprinted. Module-external errors (options, params,
 *         history, sig) bubble through unlisted.
 */
t_error	read_and_propagate_PS2(t_scanner *scanner);

/**
 * @ingroup scanner
 * @warning Dead declaration: defined nowhere in the tree and never
 *          called. TODO: implement or remove.
 */
t_error	scanner_load_cmd_sub(t_scanner *scanner);

/**
 * @ingroup scanner
 * @brief Ensures the lexer has input to consume: reads a PS2
 *        continuation when @p ps2 is set, otherwise stacks the first
 *        input of the scanner's mode when the input stack is empty.
 *
 * @note @c ERR_VEOF passes verbatim on both lanes (exit contract) and
 *       only arises from interactive end of input (@c CTRL+D at PS1 on
 *       the stacking lane, at PS2 on the continuation lane); a
 *       continuation impossible in @c SCAN_MODE_FILE / @c SCAN_MODE_STRING
 *       is the @c ERR_POSIX_SYNTAX produced by
 *       @ref read_and_propagate_PS2, printed at the exit frontier.
 *
 * @param scanner Already loaded scanner (borrowed).
 * @param out Only written when no input can be stacked at all:
 *            initialized as a @c TOKEN_EOF token (borrowed).
 * @param ps2 True to grow the current input instead of stacking one.
 * @return @c ERR_NO on success or when the input stack is already
 *         non-empty. Both lanes through @ref scanner_requalify_error:
 *         @c ERR_VEOF (end of input), @c ERR_POSIX_READ,
 *         @c ERR_POSIX_CMD_NOT_FOUND and @c ERR_POSIX_CMD_NOT_EXECUTABLE
 *         (printed, @c SCAN_MODE_FILE acquisition) or @c ERR_LIBC
 *         (printed; module allocation failure) on module-produced
 *         failure. Module-external errors (options, params, history,
 *         sig) bubble through the qualification unlisted.
 */
t_error	update_input(t_scanner *scanner, t_token *out, bool ps2);

/* ************************************************************************* */
/*                                 ERROR                                     */
/* ************************************************************************* */

/**
 * @ingroup scanner
 * @brief Applies the scanner exit contract to @p err (see the rule sheet
 *        and module-external producer inventory in scanner_error.c):
 *        @c ERR_NO_DELIM is absorbed to @c ERR_NO (benign missing
 *        delimiter, POSIX 2.7.4, diagnostic already printed at
 *        production); @c ERR_NO, @c ERR_VEOF and @c ERR_LIBC pass
 *        verbatim, unprinted; everything else passes with its type kept,
 *        printed at this frontier when still unprinted (guarded no-op on
 *        errors printed at production).
 *
 * @param err Error reaching a scanner exit point.
 * @return The requalified error (see contract above).
 */
t_error	scanner_requalify_error(t_error err);

#endif
