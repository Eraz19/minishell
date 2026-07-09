#ifndef INPUT_MODE_H
# define INPUT_MODE_H

# include "error.h"

/** @defgroup input_mode Input mode API
 *  @brief Identifies where the shell reads its commands from.
 *
 *  The input mode is derived once at startup from the invocation options
 *  (@c -s, @c -i, @c -c) and drives how the scanner sources its input and
 *  whether interactive behaviour (prompting) is enabled.
 */

/**
 * @ingroup input_mode
 * @enum e_input_mode
 * @brief Source the shell reads its commands from.
 */
typedef enum e_input_mode
{
	INPUT_MODE_NONE,
	INPUT_MODE_FILE,
	INPUT_MODE_STRING,
	INPUT_MODE_STDIN_TTY,
	INPUT_MODE_STDIN_PIPE
}	t_input_mode;

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup input_mode
 * @brief Derives the input mode from the shell invocation options, by
 *        decreasing precedence: @c -s with @c -i gives
 *        @c INPUT_MODE_STDIN_TTY, @c -s alone @c INPUT_MODE_STDIN_PIPE,
 *        @c -c @c INPUT_MODE_STRING, otherwise @c INPUT_MODE_FILE.
 *
 * @note The function never produces @c INPUT_MODE_NONE.
 * @param mode Set to the computed mode; left untouched on error (borrowed).
 * @return @c ERR_SHELL_NOT_FOUND if the shell parameters are unavailable,
 *         @c ERR_NO on success.
 */
t_error	input_mode_set(t_input_mode *mode);

#endif
