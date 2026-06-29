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
 *  about who drives it. Callers inject their behaviour through a @ref
 *  s_lexer_rules value:
 *  - the scanner provides POSIX token-recognition rules and a continuation
 *    reader, and drives it with lexer_get_next_token();
 *  - the heredoc provides expansion-only detection rules and drives it with
 *    lexer_track_context() to record the constructs found in a body;
 *  - an arithmetic tokeniser can reuse lexer_get_next_token() with its own
 *    recognition rules.
 *
 *  The recorded contexts (${ }, $(( )), $( ), ` `) are reported with their
 *  [start, end) range inside the scanned text, exactly as for a word token.
 */

/* ------------------------------------------------------------------------- */
/* Input stack                                                               */
/* ------------------------------------------------------------------------- */

/**
 * @ingroup lexer
 * @brief Stack of input sources, innermost on top (a vector of item pointers).
 *
 * The base input sits at the bottom; alias expansions and line continuations
 * are pushed on top and popped when exhausted, so the lexer always reads from
 * the topmost item.
 */
typedef t_vector	t_input_stack;

/**
 * @ingroup lexer
 * @struct s_input_lexer_stack_item
 * @brief One input source: its text, a read cursor and its own context stack.
 *
 * @var s_input_lexer_stack_item::i Read cursor (index into str).
 * @var s_input_lexer_stack_item::str Owned input text (NUL-terminated).
 * @var s_input_lexer_stack_item::context Per-input stack of open quoting/
 *                                        expansion contexts.
 */
typedef struct s_input_lexer_stack_item
{
	size_t			i;
	t_string		str;
	t_context_stack	context;
}	t_input_lexer_stack_item;

void	input_stack_init(t_input_stack *stack);
void	input_stack_free(t_input_stack *stack);
void	input_parser_stack_item_free(void *item);
t_error	input_parser_stack_item_init(t_input_lexer_stack_item **item);

t_error	input_stack_pop(t_input_stack *stack);
t_error	input_stack_push(t_input_stack *stack, t_input_lexer_stack_item *item);
t_error	input_stack_get_last(t_input_stack *stack,
			t_input_lexer_stack_item **item);

/* ------------------------------------------------------------------------- */
/* Lexer state and injected rules                                            */
/* ------------------------------------------------------------------------- */

typedef struct s_lexer	t_lexer;

/**
 * @ingroup lexer
 * @struct s_lexer_rules
 * @brief Behaviour injected by whoever drives the lexer.
 *
 * @var s_lexer_rules::recognize Applies one token-recognition rule to the
 *                               current character (used by
 *                               lexer_get_next_token; NULL for context-only
 *                               scans).
 * @var s_lexer_rules::on_eoi Handles end-of-input reached while still inside a
 *                            context: read a continuation line and resume, or
 *                            report ERR_UNEXPECTED_EOI. When NULL the lexer
 *                            reports ERR_UNEXPECTED_EOI.
 * @var s_lexer_rules::on_input_end Hook fired when the top input is exhausted
 *                                  and popped (e.g. end of an alias expansion);
 *                                  may be NULL.
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
 * @var s_lexer::err Last error recorded by the lexer.
 * @var s_lexer::input Borrowed pointer to the current (top) input item.
 * @var s_lexer::token Borrowed pointer to the token currently being built.
 * @var s_lexer::input_stack Stack of inputs; alias expansions and line
 *                           continuations are pushed on top of the base input.
 * @var s_lexer::emited_token Set when a complete token has been delimited.
 * @var s_lexer::rules Behaviour injected for the current drive.
 */
struct s_lexer
{
	t_error						err;
	t_lexer_rules				rules;
	t_input_lexer_stack_item	*input;
	t_token						*token;
	t_input_stack				input_stack;
	bool						emited_token;
};

/* ------------------------------------------------------------------------- */
/* Context-scan configuration                                                */
/* ------------------------------------------------------------------------- */

/**
 * @ingroup lexer
 * @struct s_escape_args
 * @brief Configures how a backslash is handled inside a given context.
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
 */
typedef struct s_unescape_args
{
	void	*special_args;
	t_error	(*special_handler)(t_lexer *, void *);
}	t_unescape_args;

/**
 * @ingroup lexer
 * @struct s_lexer_context_args
 * @brief Full configuration of one context scan driven by lexer_context_scan.
 */
typedef struct s_lexer_context_args
{
	t_context					context;
	size_t						opening_len;
	size_t						closing_len;
	t_context_parser_stack_item	*stack_item;
	void						*unescaped_args;
	t_error						(*escape)(t_lexer *);
	bool						(*is_end)(char, void *);
	t_error						(*unescaped)(t_lexer *, void *);
	t_error						(*quoting)(t_lexer *, t_context);
	bool						(*is_quoting)(char *, t_context *);
	t_error						(*expansion)(t_lexer *, t_context);
	bool						(*is_expansion)(char *, t_context *);
}	t_lexer_context_args;

/* ------------------------------------------------------------------------- */
/* Lifecycle                                                                 */
/* ------------------------------------------------------------------------- */

/**
 * @ingroup lexer
 * @brief Initialises the lexer to an empty, ready-to-use value.
 */
void			lexer_init(t_lexer *state);

/**
 * @ingroup lexer
 * @brief Releases the lexer's input stack and resets it to zero.
 */
