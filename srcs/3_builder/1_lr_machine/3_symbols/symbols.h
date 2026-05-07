#ifndef SYMBOLS_H
# define SYMBOLS_H

# include "builder.h"

/* ************************************************************************* */
/*                                   GROUPS                                  */
/* ************************************************************************* */

/** @defgroup symbols_pub Symbols module public API
 *  @brief Public helpers used to classify grammar symbols and compute
 *         symbol nullability information.
 *  @warning This module must only be called by its parent module 
 *           @ref lr_machine and its sibling modules @ref hooks, @ref rules,
 *           @ref first, @ref rule_state, @ref lr_state, @ref transition,
 *           @ref goto, @ref action. All other modules must call 
 *           @ref lr_machine instead of calling this module directly.
 *
 *  This module provides predicates on @ref t_symbol values and builds the
 *  nullable-symbol table stored in @ref t_lr_machine.
 */

/* ************************************************************************* */
/*                                SYMBOLS (PUB)                              */
/* ************************************************************************* */

/**
 * @ingroup symbols_pub
 * @brief Checks whether a symbol belongs to the non-terminal range.
 *
 * This function classifies @p symbol by testing whether it lies between
 * @ref SYM_NON_TERMINAL_MIN and @ref SYM_NON_TERMINAL_MAX, inclusive.
 *
 * @note This function does not access any external state.
 *
 * @warning Caller should pass a valid @ref t_symbol value.
 *
 * @param symbol Symbol to classify.
 * @return true if @p symbol is a non-terminal symbol, false otherwise.
 */
bool	symbol_is_non_terminal(t_symbol symbol);

/**
 * @ingroup symbols_pub
 * @brief Reports whether a symbol is currently marked as nullable.
 *
 * This function reads the nullable-symbol table stored in @p machine and
 * returns the value associated with @p symbol.
 *
 * @note This function does not validate whether the nullable table was
 *       previously computed by @ref symbols_build_nullables_table.
 *
 * @warning @p machine must NOT be NULL.
 * @warning @p symbol must be a valid index in the range `[0, @ref SYM_COUNT)`.
 * @warning This function performs no parameter validation.
 *
 * @param machine LR machine holding the nullable-symbol table (borrowed, must
 *                NOT be NULL).
 * @param symbol Symbol whose nullability must be queried.
 * @return true if @p symbol is marked nullable in @p machine, false otherwise.
 */
bool	symbol_is_nullable(t_lr_machine *machine, t_symbol symbol);

/**
 * @ingroup symbols_pub
 * @brief Checks whether a symbol belongs to the terminal range.
 *
 * This function classifies @p symbol by testing whether it is less than or
 * equal to @ref SYM_TERMINAL_MAX.
 *
 * @note This function does not access any external state.
 *
 * @warning Caller should pass a valid @ref t_symbol value.
 *
 * @param symbol Symbol to classify.
 * @return true if @p symbol is a terminal symbol, false otherwise.
 */
bool	symbol_is_terminal(t_symbol symbol);

/**
 * @ingroup symbols_pub
 * @brief Reports whether all symbols in a sequence are nullable.
 *
 * This function returns true only if every symbol in the sequence referenced
 * by @p symbols is reported as nullable by @ref symbol_is_nullable.
 *
 * @note An empty sequence is considered nullable. Therefore, this function
 *       returns true when @p count is zero.
 * @note When @p count is zero, @p symbols is not accessed and can be NULL.
 *
 * @warning @p machine must NOT be NULL.
 * @warning When @p count is greater than zero, @p symbols must NOT be NULL.
 * @warning Each symbol in the sequence must be a valid index in the range
 *          `[0, @ref SYM_COUNT)`.
 * @warning This function performs no parameter validation.
 *
 * @param machine LR machine holding the nullable-symbol table (borrowed, must
 *                NOT be NULL).
 * @param symbols Sequence of symbols to test (borrowed, can be NULL only when
 *                @p count is zero).
 * @param count Number of symbols in @p symbols.
 * @return true if all symbols in the sequence are nullable, false otherwise.
 */
bool	symbols_are_nullable(t_lr_machine *machine, t_symbol *symbols, size_t count);

/**
 * @ingroup symbols_pub
 * @brief Builds the nullable-symbol table of an LR machine.
 *
 * This function resets every entry of @p machine->nullable_symbols, then
 * computes a fixed point over the grammar stored in @p machine->rules.
 * A non-terminal symbol is marked nullable when at least one rule with that
 * symbol as left-hand side has an empty right-hand side or a right-hand side
 * composed entirely of nullable symbols.
 *
 * @note This function updates only the `nullable_symbols` table stored in
 *       @p machine.
 * @note The computation iterates until no new nullable symbol is discovered.
 *
 * @warning @p machine must NOT be NULL.
 * @warning @p machine->rules must already contain a valid grammar, typically
 *          populated by @ref rules_build.
 * @warning This function performs no parameter validation.
 *
 * @param machine LR machine whose nullable-symbol table must be rebuilt
 *                (borrowed, must NOT be NULL).
 */
void	symbols_build_nullables_table(t_lr_machine *machine);

#endif
