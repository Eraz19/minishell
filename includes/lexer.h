#ifndef LEXER_H
# define LEXER_H

# include "token.h"
# include "error.h"
# include "context.h"

/** @defgroup lexer Lexer API
 *  @brief Generic, rule-driven scanning engine over an input stack.
 *
 *  The lexer is a standalone helper module: it owns the cursor, the input
 *  stack and the quoting/expansion context machinery, but it knows nothing
 *  about who drives it. Callers inject their behaviour through a
 *  @ref s_lexer_rules value:
 *  - the scanner provides POSIX token-recognition rules and a continuation
 *    reader, and drives it with @ref lexer_get_next_token;
 *  - the heredoc provides expansion-only detection rules and drives it with
 *    @ref lexer_track_context to record the constructs found in a body;
 *  - an arithmetic tokeniser can reuse @ref lexer_get_next_token with its
 *    own recognition rules.
 *
 *  The recorded contexts (@c ${ @c }, @c $(( @c )), @c $( @c ), @c ` @c `)
 *  are reported with their @c [start, @c end) range inside the scanned
 *  text, exactly as for a word token.
 *
 *  ERROR CONTRACT
 *
 *  The lexer deliberately does NOT requalify its errors: its callers (the
 *  scanner endpoints, the heredoc preparation) are the requalifiers and
 *  need the specific types to map unexpected ends of input onto
 *  @c ERR_POSIX_SYNTAX and inconsistencies onto @c ERR_INTERNAL. Every
 *  error type listed below therefore crosses this API raw.
 *
 *  - @c ERR_UNEXPECTED_EOI is printed at production by @ref context_EOI,
 *    the only place that knows which construct is unterminated (top of the
 *    input's context stack); requalifiers must not reprint it (the
 *    @c printed flag protects them).
 *  - @c ERR_CTX_END_NOT_FOUND is internal control flow: produced by
 *    @ref lexer_context_arith when @c "$((" does not close as arithmetic,
 *    consumed by @ref lexer_rule_expansion which retries the construct as
 *    a command substitution (POSIX 2.6.4). It is never printed.
 *  - Errors of the injected @ref s_lexer_rules callbacks (continuation
 *    reader, recognition rules) propagate verbatim; with the scanner's
 *    rules this adds @c ERR_VEOF (end of interactive input, never printed
 *    here) and the reader's qualified errors.
 *  - @c ERR_NOT_IMPLEMENTED (printed by the stub): command substitution
 *    scanning is fully wired (@ref lexer_context_cmd_sub) but blocked on
 *    the @c runner_find_cmd_sub_closing recursive-parse stub in
 *    @c TODO.c; implementing that stub makes @c $(...) tokenization live
 *    without further lexer changes.
 */

/**
 * @ingroup lexer
 * @typedef t_lexer_input_stack
 * @brief Stack of input sources, innermost on top, backed by a
 *        @ref t_vector of @ref s_lexer_input_stack_item pointers (owned by
 *        the stack).
 *
 * The base input sits at the bottom; alias expansions and line
 * continuations are pushed on top and popped when exhausted, so the lexer
 * always reads from the topmost item.
 */
typedef t_vector	t_lexer_input_stack;

/**
 * @ingroup lexer
 * @struct s_lexer_input_stack_item
 * @brief One input source: its text, a read cursor and its own context
 *        stack.
 *
 * @var s_lexer_input_stack_item::i Read cursor (index into @c str).
 * @var s_lexer_input_stack_item::str Input text, NUL-terminated, a
 *                                    @ref t_string owned by the item.
 * @var s_lexer_input_stack_item::context Stack of currently open quoting/
 *                                        expansion contexts; its items are
 *                                        borrowed from the token's context
 *                                        stack, which owns them (borrowed).
 */
typedef struct s_lexer_input_stack_item
{
	size_t			i;
	t_string		str;
	t_context_stack	context;
}	t_lexer_input_stack_item;

typedef struct s_lexer	t_lexer;

