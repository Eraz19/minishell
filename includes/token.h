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
	NONE,			/**< Unset / placeholder type. */
	TOKEN,			/**< A word token (command name, argument, ...). */
	NEWLINE_,		/**< A newline. */
	SCOLON,			/**< ';' command separator. */
	AMPERSAND,		/**< '&' background / async operator. */
	DSEMI,			/**< ';;' case-list terminator. */
	SEMI_AND,		/**< ';&' case fall-through terminator. */
	AND_IF,			/**< '&&' logical AND. */
	OR_IF,			/**< '||' logical OR. */
	PIPE,			/**< '|' pipe. */
	LPARENTHESIS,	/**< '(' subshell open. */
	RPARENTHESIS,	/**< ')' subshell close. */
	LESSAND,		/**< '<&' duplicate input descriptor. */
	GREATAND,		/**< '>&' duplicate output descriptor. */
	LESS,			/**< '<' input redirection. */
	GREAT,			/**< '>' output redirection. */
	CLOBBER,		/**< '>|' forced output redirection. */
	LESSGREAT,		/**< '<>' open for reading and writing. */
	DGREAT,			/**< '>>' appending output redirection. */
	DLESS,			/**< '<<' here-document. */
	DLESSDASH,		/**< '<<-' tab-stripped here-document. */
	IO_NUMBER,		/**< A number immediatly followed by redirection operator */
	EOF_			/**< End of input. */
}	t_token_type;

/**
 * @ingroup token
 * @struct s_token
 * @brief A grammar type paired with the raw text it was scanned from.
 *
 * @var s_token::type Grammar type of the token.
 * @var s_token::value Owned, growable buffer holding the token text.
 * @var s_token::contexts Expansion constructs found in the value, in appearance
 *                        order, each with its [start, end) range; owns its
 *                        items.
 */
typedef struct s_token
{
	t_token_type	type;
	t_buff			value;
	t_context_stack	contexts;
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
