#ifndef TOKEN_H
# define TOKEN_H

# include "error.h"
# include "libft.h"
# include "context.h"
# include "ast_vector_type.h"

/** @defgroup token Token API
 *  @brief Lexical tokens produced by the scanner.
 *
 *  A token couples a grammar type with the raw text that produced it. The
 *  text lives in an owned, growable string, so a token owns its value and
 *  @ref token_dup hands out an independent deep copy.
 *
 *  A word token also carries the quoting and expansion constructs found
 *  while scanning it (@c ${ @c }, @c $(( @c )), @c ` @c `, quotes, ...), in
 *  the left-to-right order their openings appeared, each marked with its
 *  @c [start, @c end) range inside the value string, so the expansion phase
 *  can locate every construct without rescanning the word.
 */

/**
 * @ingroup token
 * @enum e_token_type
 * @brief Grammar type of a token, using the POSIX shell token names.
 */
typedef enum e_token_type
{
	TOKEN_NONE,
	TOKEN_TOKEN,
	TOKEN_NEWLINE,
	TOKEN_SCOLON,
	TOKEN_AMPERSAND,
	TOKEN_DSEMI,
	TOKEN_SEMI_AND,
	TOKEN_AND_IF,
	TOKEN_OR_IF,
	TOKEN_PIPE,
	TOKEN_LPARENTHESIS,
	TOKEN_RPARENTHESIS,
	TOKEN_LESSAND,
	TOKEN_GREATAND,
	TOKEN_LESS,
	TOKEN_GREAT,
	TOKEN_CLOBBER,
	TOKEN_LESSGREAT,
	TOKEN_DGREAT,
	TOKEN_DLESS,
	TOKEN_DLESSDASH,
	TOKEN_IO_NUMBER,
	TOKEN_IO_LOCATION,
	TOKEN_EOF
}	t_token_type;

/**
 * @ingroup token
 * @struct s_token_index
 * @brief Byte span of a token inside the raw BASE input, both bounds
 *        INCLUSIVE.
 *
 * Every field is @c -1 until the lexer sets it. Tokens produced from a
 * nested input (alias expansion) inherit the span of the originating
 * word in the base input, so reported positions stay meaningful.
 *
 * @var s_token_index::end Offset of the LAST character of the token in
 *                         the raw input (inclusive; equals @c start for
 *                         a token with no consumed character), @c -1
 *                         when unset.
 * @var s_token_index::start Offset of the first character of the token in
 *                           the raw input, @c -1 when unset.
 * @var s_token_index::error Offset of the character associated with a
 *                           lexing error, @c -1 when none.
 */
typedef struct s_token_index
{
	ssize_t	end;
	ssize_t	start;
	ssize_t	error;
}	t_token_index;

/**
 * @ingroup token
 * @struct s_token
 * @brief One lexical token: its grammar type, text and scanning metadata.
 *
 * @var s_token::type Grammar type of the token.
 * @var s_token::value Raw text of the token, a @ref t_string owned by the
 *                     token (initialized by @ref token_init, released by
 *                     @ref token_free).
 * @var s_token::index Span of the token in the raw lexer input, managed by
 *                     the lexer submodule.
 * @var s_token::contexts Constructs recorded while scanning the word, in
 *                        left-to-right opening order, spans relative to
 *                        @c value; a @ref t_context_stack owned by the
 *                        token, managed by the context submodule.
 * @var s_token::assignment_offset Offset in @c value of the @c '=' that
 *                                 splits an assignment word into name and
 *                                 value, @c -1 when the word is not an
 *                                 assignment.
 */
typedef struct s_token
{
	t_token_type	type;
	t_string		value;
	t_token_index	index;
	t_context_stack	contexts;
	ssize_t			assignment_offset;
	t_ast_vector	ast_vector;
}	t_token;

// vector of t_token
typedef t_vector	t_token_pool;

/* -------------------- LIFE CYCLE -------------------- */

/**
 * @ingroup token
 * @brief Zeroes @p token, giving it an empty value string, an empty context
 *        stack, type @c TOKEN_NONE, and every index and the assignment
 *        offset set to @c -1.
 *
 * @param token Token initialized by the function (borrowed).
 */
void	token_init(t_token *token);

/**
 * @ingroup token
 * @brief Frees the value string and context stack of @p token, then resets
 *        it to the unset state (indexes and assignment offset back to
 *        @c -1).
 *
 * @param token Already initialized token (borrowed).
 */
void	token_free(t_token *token);

/**
 * @ingroup token
 * @brief Frees the token pointed to by @p token, as @ref token_free does.
 *
 * @note Signature matches the @c vector_free element destructor callback.
 * @param token Token to free, as an untyped pointer (borrowed).
 */
void	token_free_void(void *token);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

void	token_pool_init(t_token_pool *pool);
t_error	token_pool_deep_dup(void *dst, const void *src);
void	token_pool_clear(t_token_pool *pool);
void	token_pool_free(t_token_pool *pool);
void	token_pool_free_void(void *pool);

/* -------------------- OPS -------------------- */

/**
 * @ingroup token
 * @brief Deep copies @p src into @p dst: duplicates the value string,
 *        deep-copies the context stack, and copies the type, index span and
 *        assignment offset, leaving @p src untouched.
 *
 * @warning @p dst must be initialized with @ref token_init and empty: the
 *          value string of @p dst is overwritten without being freed, and
 *          the copied context items are appended to its context stack.
 * @param dst Destination token, already initialized by the caller; its
 *            value string is initialized by the function (borrowed).
 * @param src Source token (borrowed, read-only).
 * @return @c ERR_LIBC if a duplication fails, @c ERR_INDEX_OUT_OF_BOUND if
 *         a context item lookup fails, @c ERR_NO on success.
 */
t_error	token_dup(t_token *dst, const t_token *src);
t_error	token_dup_void(void *dst, const void *src);

t_error	token_pool_push(t_token_pool *pool, t_token *token);

t_token	*token_pool_get(const t_token_pool *pool, size_t index);

void	token_pool_take(t_token_pool *pool, size_t index, t_token *dst);

t_error	token_pool_transfer(t_token_pool *dst, t_token_pool *src, size_t index);

void	token_transfer(t_token *dst, t_token *src);

#endif