void			lexer_free(t_lexer *state);

/**
 * @ingroup lexer
 * @brief Drops every input and the token in progress, ready for a fresh drive.
 */
void			lexer_reset(t_lexer *state);

/**
 * @ingroup lexer
 * @brief Pushes @p str as a new top input source.
 *
 * Allocates an input item, takes ownership of @p str and pushes it; on failure
 * @p str is freed and not pushed.
 *
 * @param state Pointer to the lexer state (borrowed).
 * @param str Input text to scan (ownership transferred on success).
 * @return ERR_NO on success, ERR_LIBC on allocation failure.
 */
t_error			lexer_push_input(t_lexer *state, t_string *str);

/* ------------------------------------------------------------------------- */
/* Public entry points                                                       */
/* ------------------------------------------------------------------------- */

/**
 * @ingroup lexer
 * @brief Produces the next token from the top input on the stack.
 *
 * Applies @p rules.recognize until a token is delimited or end-of-input is
 * reached; pops the input on end-of-input and fires @p rules.on_input_end.
 *
 * @param state Pointer to the lexer state (borrowed).
 * @param token Out-parameter receiving the produced token (borrowed).
 * @param rules Behaviour injected by the caller.
 * @return ERR_NO on success, ERR_EMPTY_STACK if no input remains, or the
 *         recorded error on failure.
 */
t_error			lexer_get_next_token(t_lexer *state, t_token *token,
					t_lexer_rules rules);

/**
 * @ingroup lexer
 * @brief Records the quoting/expansion contexts found in the top input.
 *
 * Scans the whole top input at the NONE (top) level using @p args to drive
 * detection, then deep-copies the recorded constructs (with their [start, end)
 * ranges) into @p out. @p args supplies the detection callbacks; the context
 * tag, delimiter lengths and outer stack item are filled in by this function.
 *
 * @param state Pointer to the lexer state (borrowed).
 * @param out Already-initialised stack receiving the deep-copied contexts.
 * @param args Detection configuration for the top-level scan.
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error			lexer_track_context(t_lexer *state, t_context_stack *out,
					t_lexer_context_args args);

/* ------------------------------------------------------------------------- */
/* Engine primitives (for caller-provided rules)                            */
/* ------------------------------------------------------------------------- */

/**
 * @ingroup lexer
 * @brief Advances the input cursor by @p offset characters (no consumption).
 */
void			lexer_advance(t_lexer *state, size_t offset);

/**
 * @ingroup lexer
 * @brief Appends @p iter input characters to the token and advances.
 */
t_error			lexer_consume(t_lexer *state, t_token_type type, size_t iter);

/**
 * @ingroup lexer
 * @brief Marks the token currently being built as complete.
 */
void			lexer_delimit_token(t_lexer *state);

/**
 * @ingroup lexer
 * @brief Snapshots the lexer for a possible later rollback.
 */
t_lexer_backup	lexer_backup(t_lexer *state);

/**
 * @ingroup lexer
 * @brief Restores the lexer to a previously captured backup.
 */
t_error			lexer_restore(t_lexer *state, t_lexer_backup backup);

/* ------------------------------------------------------------------------- */
/* Context toolkit                                                           */
/* ------------------------------------------------------------------------- */

/**
 * @ingroup lexer
 * @brief Handles reaching end-of-input while still inside a context.
 *
 * Delegates to the injected rules.on_eoi (continuation or error); reports
 * ERR_UNEXPECTED_EOI when no handler is provided.
 */
t_error			context_EOI(t_lexer *state);

/**
 * @ingroup lexer
 * @brief Consumes the character following a backslash when whitelisted.
 */
t_error			context_escape_next_char(t_lexer *state, t_escape_args args);

/**
 * @ingroup lexer
 * @brief Generic scan loop for one quoting/expansion context.
 */
t_error			lexer_context_scan(t_lexer *state, t_lexer_context_args args);

/**
 * @ingroup lexer
 * @brief Handles a backslash inside a context (line continuation or escape).
 */
t_error			lexer_context_escape(t_lexer *state, t_escape_args args);

/**
 * @ingroup lexer
 * @brief Consumes one plain character of a context (or end-of-input/handler).
 */
t_error			lexer_context_unescape(t_lexer *state, t_unescape_args args);

/**
 * @ingroup lexer
 * @brief Scans a quoting or expansion construct of the given context.
 */
t_error			lexer_context(t_lexer *state, t_context context);

/**
 * @ingroup lexer
 * @brief Scans a quoting construct, keeping it in the token (POSIX rule 4).
 */
t_error			lexer_rule_quoting(t_lexer *state, t_context context);

/**
 * @ingroup lexer
 * @brief Scans an expansion construct, keeping it in the token (POSIX rule 5).
 *
 * For an arithmetic context, falls back to command substitution when the
 * "$((" turns out not to close as arithmetic.
 */
t_error			lexer_rule_expansion(t_lexer *state, t_context context);

t_error			lexer_context_param(t_lexer *state);
t_error			lexer_context_arith(t_lexer *state);
t_error			lexer_context_dquote(t_lexer *state);
t_error			lexer_context_backtick(t_lexer *state);
t_error			lexer_context_squote(t_lexer *state);
t_error			lexer_context_dollar_squote(t_lexer *state);

#endif
