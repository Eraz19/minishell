#ifndef FIRST_H
# define FIRST_H

# include "builder.h"

/* ************************************************************************* */
/*                                   TYPES                                   */
/* ************************************************************************* */

/**
 * @struct s_first_param
 * @brief Parameters and output storage used by @ref first.
 *
 * @var s_first_param::symbols Sequence whose FIRST set must be computed
 *      (borrowed, can be NULL only when @ref s_first_param::count is zero).
 * @var s_first_param::count Number of symbols stored in
 *      @ref s_first_param::symbols.
 * @var s_first_param::lookahead Terminal symbol appended conceptually after
 *      the sequence when @ref s_first_param::has_lookahead is true.
 * @var s_first_param::has_lookahead Whether @ref s_first_param::lookahead must
 *      be added when the whole sequence is nullable.
 * @var s_first_param::result Output FIRST-set buffer indexed by terminal
 *      symbol. This array is overwritten by @ref first.
 */
typedef struct s_first_param
{
	t_symbol	*symbols;
	size_t		count;
	t_symbol	lookahead;
	bool		has_lookahead;
	bool		result[SYM_TERMINAL_MAX + 1];
}	t_first_param;

/* ************************************************************************* */
/*                                   GROUPS                                  */
/* ************************************************************************* */

/** @defgroup first_pub First module public API
 *  @brief Public functions used to build and query FIRST sets.
 *  @warning This module must only be called by its parent module
 *           @ref lr_machine and its sibling modules @ref hooks, @ref rules,
 *           @ref symbols, @ref rule_state, @ref lr_state, @ref transition,
 *           @ref goto, @ref action. All other modules must call @ref lr_machine
 *           instead of calling this module directly.
 *
 *  This module builds the FIRST table stored in @ref t_lr_machine and computes
 *  FIRST sets for symbol sequences.
 */

/* ************************************************************************* */
/*                                 FIRST (PUB)                               */
/* ************************************************************************* */

/**
 * @ingroup first_pub
 * @brief Computes the FIRST set of a symbol sequence.
 *
 * This function clears @p param->result, then computes the FIRST set of the
 * sequence described by @p param->symbols and @p param->count using the
 * precomputed FIRST and nullable-symbol tables stored in @p machine.
 *
 * If the first non-nullable symbol in the sequence is terminal, only that
 * terminal is added to the result. If it is non-terminal, its FIRST set is
 * merged into the result. This continues until a non-nullable symbol is
 * encountered or the sequence is exhausted. When the whole sequence is
 * nullable and @p param->has_lookahead is true, @p param->lookahead is also
 * added to the result.
 *
 * @note @p param->result is always reset before the computation starts.
 * @note When @p param->count is zero, @p param->symbols is not accessed and
 *       can be NULL.
 * @note This function stores only terminal membership inside
 *       @p param->result. Nullability itself must be queried separately
 *       through @ref symbol_is_nullable.
 *
 * @warning @p machine and @p param must NOT be NULL.
 * @warning @ref first_build_table and @ref symbols_build_nullables_table must
 *          already have been called successfully on @p machine before calling
 *          this function.
 * @warning Every symbol stored in @p param->symbols must be a valid
 *          @ref t_symbol value in the range `[0, @ref SYM_COUNT)`.
 * @warning When @p param->has_lookahead is true, @p param->lookahead must be
 *          a terminal symbol in the range `[0, @ref SYM_TERMINAL_MAX]`.
 * @warning This function performs no parameter validation.
 *
 * @param machine LR machine providing the precomputed FIRST and nullable
 *                tables (borrowed, must NOT be NULL).
 * @param param Input parameters and output buffer used for the computation
 *              (borrowed, must NOT be NULL).
 */
void	first(t_lr_machine *machine, t_first_param *param);

/**
 * @ingroup first_pub
 * @brief Builds the FIRST table stored in an LR machine.
 *
 * This function resets the whole `first` table stored in @p machine, marks
 * each terminal symbol as belonging to its own FIRST set, then computes a
 * fixed point over the grammar rules stored in @p machine->rules.
 *
 * For each rule, the right-hand side is scanned from left to right. Terminal
 * symbols are added directly. Non-terminal FIRST sets are merged into the
 * left-hand side FIRST set, and the scan continues only while the current
 * symbol is nullable according to @ref symbol_is_nullable.
 *
 * @note This function updates only the `first` table stored in @p machine.
 * @note FIRST sets for terminal symbols are initialized so that each terminal
 *       contains itself.
 * @note This function stores only terminal membership. Nullable-symbol
 *       information remains stored separately in `nullable_symbols`.
 *
 * @warning @p machine must NOT be NULL.
 * @warning @p machine->rules must already contain a valid grammar, typically
 *          populated by @ref rules_build.
 * @warning The nullable-symbol table must already have been built with
 *          @ref symbols_build_nullables_table before calling this function.
 * @warning This function performs no parameter validation.
 *
 * @param machine LR machine whose FIRST table must be rebuilt (borrowed, must
 *                NOT be NULL).
 */
void	first_build_table(t_lr_machine *machine);

#endif
