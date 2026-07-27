#ifndef POSITIONALS_H
# define POSITIONALS_H

# include "libft.h"
# include "error.h"

/**
 * @brief Positional arguments frame stored as a vector of @ref t_string .
 */
typedef t_vector	t_positionals;

/**
 * @brief Stack of positional frames stored as a vector of @ref t_positionals .
 */
typedef t_vector	t_positionals_stack;

/* ************************************************************************* */
/*                                LIFE CYCLE                                 */
/* ************************************************************************* */

/**
 * @brief Initialize an empty positional stack.
 *
 * @param stack Destination stack (borrowed).
 */
void	positionals_init_stack(t_positionals_stack *stack);

/**
 * @brief Load the initial positional frame from @p argv .
 *
 * The pushed frame owns copies of the argument strings.
 *
 * @param stack Destination stack (borrowed).
 * @param argc Argument count.
 * @param argv Argument array (borrowed, read-only).
 * @param start_index Index of the first positional argument.
 * @return @c ERR_NO or @c ERR_LIBC.
 */
t_error	positionals_load_stack(
			t_positionals_stack *stack,
			int argc,
			char **argv,
			size_t start_index);

// TODO: doc
void	positionals_clear_stack(t_positionals_stack *stack);

/**
 * @brief Release every positional frame owned by the stack.
 *
 * @param stack Stack to clear (borrowed).
 */
void	positionals_free_stack(t_positionals_stack *stack);

/* ************************************************************************* */
/*                                   OPS                                     */
/* ************************************************************************* */

/**
 * @brief Borrow the current positional frame as a read-only vector view.
 *
 * @param stack Source stack (borrowed, read-only).
 * @param dst Destination pointer to the borrowed read-only frame view.
 * @return @c ERR_NO or @c ERR_VAR_NOT_FOUND.
 */
t_error	positionals_get(
			const t_positionals_stack *stack,
			const t_positionals **dst);

/**
 * @brief Read a single positional parameter into a fresh string.
 *
 * The name @c # returns the current positional count.
 * The caller owns @p dst on success and must release it with
 * @ref string_free().
 *
 * @param stack Source stack (borrowed, read-only).
 * @param name Requested positional name (borrowed, read-only).
 * @param dst Initialized destination string (borrowed).
 * @return @c ERR_NO, @c ERR_VAR_NOT_FOUND, @c ERR_VAR_INVALID_NAME or
 *         @c ERR_LIBC.
 */
t_error	positionals_get_one(
			const t_positionals_stack *stack,
			const t_string *name,
			t_string *dst);

/**
 * @brief Const-name variant of @ref positionals_get_one().
 *
 * The name @c # returns the current positional count.
 * The caller owns @p dst on success and must release it with
 * @ref string_free().
 *
 * @param stack Source stack (borrowed, read-only).
 * @param name Requested positional name (borrowed, read-only).
 * @param dst Destination string initialized by the function (borrowed).
 * @return @c ERR_NO, @c ERR_VAR_NOT_FOUND, @c ERR_VAR_INVALID_NAME or
 *         @c ERR_LIBC.
 */
t_error	positionals_get_one_cst(
			const t_positionals_stack *stack,
			const char *name,
			t_string *dst);

/**
 * @brief Pop the current positional frame from the @p stack .
 *
 * @param stack Stack to modify (borrowed).
 * @return @c ERR_NO or @c ERR_LIBC.
 */
t_error	positionals_pop(t_positionals_stack *stack);

/**
 * @brief Push a new positional frame on top of the @p stack .
 *
 * Ownership transfers to the stack on success.
 *
 * @param stack Destination stack (borrowed).
 * @param positionals Frame to push (ownership taken by @p stack).
 * @return @c ERR_NO or @c ERR_LIBC.
 */
t_error	positionals_push(
			t_positionals_stack *stack,
			t_positionals *positionals);

/**
 * @brief Replace the current positional frame.
 *
 * Ownership transfers to the stack on success.
 *
 * @warning @p positionals must NOT reference an existing stack frame.
 *
 * @param stack Destination stack (borrowed).
 * @param positionals Replacement frame (ownership taken by stack).
 * @return @c ERR_NO, @c ERR_VAR_NOT_FOUND or @c ERR_LIBC.
 */
t_error	positionals_replace(
			t_positionals_stack *stack,
			t_positionals *positionals);

/**
 * @brief Remove the first @p n positional arguments from the current frame.
 *
 * @param stack Stack to modify (borrowed).
 * @param n Number of leading arguments to remove.
 * @return @c ERR_NO, @c ERR_VAR_NOT_FOUND or @c ERR_SHIFT_INVALID_VALUE.
 */
t_error	positionals_shift(t_positionals_stack *stack, size_t n);

/* ************************************************************************* */
/*                                   DEBUG                                   */
/* ************************************************************************* */

/**
 * @brief Dump positional frames to stderr.
 */
void	positionals_dump(void);

#endif
