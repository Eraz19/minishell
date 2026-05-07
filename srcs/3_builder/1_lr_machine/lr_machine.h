#ifndef LR_MACHINE_H
# define LR_MACHINE_H

# include "builder.h"

/* ************************************************************************* */
/*                                   GROUPS                                  */
/* ************************************************************************* */

/** @defgroup lr_machine_pub LR machine module public API
 *  @brief Public functions used to initialize, build and release an
 *         @ref t_lr_machine.
 *  @warning This module must only be called by its parent module
 *           @ref builder and its sibling modules @ref parser. All other
 *           modules must call @ref builder instead of calling this module
 *           directly.
 *
 *  This module orchestrates the construction and cleanup of the grammar,
 *  nullable-symbol, FIRST, LR-state, transition, GOTO and ACTION tables.
 */

/* ************************************************************************* */
/*                              LR_MACHINE (PUB)                             */
/* ************************************************************************* */

/**
 * @ingroup lr_machine_pub
 * @brief Builds all derived tables of an LR machine.
 *
 * This function builds the grammar rule table with @ref rules_build, then
 * computes nullable-symbol information with
 * @ref symbols_build_nullables_table, FIRST sets with @ref first_build_table,
 * LR states and transitions with @ref transition_build_table, the GOTO table
 * with @ref goto_build_table, and finally the ACTION table with
 * @ref action_build_table.
 *
 * @note This function mutates multiple fields of @p machine in place,
 *       including `rules`, `nullable_symbols`, `first`, `lr_states`,
 *       `transitions`, `gotos`, and `actions`.
 * @note This function is intended to be called after @ref lr_machine_init.
 *
 * @warning @p machine must NOT be NULL.
 * @warning @p machine must previously have been initialized with
 *          @ref lr_machine_init.
 * @warning This function does not clear previously built tables before
 *          rebuilding them.
 * @warning On failure, data successfully built before the error remain stored
 *          in @p machine. This function does not roll back partial progress.
 * @warning The current implementation temporarily changes the numeric locale
 *          and restores it only on successful completion.
 * @warning This function performs no parameter validation.
 *
 * @param machine LR machine to build in place (borrowed, must NOT be NULL).
 * @return true if the whole LR machine was built successfully, false if one of
 *         the table-building steps failed.
 */
bool	lr_machine_build(t_lr_machine *machine);

/**
 * @ingroup lr_machine_pub
 * @brief Releases the dynamic resources owned by an LR machine.
 *
 * This function releases the transition table with @ref transition_free, the
 * ACTION table with @ref action_free, the GOTO table with @ref goto_free, and
 * the LR-state registry with @ref lr_state_table_free.
 *
 * @note This function does not free the @ref t_lr_machine object itself.
 * @note The rule table, nullable-symbol table, and FIRST table are stored
 *       inline inside @ref t_lr_machine and therefore do not require explicit
 *       deallocation.
 *
 * @warning @p machine must NOT be NULL.
 * @warning @p machine must previously have been initialized with
 *          @ref lr_machine_init.
 * @warning The row count passed internally to @ref action_free and
 *          @ref goto_free is taken from `@p machine->lr_states.len`.
 *          Corrupting that registry before cleanup would make this call
 *          unsafe.
 * @warning This function performs no parameter validation.
 *
 * @param machine LR machine to release in place (borrowed, must NOT be NULL).
 */
void	lr_machine_free(t_lr_machine *machine);

/**
 * @ingroup lr_machine_pub
 * @brief Initializes an LR machine to an empty state.
 *
 * This function initializes the embedded rule table with @ref rules_init, the
 * LR-state registry with @ref lr_state_table_init, the transition table with
 * @ref transition_init, the ACTION table pointer with @ref action_init, and
 * the GOTO table pointer with @ref goto_init.
 *
 * @note After this call, @p machine is ready to be passed to
 *       @ref lr_machine_build.
 * @note This function does not build derived parsing tables; it only prepares
 *       their storage and default empty state.
 *
 * @warning @p machine must NOT be NULL.
 * @warning @p machine must not already own allocated resources. Release them
 *          first with @ref lr_machine_free before reinitializing it.
 * @warning This function performs no parameter validation.
 *
 * @param machine LR machine to initialize in place (borrowed, must NOT be
 *                NULL).
 */
void	lr_machine_init(t_lr_machine *machine);

#endif
