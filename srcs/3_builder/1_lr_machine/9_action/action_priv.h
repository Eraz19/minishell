#ifndef ACTION_PRIV_H
# define ACTION_PRIV_H

# include "builder.h"

/* ************************************************************************* */
/*                                   GROUPS                                  */
/* ************************************************************************* */

/** @defgroup action_priv Action module internal API
 *  @brief Internal helpers used to allocate and initialize the ACTION table.
 *  @warning These functions must only be called by the @ref action module
 *           itself.
 *
 *  This private API is intended for the implementation of the @ref action
 *  module.
 */

/* ************************************************************************* */
/*                                  PRIVATE                                  */
/* ************************************************************************* */

/**
 * @ingroup action_priv
 * @brief Allocates and initializes the default ACTION table of an LR machine.
 *
 * This function allocates a two-dimensional ACTION table whose row count
 * equals `@p machine->lr_states.len` and whose column count equals
 * `@ref SYM_TERMINAL_MAX + 1`. Every entry is initialized to an
 * @ref ACTION_ERROR action whose payload is @ref ACTION_PAYLOAD_EMPTY.
 *
 * @note On success, ownership of the allocated table remains with @p machine
 *       and the table must later be released with @ref action_free.
 * @note On allocation failure, this function frees any partially allocated
 *       rows and leaves `@p machine->actions` set to NULL.
 *
 * @warning @p machine must NOT be NULL.
 * @warning `@p machine->lr_states` must already have been built.
 * @warning This function does not free a previously allocated ACTION table
 *          before overwriting `@p machine->actions`.
 * @warning This function performs no parameter validation.
 *
 * @param machine LR machine whose ACTION table must be allocated and
 *                initialized (borrowed, must NOT be NULL).
 * @return ERR_NO / ERR_LIBC
 */
bool	action_build_default_table(t_lr_machine *machine);

# endif
