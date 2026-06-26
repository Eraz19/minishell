#ifndef TOKEN_H
# define TOKEN_H

# include "error.h"
# include "libft.h"
# include "context.h"

/** @defgroup token Token API
 *  @brief Lexical tokens produced by the scanner.
 *
 *  A token couples a grammar type with the raw text that produced it. The
 *  text lives in an owned, growable buffer, so a token owns its value and
 *  token_dup() hands out an independent deep copy.
 *
 *  A word token also carries the expansion constructs found while scanning it
 *  (${ }, $(( )), ` `), in the left-to-right order their openings appeared, each
 *  marked with its [start, end) range inside the value buffer, so the expansion
 *  phase can locate every construct without rescanning the word.
 */

/**
 * @ingroup token
 * @enum e_token_type
 * @brief Grammar type of a token, using the POSIX shell token names.
 */
typedef enum e_token_type
{
	TOKEN_NONE,			/**< Unset / placeholder type. */
	TOKEN_TOKEN,		/**< A word token (command name, argument, ...). */
	TOKEN_NEWLINE,		/**< A newline. */
	TOKEN_SCOLON,		/**< ';' command separator. */
	TOKEN_AMPERSAND,	/**< '&' background / async operator. */
	TOKEN_DSEMI,		/**< ';;' case-list terminator. */
	TOKEN_SEMI_AND,		/**< ';&' case fall-through terminator. */
	TOKEN_AND_IF,		/**< '&&' logical AND. */
	TOKEN_OR_IF,		/**< '||' logical OR. */
	TOKEN_PIPE,			/**< '|' pipe. */
	TOKEN_LPARENTHESIS,	/**< '(' subshell open. */
	TOKEN_RPARENTHESIS,	/**< ')' subshell close. */
	TOKEN_LESSAND,		/**< '<&' duplicate input descriptor. */
	TOKEN_GREATAND,		/**< '>&' duplicate output descriptor. */
	TOKEN_LESS,			/**< '<' input redirection. */
	TOKEN_GREAT,		/**< '>' output redirection. */
	TOKEN_CLOBBER,		/**< '>|' forced output redirection. */
	TOKEN_LESSGREAT,	/**< '<>' open for reading and writing. */
	TOKEN_DGREAT,		/**< '>>' appending output redirection. */
	TOKEN_DLESS,		/**< '<<' here-document. */
	TOKEN_DLESSDASH,	/**< '<<-' tab-stripped here-document. */
	TOKEN_IO_NUMBER,	/**< Solely digits and the delimiter character is '<' or '>' */
	TOKEN_IO_LOCATION,	/**< At least three characters, begins with '{' and ends '}', and the delimiter character is '<' or '>' */
	TOKEN_EOF			/**< End of input. */
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	t_buff			value;
	t_context_stack	contexts;
	ssize_t			assignment_offset;
}	t_token;

/**
 * @ingroup token
 * @brief Initialises a token to an empty word with an empty value buffer.
 *
 * @param token Pointer to the token to initialise (borrowed).
 */
void	token_init(t_token *token);

/**
 * @ingroup token
 * @brief Frees the token's value buffer and resets it to zero.
 *
 * @param token Pointer to the token to free (borrowed).
 */
void	token_free(t_token *token);

// TODO: doc
// @note used for vector_free() compatibility
void	token_free_void(void *token);

/**
 * @ingroup token
 * @brief Deep copies a token into another.
 *
 * Duplicates @p src's value buffer and deep-copies its context list into
 * @p dst, and copies its type, so @p dst owns an independent copy and @p src is
 * left untouched.
 *
 * @param dst Destination token receiving the copy (borrowed).
 * @param src Source token to copy (borrowed).
 * @return ERR_NO on success, ERR_LIBC on allocation failure.
 */
t_error	token_dup(t_token *dst, t_token *src);

#endif
