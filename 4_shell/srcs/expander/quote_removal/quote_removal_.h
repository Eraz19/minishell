#ifndef QUOTE_REMOVAL__H
# define QUOTE_REMOVAL__H

# include "error.h"
# include "expander_.h"

/** @defgroup expander_quote_removal Expander quote removal
 *  @brief POSIX 2.6.7 quote removal, the final expansion stage: rebuilds
 *         every field without its quoting marks.
 *
 *  Each word is consumed item by item: expansion results are forwarded
 *  untouched, unquoted escapes are resolved, and a quoted item whose
 *  character is the actual opening mark of its context enters the
 *  matching quoting-context scan (see the context submodule).
 *
 *  @note Every function also records its result in @c expander->err
 *        before returning it.
 */

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup expander_quote_removal
 * @brief Applies quote removal to every field of @c expander->fields and
 *        replaces the container with the rebuilt fields.
 *
 * @note On failure the fields produced so far are freed and the
 *       remaining input stays in @c expander->fields for
 *       @ref expander_free.
 * @param expander Loaded expander state (borrowed).
 * @return @c ERR_EMPTY_STACK if a word ends inside a quoting context or
 *         on a dangling escape, @c ERR_LIBC if a pop or push fails,
 *         @c ERR_NO on success.
 */
t_error	quote_removal(t_expander *expander);

/**
 * @ingroup expander_quote_removal
 * @brief Consumes the next item of @c expander->word into
 *        @c expander->word_exp: forwards expansion results and plain
 *        unquoted characters, resolves an unquoted backslash (the
 *        backslash is dropped, the escaped item forwarded), and hands
 *        quoted items to their quoting-context handler, dropping the
 *        opening mark when the item is one.
 *
 * @warning An unquoted backslash that ends the word is dropped: POSIX
 *          2.2.1 leaves a trailing unescaped backslash unspecified and
 *          shells diverge (bash drops it, dash keeps it literal) —
 *          DECIDED 2026-07-10: bash-compatible drop. The heredoc
 *          handler keeps it (POSIX 2.7.4 escape set differs there).
 * @note Items quoted @c CONTEXT_HEREDOC have no opening mark: each one
 *       is handled individually by @ref context_heredoc.
 * @param expander Expander state whose @c word head is consumed
 *                 (borrowed).
 * @return @c ERR_EMPTY_STACK if @c expander->word is empty or ends
 *         inside a quoting context, @c ERR_LIBC if a pop or push fails,
 *         @c ERR_NO on success.
 */
t_error	quote_remove_char(t_expander *expander);

#endif