/**
 * @ingroup lexer
 * @struct s_lexer_rules
 * @brief Behaviour injected by whoever drives the lexer.
 *
 * @var s_lexer_rules::recognize Applies one token-recognition rule to the
 *                               current character (used by
 *                               @ref lexer_get_next_token; @c NULL for
 *                               context-only scans).
 * @var s_lexer_rules::on_eoi Handles end of input reached while still
 *                            inside a context: read a continuation line
 *                            and resume, or report the error. When
 *                            @c NULL, @ref context_EOI reports
 *                            @c ERR_UNEXPECTED_EOI (printed).
 * @var s_lexer_rules::on_input_end Hook fired when the top input is
 *                                  exhausted and popped (e.g. end of an
 *                                  alias expansion); may be @c NULL.
 */
typedef struct s_lexer_rules
{
	t_error	(*on_eoi)(t_lexer *);
	t_error	(*on_input_end)(t_lexer *);
	t_error	(*recognize)(t_lexer *, t_context *);
}	t_lexer_rules;

/**
 * @ingroup lexer
 * @struct s_lexer_backup
 * @brief Snapshot of the lexer used to roll back a speculative scan.
 *
 * @var s_lexer_backup::i Saved read cursor.
 * @var s_lexer_backup::token_type Saved type of the token in progress.
 * @var s_lexer_backup::context_len Saved depth of the input context stack.
 * @var s_lexer_backup::token_value_len Saved length of the token value.
 * @var s_lexer_backup::token_contexts_len Saved depth of the token context
 *                                         stack.
 */
typedef struct s_lexer_backup
{
	size_t			i;
	t_token_type	token_type;
	size_t			context_len;
	size_t			token_value_len;
	size_t			token_contexts_len;
}	t_lexer_backup;

/**
 * @ingroup lexer
 * @struct s_lexer
 * @brief State of the rule-driven scanning engine.
 *
 * @var s_lexer::err Last error recorded by the module.
 * @var s_lexer::rules Behaviour injected for the current drive.
 * @var s_lexer::input Current (top) input item (borrowed).
 * @var s_lexer::token Token currently being built (borrowed).
 * @var s_lexer::input_stack Stack of inputs owned by the lexer; alias
 *                           expansions and line continuations are pushed
 *                           on top of the base input.
 * @var s_lexer::emited_token Set when a complete token has been delimited.
 */
struct s_lexer
{
	t_error						err;
	t_lexer_rules				rules;
	t_lexer_input_stack_item	*input;
	t_token						*token;
	t_lexer_input_stack			input_stack;
	bool						emited_token;
};

/**
 * @ingroup lexer
 * @struct s_escape_args
 * @brief Configures how a backslash is handled inside a given context.
 *
 * @var s_escape_args::enable_line_continuation Remove backslash-newline
 *                                              pairs instead of keeping
 *                                              them.
 * @var s_escape_args::is_in_whitelist Escapable-character set of the
 *                                     context.
 * @var s_escape_args::is_in_special_whitelist Escapable set used while in
 *                                             the special context; may be
 *                                             @c NULL.
 * @var s_escape_args::is_in_special_context Tells whether the special set
 *                                           applies; may be @c NULL.
 */
typedef struct s_escape_args
{
	bool	enable_line_continuation;
	bool	(*is_in_whitelist)(char);
	bool	(*is_in_special_whitelist)(char);
	bool	(*is_in_special_context)(t_lexer *);
}	t_escape_args;

/**
 * @ingroup lexer
 * @struct s_unescape_args
 * @brief Configures how a plain (non-delimiter) character is consumed.
 *
 * @var s_unescape_args::special_args Argument forwarded to the handler
 *                                    (borrowed).
 * @var s_unescape_args::special_handler Consumes one character with
 *                                       context-specific bookkeeping
 *                                       (e.g. parenthesis depth); may be
 *                                       @c NULL for a plain consume.
 */
typedef struct s_unescape_args
{
	void	*special_args;
	t_error	(*special_handler)(t_lexer *, void *);
}	t_unescape_args;

