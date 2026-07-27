#ifndef VARIABLES_PRIV_H
# define VARIABLES_PRIV_H

# include "libft.h"
# include <stddef.h>

/* ************************************************************************* */
/*                                   TYPES                                   */
/* ************************************************************************* */

/**
 * @struct s_var
 * @brief Internal representation of a shell variable.
 *
 * @var s_var::value Variable value, empty when unset (owned).
 * @var s_var::export Export flag.
 * @var s_var::readonly Read-only flag.
 */
typedef struct s_var
{
	/** @brief Owned variable value, empty when unset. */
	t_string	value;
	/** @brief Export flag. */
	bool		export;
	/** @brief Read-only flag. */
	bool		readonly;
}	t_var;

/* ************************************************************************* */
/*                                LIFE CYCLE                                 */
/* ************************************************************************* */

/**
 * @brief Release a single variable entry.
 *
 * Suitable for vector_free() callbacks.
 *
 * @param var Variable entry to clear (borrowed).
 */
void	var_free_one(void *var);

#endif
