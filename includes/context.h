#ifndef CONTEXT_H
# define CONTEXT_H

# include "error.h"
# include "libft.h"

/** @defgroup context Context API
 *  @brief Quoting and expansion contexts recognised while scanning input.
 *
 *  As the scanner walks the input it tracks the nested constructs currently
 *  open on a context stack (e.g. inside "...", $(...) or $((...))). Each
 *  context type exposes up to three predicates following a shared naming
 *  convention:
 *  - is_context_<x>_start(str): does @p str begin an <x> construct?
 *  - is_context_<x>_ending(c, arg): is @p c the closing delimiter of <x>?
 *  - is_in_context_<x>_whitelist(c): inside <x>, does @p c keep a special
 *    meaning (and therefore still need processing)?
 *
 *  Ending predicates share the signature bool(char, void *) so they can be
 *  held in a single function pointer; the void * carries optional state and
 *  is unused by every context except arithmetic (its nesting depth).
 */

/**
 * @ingroup context
 * @enum e_context
 * @brief A quoting or expansion construct the scanner can be inside of.
 */
typedef enum e_context
{
	CONTEXT_NONE,			/**< Top level, outside any quoting or expansion. */
	CONTEXT_SQUOTE,			/**< Single quotes: '...'. */
	CONTEXT_DQUOTE,			/**< Double quotes: "...". */
	CONTEXT_DOLLAR_SQUOTE,	/**< ANSI-C quoting: $'...'. */
	CONTEXT_BACKTICK,		/**< Backquote command substitution: `...`. */
	CONTEXT_CMD_SUB,		/**< Command substitution: $(...). */
	CONTEXT_ARITH,			/**< Arithmetic expansion: $((...)). */
	CONTEXT_PARAM,			/**< Parameter expansion: ${...}. */
}	t_context;

/**
 * @ingroup context
 * @struct s_context_parser_stack_item
 * @brief One context together with the span it covers in a token's value
 *        buffer.
 *
 * @var s_context_parser_stack_item::end Index one past the construct's last character
 *                                in the token value (filled in when the context
 *                                closes).
 * @var s_context_parser_stack_item::start Index of the construct's first character in
 *                                  the token value (filled in when the context
 *                                  opens).
 * @var s_context_parser_stack_item::context Which construct it is.
 */
typedef struct s_context_parser_stack_item
{
	size_t		end;
	size_t		start;
	t_context	context;
}	t_context_parser_stack_item;

/**
 * @ingroup context
 * @brief Stack of context items (a vector of t_context_parser_stack_item *).
 *
 * Used in two roles: the lexer's live nesting stack (innermost context on top,
 * borrowing its items) and a token's recorded contexts (owning its items). See
 * context_stack_free() for the matching ownership rule.
 */
typedef t_vector	t_context_stack;

/**
 * @ingroup context
 * @brief Initialises an empty context stack.
 *
 * @param stack Pointer to the stack to initialise (borrowed).
 */
void	context_stack_init(t_context_stack *stack);

/**
 * @ingroup context
 * @brief Frees an owning stack: every item pointer it still holds, then its
 *        backing array.
 *
 * Use this for a stack that OWNS its items (a token's recorded contexts). For a
 * stack that only borrows item pointers owned elsewhere (the lexer's live
 * nesting stack), free the backing array alone with vector_free(stack, NULL) so
 * the borrowed items are left intact.
 *
 * @param stack Pointer to the stack to free (borrowed).
 */
void	context_stack_free(t_context_stack *stack);

/**
 * @ingroup context
 * @brief Allocates a context-stack item on the heap.
 *
 * The item's context is set to @p context; its start and end are zeroed and
 * filled in later as the context opens and closes.
 *
 * @param item Out-parameter receiving the newly allocated item (caller owns).
 * @param context Which construct the item represents.
 * @return ERR_NO on success, ERR_LIBC on allocation failure.
 */
t_error	context_parser_stack_item_init(t_context_parser_stack_item **item, t_context context);

/**
 * @ingroup context
 * @brief Deep copies a context stack onto an already-initialised one.
 *
 * Allocates an independent item for every entry of @p src and pushes it onto
 * @p dst in order, so the two stacks share no memory. @p dst must already be
 * initialised (context_stack_init); its existing contents are kept and the
 * copies are appended.
 *
 * @param dst Destination stack, initialised by the caller, appended to here
 *            (borrowed).
 * @param src Source stack to copy (borrowed).
 * @return ERR_NO on success, ERR_LIBC on allocation failure.
 */
t_error	context_stack_dup(t_context_stack *dst, t_context_stack *src);

/**
 * @ingroup context
 * @brief Pushes an item pointer onto the top (back) of the stack.
 *
 * Only the pointer is stored; ownership of the pointed-to item is not
 * transferred.
 *
 * @param stack Pointer to the stack (borrowed).
 * @param item Item pointer to push.
 * @return ERR_NO on success, ERR_LIBC on allocation failure.
 */
