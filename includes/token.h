/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 15:32:15 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/16 14:41:48 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
 *  A word token also carries a queue of the quoting/expansion constructs found
 *  while scanning it, each marked with its [start, end) range inside the value
 *  buffer, so the expansion phase can locate every construct without rescanning
 *  the word.
 */

/**
 * @ingroup token
 * @brief Queue of expansion constructs found in a token, in left-to-right order
 *        (a vector of t_token_context_queue_item).
 */
typedef t_vector	t_token_context_queue;

/**
 * @ingroup token
 * @struct s_token_context_queue_item
 * @brief One expansion construct located inside a token's value buffer.
 *
 * @var s_token_context_queue_item::end Index one past the construct's last
 *                                      character in the token value.
 * @var s_token_context_queue_item::start Index of the construct's first
 *                                        character in the token value.
 * @var s_token_context_queue_item::context Which construct it is (PARAM, ARITH,
 *                                          BACKTICK or CMD_SUB).
 */
typedef struct s_token_context_queue_item
{
	size_t		end;
	size_t		start;
	t_context	context;
}	t_token_context_queue_item;

/**
 * @ingroup token
 * @brief Initialises an empty context queue.
 * @param queue Pointer to the queue to initialise (borrowed).
 */
void	token_context_queue_init(t_token_context_queue *queue);

/**
 * @ingroup token
 * @brief Frees the context queue (its items are plain values).
 * @param queue Pointer to the queue to free (borrowed).
 */
void	token_context_queue_free(t_token_context_queue *queue);

/**
 * @ingroup token
 * @brief Removes the front (oldest) construct from the queue.
 *
 * @param queue Pointer to the queue (borrowed).
 * @param item Out-parameter receiving the removed item.
 * @return ERR_NO on success, ERR_LIBC if the queue is empty.
 */
t_error	token_context_queue_pop(t_token_context_queue *queue,
			t_token_context_queue_item *item);

/**
 * @ingroup token
 * @brief Appends a construct's range and kind to the back of the queue.
 *
 * @param queue Pointer to the queue (borrowed).
 * @param start Index of the construct's first character in the token value.
 * @param end Index one past its last character in the token value.
 * @param context Which construct it is (PARAM, ARITH, BACKTICK or CMD_SUB).
 * @return ERR_NO on success, ERR_LIBC on allocation failure.
 */
t_error	token_context_queue_push(t_token_context_queue *queue, size_t start,
			size_t end, t_context context);

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
	EOF_			/**< End of input. */
}	t_token_type;

/**
 * @ingroup token
 * @struct s_token
 * @brief A grammar type paired with the raw text it was scanned from.
 *
 * @var s_token::type Grammar type of the token.
 * @var s_token::value Owned, growable buffer holding the token text.
 * @var s_token::contexts Queue of the expansion constructs found in the value,
 *                        each with its [start, end) range (owned).
 */
typedef struct s_token
{
	t_token_type			type;
	t_buff					value;
	t_token_context_queue	contexts;
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
 * Duplicates @p src's value buffer into @p dst and copies its type, so @p dst
 * owns an independent copy and @p src is left untouched.
 *
 * @param dst Destination token receiving the copy (borrowed).
 * @param src Source token to copy (borrowed).
 * @return ERR_NO on success, ERR_LIBC on allocation failure.
 */
t_error	token_dup(t_token *dst, t_token *src);

#endif
