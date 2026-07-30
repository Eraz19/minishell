#ifndef LOADER__H
# define LOADER__H

# include "word_.h"
# include "error.h"
# include "expander_.h"

/** @defgroup expander_loader Expander loader
 *  @brief Turns a raw token value and its lexer-recorded context stack
 *         into a @ref t_word of annotated characters.
 *
 *  The loader walks the raw text once, entering each recorded span when
 *  it reaches its start offset: quoting spans set the quoting metadata,
 *  substitution spans set the construct metadata and its span length,
 *  and a backslash before a whitelisted character marks the next item
 *  escaped.
 */

/**
 * @ingroup expander_loader
 * @struct s_loader
 * @brief State of one load run.
 *
 * @var s_loader::i Current read offset in @c word.
 * @var s_loader::err Last error recorded by the run.
 * @var s_loader::word Raw text being loaded, a @ref t_string duplicated
 *                     from the run's input; owned by the loader.
 * @var s_loader::stack Contexts not yet entered, duplicated from the
 *                      input stack and consumed bottom-first as their
 *                      start offset is reached; managed by the context
 *                      module.
 * @var s_loader::quoting Quoting context enclosing the current character
 *                        (@c CONTEXT_NONE when unquoted).
 * @var s_loader::local_quoting Quoting seen from inside the innermost
 *                              substitution: reset to @c CONTEXT_NONE on
 *                              substitution entry, restored on exit.
 * @var s_loader::loaded_word Annotated word under construction, the
 *                            output of the run; managed by the word
 *                            submodule.
 * @var s_loader::loading_stack Substitution contexts open at the read
 *                              position; managed by the context module.
 * @var s_loader::context_item Innermost open substitution context,
 *                             @c NULL at top level; aliases the top of
 *                             @c loading_stack (borrowed).
 */
typedef struct s_loader
{
	size_t					i;
	t_error					err;
	t_string				word;
	t_context_stack			stack;
	t_context				quoting;
	t_context				local_quoting;
	t_word					loaded_word;
	t_context_stack			loading_stack;
	t_context_stack_item	*context_item;
}	t_loader;

/* ************************************************************************* */
/*                                LIFE_CYCLE                                 */
/* ************************************************************************* */

/**
 * @ingroup expander_loader
 * @brief Zeroes @p loader and initializes its two stacks and its loaded
 *        word; @c word stays zeroed until @ref loader_load fills it.
 *
 * @param loader Loader state initialized by the function (borrowed).
 */
void	loader_init(t_loader *loader);

/**
 * @ingroup expander_loader
 * @brief Copies the run's input into @p loader: duplicates
 *        @c args->value into the raw text and @c args->contexts (when
 *        not @c NULL) into the pending stack.
 *
 * @param loader Already initialized loader state (borrowed).
 * @param args Input of the run, left untouched (borrowed, read-only).
 * @return @c ERR_INDEX_OUT_OF_BOUND if an item lookup fails while
 *         duplicating the stack, @c ERR_LIBC on allocation failure,
 *         @c ERR_NO on success.
 */
t_error	loader_load(t_loader *loader, t_expander_args *args);

/**
 * @ingroup expander_loader
 * @brief Frees the raw text, both stacks and the loaded word of
 *        @p loader, then zeroes it.
 *
 * @param loader Already initialized loader state (borrowed).
 */
void	loader_free(t_loader *loader);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup expander_loader
 * @brief Tells whether the current character is a backslash escaping the
 *        next one: the next character must not be the terminating NUL
 *        and must be in the escape whitelist of the current quoting
 *        context (@ref is_in_quoting_whitelist when quoted,
 *        @ref is_in_substitution_whitelist otherwise).
 *
 * @param loader Loader state (borrowed, read-only).
 */
bool	is_char_escaped(t_loader *loader);

/**
 * @ingroup expander_loader
 * @brief Appends the current character to the loaded word as an item
 *        stamped with the current metadata (offset, quoting, local
 *        quoting, innermost construct and its span length), then
 *        advances the read offset.
 *
 * @note Every item of a substitution span carries the construct kind and
 *       its full @c context_len, not only the opening character.
 * @param loader Loaded loader state (borrowed).
 * @param escaped Recorded as the item's escape flag.
 * @return @c ERR_LIBC if the push fails, @c ERR_NO on success.
 */
t_error	loader_consume(t_loader *loader, bool escaped);

/**
 * @ingroup expander_loader
 * @brief Loads one construct starting at the read offset: a whole
 *        substitution span, a whole quoting span, an escaped pair (the
 *        backslash, then the character it escapes marked escaped), or a
 *        single plain character; call in a loop until the raw text is
 *        exhausted.
 *
 * @note Resets @c quoting and @c local_quoting to @c CONTEXT_NONE first:
 *       the read offset is assumed to be at top level.
 * @param loader Loaded loader state (borrowed).
 * @return @c ERR_EMPTY_STACK or @c ERR_INDEX_OUT_OF_BOUND on a context
 *         stack inconsistency, @c ERR_LIBC on allocation or push
 *         failure, @c ERR_NO on success.
 */
t_error	loader_prepare_word(t_loader *loader);

/**
 * @ingroup expander_loader
 * @brief Enters the quoting span at the bottom of the pending stack and
 *        loads its whole body, tagging every item (nested substitutions
 *        included) with the quoting context; the previous quoting is
 *        restored on exit.
 *
 * @warning Call only when @ref is_quoting_start is true: the bottom
 *          pending context is popped and freed unconditionally.
 * @param loader Loaded loader state (borrowed).
 * @return @c ERR_EMPTY_STACK or @c ERR_INDEX_OUT_OF_BOUND on a context
 *         stack inconsistency, @c ERR_LIBC on allocation or push
 *         failure, @c ERR_NO on success.
 */
t_error	loader_quoted(t_loader *loader);

#endif