t_error	context_stack_push(t_context_stack *stack, t_context_parser_stack_item *item);

/**
 * @ingroup context
 * @brief Removes the item on top (back) of the stack.
 *
 * Regular LIFO pop: yields the most recently pushed (innermost) context.
 *
 * @param stack Pointer to the stack (borrowed).
 * @param item Out-parameter receiving the removed item pointer; may be NULL to
 *             discard it.
 * @return ERR_NO on success, ERR_EMPTY_STACK if the stack is empty.
 */
t_error	context_stack_bpop(t_context_stack *stack, t_context_parser_stack_item **item);

/**
 * @ingroup context
 * @brief Removes the item at the bottom (front) of the stack.
 *
 * FIFO-style removal: yields the oldest (outermost) context.
 *
 * @param stack Pointer to the stack (borrowed).
 * @param item Out-parameter receiving the removed item pointer; may be NULL to
 *             discard it.
 * @return ERR_NO on success, ERR_EMPTY_STACK if the stack is empty.
 */
t_error	context_stack_fpop(t_context_stack *stack, t_context_parser_stack_item **item);

/**
 * @ingroup context
 * @brief Reads the item at @p index without removing it.
 *
 * Index 0 is the bottom (front / outermost) of the stack.
 *
 * @param stack Pointer to the stack (borrowed).
 * @param item Out-parameter receiving the item pointer at @p index.
 * @param index Position to read.
 * @return ERR_NO on success, ERR_EMPTY_STACK if the stack is empty,
 *         ERR_INDEX_OUT_OF_BOUND if @p index is past the last element.
 */
t_error	context_stack_get(t_context_stack *stack, t_context_parser_stack_item **item,
			size_t index);

/**
 * @ingroup context
 * @brief Tests whether a character is a blank (space or tab).
 *
 * @param c Character to test.
 * @return true if @p c is a space or a tab.
 */
bool	is_blank(char c);

/**
 * @ingroup context
 * @brief Whitelist for the top-level context: every character is processed.
 *
 * @param c Character to test (ignored).
 * @return Always true.
 */
bool	is_in_context_none_whitelist(char c);

/**
 * @ingroup context
 * @brief Tests whether the top-level context ends at @p c.
 *
 * @param c Character to test.
 * @param _ Unused; present for the shared ending-predicate signature.
 * @return true at the end of input (NUL).
 */
bool	is_context_none_ending(char c, void *_);

/**
 * @ingroup context
 * @brief Tests whether @p str begins an arithmetic expansion ($((  ).
 *
 * @param str Input cursor to test.
 * @return true if @p str starts with "$((".
 */
bool	is_context_arith_start(char *str);

/**
 * @ingroup context
 * @brief Tests whether an arithmetic expansion ends at @p c.
 *
 * @param c Character to test.
 * @param nesting_depth Pointer to the current parenthesis depth (size_t *);
 *                      the context ends only at the outermost ')'.
 * @return true if @p c is ')' and the nesting depth is zero.
 */
bool	is_context_arith_ending(char c, void *nesting_depth);

/**
 * @ingroup context
 * @brief Tests whether @p str begins a backquote substitution (`).
 *
 * @param str Input cursor to test.
 * @return true if @p str starts with a backquote.
 */
bool	is_context_backtick_start(char *str);

/**
 * @ingroup context
 * @brief Whitelist of characters special inside a backquote substitution.
 *
 * @param c Character to test.
 * @return true for '\\', '$' and '`'.
 */
bool	is_in_context_backtick_whitelist(char c);

/**
 * @ingroup context
 * @brief Tests whether a backquote substitution ends at @p c.
 *
 * @param c Character to test.
 * @param _ Unused; present for the shared ending-predicate signature.
 * @return true if @p c is a backquote.
 */
bool	is_context_backtick_ending(char c, void *_);

/**
 * @ingroup context
 * @brief Extended special set for backquotes nested inside double quotes.
 *
 * @param c Character to test.
 * @return true for '$', '`', '"' and '\\'.
 */
bool	is_in_context_backtick_special_whitelist(char c);

/**
 * @ingroup context
 * @brief Tests whether @p str begins a command substitution ($(  ).
 *
 * @param str Input cursor to test.
 * @return true if @p str starts with "$(".
 */
bool	is_context_cmd_sub_start(char *str);

/**
 * @ingroup context
 * @brief Tests whether @p str begins a parameter expansion (${  ).
 *
 * @param str Input cursor to test.
 * @return true if @p str starts with "${".
 */
bool	is_context_param_start(char *str);

/**
 * @ingroup context
 * @brief Whitelist for a parameter expansion: every character is processed.
 *
 * @param c Character to test (ignored).
 * @return Always true.
 */