/**
 * @ingroup lexer
 * @struct s_lexer_context_args
 * @brief Full configuration of one context scan driven by
 *        @ref lexer_context_scan.
 *
 * @var s_lexer_context_args::context Context tag recorded on the stacks.
 * @var s_lexer_context_args::opening_len Characters consumed as the
 *                                        opening delimiter.
 * @var s_lexer_context_args::closing_len Characters consumed as the
 *                                        closing delimiter.
 * @var s_lexer_context_args::stack_item Item recording the construct span;
 *                                       owned by the token's context stack
 *                                       or by the caller (borrowed).
 * @var s_lexer_context_args::unescaped_args Argument forwarded to
 *                                           @c is_end and @c unescaped
 *                                           (borrowed).
 * @var s_lexer_context_args::escape Handles a backslash.
 * @var s_lexer_context_args::is_end Detects the closing delimiter.
 * @var s_lexer_context_args::unescaped Consumes one plain character.
 * @var s_lexer_context_args::quoting Scans a nested quoting construct; may
 *                                    be @c NULL.
 * @var s_lexer_context_args::is_quoting Detects a nested quoting
 *                                       construct; may be @c NULL.
 * @var s_lexer_context_args::expansion Scans a nested expansion construct;
 *                                      may be @c NULL.
 * @var s_lexer_context_args::is_expansion Detects a nested expansion
 *                                         construct; may be @c NULL.
 */
typedef struct s_lexer_context_args
{
	t_context				context;
	size_t					opening_len;
	size_t					closing_len;
	t_context_stack_item	*stack_item;
	void					*unescaped_args;
	t_error					(*escape)(t_lexer *);
	bool					(*is_end)(char, void *);
	t_error					(*unescaped)(t_lexer *, void *);
	t_error					(*quoting)(t_lexer *, t_context);
	bool					(*is_quoting)(char *, t_context *);
	t_error					(*expansion)(t_lexer *, t_context);
	bool					(*is_expansion)(char *, t_context *);
}	t_lexer_context_args;

/* ************************************************************************* */
/*                                LIFE_CYCLE                                 */
/* ************************************************************************* */

/**
 * @ingroup lexer
 * @brief Zeroes @p lexer and initializes its empty input stack.
 *
 * @param lexer Lexer initialized by the function (borrowed).
 */
void			lexer_init(t_lexer *lexer);

/**
 * @ingroup lexer
 * @brief Drops every input and the token in progress, ready for a fresh
 *        drive (typically after a syntax error).
 *
 * @param lexer Already initialized lexer (borrowed).
 */
void			lexer_reset(t_lexer *lexer);

/**
 * @ingroup lexer
 * @brief Releases the input stack of @p lexer and zeroes it.
 *
 * @param lexer Already initialized lexer (borrowed).
 */
void			lexer_free(t_lexer *lexer);

/* ************************************************************************* */
/*                                INPUT STACK                                */
/* ************************************************************************* */

/**
 * @ingroup lexer
 * @brief Frees @p stack and every input item it owns.
 *
 * @param stack Already initialized stack (borrowed).
 */
void			lexer_input_stack_free(t_lexer_input_stack *stack);

/**
 * @ingroup lexer
 * @brief Fetches the top (current) input item without removing it.
 *
 * @param stack Already initialized stack (borrowed).
 * @param item Set to the top item; @p stack keeps ownership (borrowed).
 * @return @c ERR_EMPTY_STACK if @p stack is empty, @c ERR_NO on success.
 */
t_error			lexer_input_stack_get_last(
					t_lexer_input_stack *stack,
					t_lexer_input_stack_item **item);

/**
 * @ingroup lexer
 * @brief Initializes @p stack as an empty input stack.
 *
 * @param stack Stack initialized by the function (borrowed).
 */
void			lexer_input_stack_init(t_lexer_input_stack *stack);

/**
 * @ingroup lexer
 * @brief Frees one input item: its text, its context stack and the item
 *        itself, then sets the caller's pointer to @c NULL.
 *
 * @note The context stack entries are borrowed from the token's context
 *       stack, so only the backing storage is released, not the entries.
 * @note Signature matches the @c vector_free element destructor callback.
 * @param item Pointer to the item pointer to free, as an untyped pointer
 *             (borrowed).
 */
void			lexer_input_stack_item_free(void *item);

/**
 * @ingroup lexer
 * @brief Allocates a zeroed input item with an empty context stack.
 *
 * @param item Set to the newly allocated item; the caller becomes its
 *             owner until it is pushed with @ref lexer_input_stack_push
 *             (borrowed).
 * @return @c ERR_LIBC if the allocation fails, @c ERR_NO on success.
 */
