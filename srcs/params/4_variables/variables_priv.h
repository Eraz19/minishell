#ifndef VARIABLES_PRIV_H
# define VARIABLES_PRIV_H

# include "variables.h"
# include <stddef.h>

/* ************************************************************************* */
/*                                   TYPES                                   */
/* ************************************************************************* */

/**
 * @struct s_var
 * @brief Internal representation of a shell variable.
 *
 * @var s_var::name Variable name (owned).
 * @var s_var::value Variable value, empty when unset (owned).
 * @var s_var::export Export flag.
 * @var s_var::readonly Read-only flag.
 */
typedef struct s_var
{
	/** @brief Owned variable name. */
	t_string	name;
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

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @brief Search a variable by name in a variable list.
 *
 * @param variables Variable list to inspect (borrowed, read-only).
 * @param name Variable name (borrowed, read-only).
 * @param res Receives the index when the function returns true (borrowed).
 * @return True when a matching variable is found.
 */
bool	var_find(
			const t_var_list *variables,
			const t_string *name,
			size_t *res);

/**
 * @brief Const-name variant of @ref var_find().
 *
 * @param variables Variable list to inspect (borrowed, read-only).
 * @param name Variable name (borrowed, read-only).
 * @param res Receives the found index (borrowed).
 * @return True when a matching variable is found.
 */
bool	var_find_from_const(
			const t_var_list *variables,
			const char *name,
			size_t *res);

/* ************************************************************************* */
/*                                   DEBUG                                   */
/* ************************************************************************* */

/**
 * @brief Dump a single variable entry to stderr.
 *
 * @param var Variable entry to print (borrowed, read-only).
 */
void	var_dump_one(const t_var *var);

#endif