bool	is_in_context_param_whitelist(char c);

/**
 * @ingroup context
 * @brief Tests whether a parameter expansion ends at @p c.
 *
 * @param c Character to test.
 * @param _ Unused; present for the shared ending-predicate signature.
 * @return true if @p c is '}'.
 */
bool	is_context_param_ending(char c, void *_);

/**
 * @ingroup context
 * @brief Detects which expansion construct, if any, @p str begins.
 *
 * Tested in priority order: parameter, arithmetic, command substitution,
 * backquote.
 *
 * @param str Input cursor to test.
 * @param context Out-parameter receiving the detected context on a match.
 * @return true if @p str begins an expansion (and @p context was set).
 */
bool	is_expansion_context(char *str, t_context *context);

/**
 * @ingroup context
 * @brief Tests @p c against the whitelist of the given expansion context.
 *
 * Dispatches to the matching is_in_context_<x>_whitelist() for PARAM, ARITH,
 * CMD_SUB and BACKTICK.
 *
 * @param c Character to test.
 * @param context Expansion context whose whitelist to use.
 * @return true if @p c is special within @p context.
 */
bool	is_in_expansion_whitelist(char c, t_context context);

/**
 * @ingroup context
 * @brief Tests whether @p str begins ANSI-C quoting ($'  ).
 *
 * @param str Input cursor to test.
 * @return true if @p str starts with "$'".
 */
bool	is_context_dollar_squote_start(char *str);

/**
 * @ingroup context
 * @brief Whitelist for ANSI-C quoting: every character is processed.
 *
 * @param c Character to test (ignored).
 * @return Always true.
 */
bool	is_in_context_dollar_squote_whitelist(char c);

/**
 * @ingroup context
 * @brief Tests whether ANSI-C quoting ends at @p c.
 *
 * @param c Character to test.
 * @param _ Unused; present for the shared ending-predicate signature.
 * @return true if @p c is a single quote.
 */
bool	is_context_dollar_squote_ending(char c, void *_);

/**
 * @ingroup context
 * @brief Tests whether @p str begins a double-quoted section (").
 *
 * @param str Input cursor to test.
 * @return true if @p str starts with a double quote.
 */
bool	is_context_dquote_start(char *str);

/**
 * @ingroup context
 * @brief Whitelist of characters special inside double quotes.
 *
 * @param c Character to test.
 * @return true for '$', '`', '\\' and '"'.
 */
bool	is_in_context_dquote_whitelist(char c);

/**
 * @ingroup context
 * @brief Tests whether a double-quoted section ends at @p c.
 *
 * @param c Character to test.
 * @param _ Unused; present for the shared ending-predicate signature.
 * @return true if @p c is a double quote.
 */
bool	is_context_dquote_ending(char c, void *_);

/**
 * @ingroup context
 * @brief Tests whether @p str begins a single-quoted section (').
 *
 * @param str Input cursor to test.
 * @return true if @p str starts with a single quote.
 */
bool	is_context_squote_start(char *str);

/**
 * @ingroup context
 * @brief Whitelist for single quotes: nothing is special inside them.
 *
 * @param c Character to test (ignored).
 * @return Always false.
 */
bool	is_in_context_squote_whitelist(char c);

/**
 * @ingroup context
 * @brief Tests whether a single-quoted section ends at @p c.
 *
 * @param c Character to test.
 * @param _ Unused; present for the shared ending-predicate signature.
 * @return true if @p c is a single quote.
 */
bool	is_context_squote_ending(char c, void *_);

/**
 * @ingroup context
 * @brief Tests whether @p c closes the given quoting context.
 *
 * Dispatches to the matching is_context_<x>_ending() for SQUOTE, DQUOTE and
 * DOLLAR_SQUOTE.
 *
 * @param c Character to test.
 * @param context Quoting context to test against.
 * @return true if @p c closes @p context, false for non-quoting contexts.
 */
bool	is_quoting_ending(char c, t_context context);

/**
 * @ingroup context
 * @brief Detects which quoting construct, if any, @p str begins.
 *
 * Tested in priority order: single quote, ANSI-C quote, double quote.
 *
 * @param str Input cursor to test.
 * @param context Out-parameter receiving the detected context on a match.
 * @return true if @p str begins a quoting context (and @p context was set).
 */
bool	is_quoting_context(char *str, t_context *context);

/**
 * @ingroup context
 * @brief Tests @p c against the whitelist of the given quoting context.
 *
 * Dispatches to the matching is_in_context_<x>_whitelist() for NONE_, SQUOTE,
 * DQUOTE and DOLLAR_SQUOTE.
 *
 * @param c Character to test.
 * @param context Quoting context whose whitelist to use.
 * @return true if @p c is special within @p context.
 */
bool	is_in_quoting_whitelist(char c, t_context context);

#endif