t_error			lexer_input_stack_item_init(t_lexer_input_stack_item **item);

/**
 * @ingroup lexer
 * @brief Pops and frees the top input item of @p stack.
 *
 * @param stack Already initialized stack (borrowed).
 */
void	lexer_input_stack_pop(t_lexer_input_stack *stack);

/**
 * @ingroup lexer
 * @brief Pushes @p item on top of @p stack.
 *
 * @param stack Already initialized stack (borrowed).
 * @param item Item to push (ownership taken by @p stack).
 * @return @c ERR_LIBC if the push fails, @c ERR_NO on success.
 */
t_error			lexer_input_stack_push(
					t_lexer_input_stack *stack,
					t_lexer_input_stack_item *item);

/* ************************************************************************* */
/*                               ENTRY POINTS                                */
/* ************************************************************************* */

/**
 * @ingroup lexer
 * @brief Produces the next token from the top input on the stack.
 *
 * Applies @p rules.recognize until a token is delimited or end of input is
 * reached; pops the input on a @c TOKEN_EOF and fires
 * @p rules.on_input_end.
 *
 * @param lexer Already initialized lexer holding at least one input
 *              (borrowed).
 * @param token Token initialized by the function; the caller owns it and
 *              must release it with @c token_free (borrowed).
 * @param rules Behaviour injected by the caller.
 * @return @c ERR_EMPTY_STACK if no input remains; @c ERR_LIBC on
 *         allocation failure; from the context toolkit reached through the
 *         recognition rules: @c ERR_UNEXPECTED_EOI (printed),
 *         @c ERR_NO_INPUT_TO_LEX, @c ERR_NOT_IMPLEMENTED (printed),
 *         @c ERR_INCOHERENT_STATE; any error of the injected
 *         @p rules callbacks, verbatim; @c ERR_NO on success.
 */
t_error			lexer_get_next_token(
					t_lexer *lexer,
					t_token *token,
					t_lexer_rules rules);

/**
 * @ingroup lexer
 * @brief Pushes @p str as a new top input source.
 *
 * @param lexer Already initialized lexer (borrowed).
 * @param str Input text to scan; its buffer is taken in every outcome and
 *            @p str is left as an empty initialized string (ownership
 *            taken by the lexer).
 * @return @c ERR_LIBC on allocation or push failure, @c ERR_NO on success.
 */
t_error			lexer_push_input(t_lexer *lexer, t_string *str);

/**
 * @ingroup lexer
 * @brief Rewrites @p word without its escaped newlines, scanning it with
 *        @p args on a private lexer.
 *
 * @param word Word to clean; replaced by the cleaned copy (borrowed).
 * @param args Detection configuration for the scan; the context tag,
 *             delimiter lengths and stack item are filled in by the
 *             function.
 * @return @c ERR_LIBC on allocation failure; @c ERR_EMPTY_STACK on an
 *         input stack inconsistency; from the scan: @c ERR_UNEXPECTED_EOI
 *         (printed), @c ERR_NO_INPUT_TO_LEX, @c ERR_NOT_IMPLEMENTED
 *         (printed), @c ERR_INCOHERENT_STATE; @c ERR_NO on success.
 */
t_error			lexer_remove_escaped_newlines(
					t_string *word,
					t_lexer_context_args args);

/**
 * @ingroup lexer
 * @brief Records the quoting/expansion contexts found in the top input.
 *
 * Scans the whole top input at the NONE (top) level using @p args to drive
 * detection, then deep-copies the recorded constructs (with their
 * @c [start, @c end) ranges) into @p out.
 *
 * @param lexer Already initialized lexer holding at least one input
 *              (borrowed).
 * @param out Destination stack, already initialized by the caller; the
 *            copied contexts are appended (borrowed).
 * @param args Detection configuration; the context tag, delimiter lengths
 *             and outer stack item are filled in by the function.
 * @return @c ERR_EMPTY_STACK if no input remains; @c ERR_LIBC on
 *         allocation failure; @c ERR_INDEX_OUT_OF_BOUND if the final copy
 *         fails; from the scan: @c ERR_UNEXPECTED_EOI (printed),
 *         @c ERR_NO_INPUT_TO_LEX, @c ERR_NOT_IMPLEMENTED (printed),
 *         @c ERR_INCOHERENT_STATE; @c ERR_NO on success.
 */
