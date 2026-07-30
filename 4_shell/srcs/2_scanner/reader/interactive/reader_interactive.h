#ifndef READER_INTERACTIVE_H
# define READER_INTERACTIVE_H

# include "error.h"
# include "libft.h"

/* ************************************************************************* */
/*                                  TYPES                                    */
/* ************************************************************************* */

/**
 * @ingroup scanner_reader
 * @brief Retry budgets for EOFs ignored under @c set @c -o @c ignoreeof:
 *        @c PS1 re-prompts up to 10 times, @c PS2 gives up on the first
 *        EOF. Exceeding a positive budget trips the infinite-loop guard;
 *        both cases surface as @c ERR_VEOF.
 */
# define MAX_RETRY_PS1	10
# define MAX_RETRY_PS2	0

/**
 * @ingroup scanner_reader
 * @enum s_prompt_mode
 * @brief Selects which prompt variable the interactive read displays.
 *
 * @var s_prompt_mode::PROMPT_PS1
 *      Primary prompt: @c PS1, with @c ! history-number expansion.
 * @var s_prompt_mode::PROMPT_PS2
 *      Continuation prompt: @c PS2.
 */
typedef enum s_prompt_mode
{
	PROMPT_PS1,
	PROMPT_PS2,
}	t_prompt_mode;

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup scanner_reader
 * @brief Builds the @p mode prompt, then reads lines through readline
 *        until one is not empty, appending the trailing newline readline
 *        stripped.
 *
 * @note @c PROMPT_PS2 returns the line verbatim; @c PROMPT_PS1 silently
 *       discards empty lines (a lone newline) and reads again — a
 *       documented choice, an empty top-level line being a valid empty
 *       program with no observable effect.
 *
 * @param out Receives the line; initialized by the function, freed by the
 *            function on failure (borrowed).
 * @param mode Prompt to display (@ref t_prompt_mode).
 * @param max_retry Ignored-EOF budget (see @c MAX_RETRY_PS1 /
 *                  @c MAX_RETRY_PS2).
 * @return @c ERR_NO on success; @c ERR_VEOF (end of input or budget
 *         exhausted) or @c ERR_LIBC (module allocation / libc failure) on
 *         module-produced failure. Module-external errors (options,
 *         params, sig, EOF newline echo) bubble through unlisted.
 */
t_error	read_interactive(t_string *out, t_prompt_mode mode, size_t max_retry);

#endif