t_error			lexer_track_context(
					t_lexer *lexer,
					t_context_stack *out,
					t_lexer_context_args args);

/* ************************************************************************* */
/*                             ENGINE PRIMITIVES                             */
/* ************************************************************************* */

/**
 * @ingroup lexer
 * @brief Advances the input cursor by @p offset characters without
 *        consuming them into the token.
 *
 * @param lexer Already initialized lexer (borrowed).
 * @param offset Characters to skip.
 */
void			lexer_advance(t_lexer *lexer, size_t offset);

/**
 * @ingroup lexer
 * @brief Snapshots the lexer for a possible later @ref lexer_restore.
 *
 * @param lexer Already initialized lexer (borrowed, read-only).
 * @return The snapshot value.
 */
t_lexer_backup	lexer_backup(t_lexer *lexer);

/**
 * @ingroup lexer
 * @brief Appends @p iter input characters to the token, tags it with
 *        @p type and advances the cursor.
 *
 * @param lexer Already initialized lexer (borrowed).
 * @param type Token type to record.
 * @param iter Characters to consume.
 * @return @c ERR_LIBC if an append fails, otherwise the lexer's recorded
 *         error.
 */
t_error			lexer_consume(t_lexer *lexer, t_token_type type, size_t iter);

/**
 * @ingroup lexer
 * @brief Marks the token currently being built as complete and records its
 *        end offset in the raw input.
 *
 * @param lexer Already initialized lexer (borrowed).
 */
void			lexer_delimit_token(t_lexer *lexer);

/**
 * @ingroup lexer
 * @brief Restores the lexer to a previously captured @p backup, unwinding
 *        both context stacks and the token value.
 *
 * @param lexer Already initialized lexer (borrowed).
 * @param backup Snapshot captured by @ref lexer_backup.
 * @return @c ERR_EMPTY_STACK or @c ERR_LIBC if a context unwind fails,
 *         @c ERR_NO on success.
 */
t_error			lexer_restore(t_lexer *lexer, t_lexer_backup backup);

/* ************************************************************************* */
/*                              CONTEXT TOOLKIT                              */
/* ************************************************************************* */

/**
 * @ingroup lexer
 * @brief Handles reaching end of input while still inside a context.
 *
 * Delegates to the injected @c rules.on_eoi (continuation) when present.
 * Otherwise reports @c ERR_UNEXPECTED_EOI, printed here with the name of
 * the unterminated construct (top of the input's context stack): this is
 * the most specific diagnostic point, requalifiers must not reprint it.
 *
 * @param lexer Already initialized lexer (borrowed).
 * @return The @c on_eoi handler's error, verbatim; or
 *         @c ERR_UNEXPECTED_EOI (printed).
 */
t_error			context_EOI(t_lexer *lexer);

/**
 * @ingroup lexer
 * @brief Consumes the character following a backslash when the context's
 *        whitelist marks it as escapable; a non-escapable character is
 *        left for the normal scan (the backslash stays literal).
 *
 * @param lexer Already initialized lexer (borrowed).
 * @param args Escape configuration of the context.
 * @return @c ERR_LIBC if the consume fails, @c ERR_INCOHERENT_STATE when
 *         no applicable whitelist is configured, otherwise the lexer's
 *         recorded error.
 */
t_error			context_escape_next_char(t_lexer *lexer, t_escape_args args);

/**
 * @ingroup lexer
 * @brief Scans one construct of the given @p context, dispatching to the
 *        matching @c lexer_context_* function.
 *
 * @param lexer Already initialized lexer (borrowed).
 * @param context Construct to scan; @c CONTEXT_NONE and @c CONTEXT_HEREDOC
 *                are not scannable constructs.
 * @return @c ERR_INCOHERENT_STATE for a non-scannable @p context;
 *         otherwise the dispatched function's error, verbatim.
 */
t_error			lexer_context(t_lexer *lexer, t_context context);

/**
 * @ingroup lexer
 * @brief Scans an arithmetic expansion @c $((...)), tracking parenthesis
 *        depth, and rolls the lexer back when it does not close as
 *        arithmetic.
 *
 * @param lexer Already initialized lexer (borrowed).
 * @return @c ERR_CTX_END_NOT_FOUND when the construct does not close with
 *         @c "))" (after rollback; consumed by @ref lexer_rule_expansion
 *         as the POSIX 2.6.4 command substitution fallback, never
 *         printed); @c ERR_LIBC on allocation failure;
 *         @c ERR_UNEXPECTED_EOI (printed) or the @c on_eoi handler's error
 *         at end of input; @c ERR_EMPTY_STACK on a context stack
 *         inconsistency; from nested constructs: @c ERR_NO_INPUT_TO_LEX,
 *         @c ERR_NOT_IMPLEMENTED (printed), @c ERR_INCOHERENT_STATE;
 *         @c ERR_NO on success.
 */
t_error			lexer_context_arith(t_lexer *lexer);

/**
 * @ingroup lexer
 * @brief Scans a backquote command substitution, with the extended escape
 *        set when the backquotes are nested in double quotes or
 *        arithmetic.
 *
 * @param lexer Already initialized lexer (borrowed).
 * @return @c ERR_LIBC on allocation failure; @c ERR_UNEXPECTED_EOI
 *         (printed) or the @c on_eoi handler's error at end of input;
 *         @c ERR_EMPTY_STACK on a context stack inconsistency; from nested
 *         constructs: @c ERR_CTX_END_NOT_FOUND, @c ERR_NO_INPUT_TO_LEX,
 *         @c ERR_NOT_IMPLEMENTED (printed), @c ERR_INCOHERENT_STATE;
 *         @c ERR_NO on success.
 */
t_error			lexer_context_backtick(t_lexer *lexer);

/**
 * @ingroup lexer
 * @brief Scans a command substitution @c $(...), finding the closing
 *        parenthesis by recursive parsing (POSIX 2.6.3).
 *
 * @warning Blocked on the @c runner_find_cmd_sub_closing stub: until it is
 *          implemented the scan reports @c ERR_NOT_IMPLEMENTED (printed by
 *          the stub); no other lexer change is needed to enable it.
 * @param lexer Already initialized lexer (borrowed).
 * @return @c ERR_NOT_IMPLEMENTED (printed) from the closing finder stub;
 *         @c ERR_NO_INPUT_TO_LEX when no input is loaded; @c ERR_LIBC on
 *         allocation failure; @c ERR_UNEXPECTED_EOI (printed) or the
 *         @c on_eoi handler's error at end of input; @c ERR_NO on success.
 */
t_error			lexer_context_cmd_sub(t_lexer *lexer);

/**
 * @ingroup lexer
 * @brief Scans an ANSI-C quoted string @c $'...' (no nested constructs,
 *        every character escapable).
 *
 * @param lexer Already initialized lexer (borrowed).
 * @return @c ERR_LIBC on allocation failure; @c ERR_UNEXPECTED_EOI
 *         (printed) or the @c on_eoi handler's error at end of input;
 *         @c ERR_EMPTY_STACK on a context stack inconsistency; @c ERR_NO
 *         on success.
 */
t_error			lexer_context_dollar_squote(t_lexer *lexer);

/**
 * @ingroup lexer
 * @brief Scans a double-quoted string, with nested expansions and the
 *        POSIX 2.2.3 escape set (@c $, @c `, @c ", @c \, line
 *        continuation).
 *
 * @param lexer Already initialized lexer (borrowed).
 * @return @c ERR_LIBC on allocation failure; @c ERR_UNEXPECTED_EOI
 *         (printed) or the @c on_eoi handler's error at end of input;
 *         @c ERR_EMPTY_STACK on a context stack inconsistency; from nested
 *         constructs: @c ERR_CTX_END_NOT_FOUND, @c ERR_NO_INPUT_TO_LEX,
 *         @c ERR_NOT_IMPLEMENTED (printed), @c ERR_INCOHERENT_STATE;
 *         @c ERR_NO on success.
 */
t_error			lexer_context_dquote(t_lexer *lexer);

/**
 * @ingroup lexer
 * @brief Handles a backslash inside a context: removes a line continuation
 *        when enabled, otherwise consumes the backslash and lets
 *        @ref context_escape_next_char decide about the next character.
 *
 * @param lexer Already initialized lexer (borrowed).
 * @param args Escape configuration of the context.
 * @return @c ERR_LIBC on allocation failure; @c ERR_UNEXPECTED_EOI
 *         (printed) or the @c on_eoi handler's error when the input ends
 *         on the escape; @c ERR_INCOHERENT_STATE when no whitelist is
 *         configured; @c ERR_NO on success.
 */
t_error			lexer_context_escape(t_lexer *lexer, t_escape_args args);

/**
 * @ingroup lexer
 * @brief Scans a parameter expansion @c ${...}, with nested quoting and
 *        expansions.
 *
 * @param lexer Already initialized lexer (borrowed).
 * @return @c ERR_LIBC on allocation failure; @c ERR_UNEXPECTED_EOI
 *         (printed) or the @c on_eoi handler's error at end of input;
 *         @c ERR_EMPTY_STACK on a context stack inconsistency; from nested
 *         constructs: @c ERR_CTX_END_NOT_FOUND, @c ERR_NO_INPUT_TO_LEX,
 *         @c ERR_NOT_IMPLEMENTED (printed), @c ERR_INCOHERENT_STATE;
 *         @c ERR_NO on success.
 */
t_error			lexer_context_param(t_lexer *lexer);

/**
 * @ingroup lexer
 * @brief Generic scan loop for one quoting/expansion context: opens the
 *        construct, dispatches every character to the configured handlers
 *        and closes it on the end delimiter.
 *
 * @param lexer Already initialized lexer (borrowed).
 * @param args Full configuration of the scan.
 * @return @c ERR_LIBC on allocation failure; @c ERR_EMPTY_STACK if the
 *         context close fails; any error recorded by the configured
 *         handlers, verbatim; @c ERR_NO on success.
 */
t_error			lexer_context_scan(t_lexer *lexer, t_lexer_context_args args);

/**
 * @ingroup lexer
 * @brief Scans a single-quoted string: no escapes, no nested constructs,
 *        @c ' closes (POSIX 2.2.2).
 *
 * @param lexer Already initialized lexer (borrowed).
 * @return @c ERR_LIBC on allocation failure; @c ERR_UNEXPECTED_EOI
 *         (printed) or the @c on_eoi handler's error at end of input;
 *         @c ERR_EMPTY_STACK on a context stack inconsistency; @c ERR_NO
 *         on success.
 */
t_error			lexer_context_squote(t_lexer *lexer);

/**
 * @ingroup lexer
 * @brief Consumes one plain character of a context: end of input goes to
 *        @ref context_EOI, otherwise the special handler or a plain
 *        consume.
 *
 * @param lexer Already initialized lexer (borrowed).
 * @param args Plain-character configuration of the context.
 * @return @c ERR_LIBC on allocation failure; @c ERR_UNEXPECTED_EOI
 *         (printed) or the @c on_eoi handler's error at end of input; the
 *         special handler's error, verbatim; @c ERR_NO on success.
 */
t_error			lexer_context_unescape(t_lexer *lexer, t_unescape_args args);

/**
 * @ingroup lexer
 * @brief Scans an expansion construct, keeping it in the token (POSIX
 *        rule 5).
 *
 * For an arithmetic context, consumes @c ERR_CTX_END_NOT_FOUND and retries
 * the construct as a command substitution when @c "$((" turns out not to
 * close as arithmetic (POSIX 2.6.4).
 *
 * @param lexer Already initialized lexer (borrowed).
 * @param context Expansion construct to scan.
 * @return The scanned construct's error, verbatim (see the matching
 *         @c lexer_context_* function); @c ERR_INCOHERENT_STATE for a
 *         non-scannable @p context; @c ERR_NO on success.
 */
t_error			lexer_rule_expansion(t_lexer *lexer, t_context context);

/**
 * @ingroup lexer
 * @brief Scans a quoting construct, keeping it in the token (POSIX
 *        rule 4).
 *
 * @param lexer Already initialized lexer (borrowed).
 * @param context Quoting construct to scan.
 * @return The scanned construct's error, verbatim (see the matching
 *         @c lexer_context_* function); @c ERR_INCOHERENT_STATE for a
 *         non-scannable @p context; @c ERR_NO on success.
 */
t_error			lexer_rule_quoting(t_lexer *lexer, t_context context);

#endif
