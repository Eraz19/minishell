#ifndef WORD__H
# define WORD__H

# include "error.h"
# include "libft.h"
# include "context.h"

/** @defgroup expander_word Expander word
 *  @brief The expander's working representation: a word is a sequence of
 *         annotated characters, each carrying the quoting and construct
 *         metadata the expansion stages decide on.
 */

// Forward type
typedef t_vector	t_fields;

/**
 * @ingroup expander_word
 * @typedef t_word
 * @brief One word as a @ref t_vector of @ref s_word_item values.
 */
typedef t_vector	t_word;

/**
 * @ingroup expander_word
 * @struct s_word_item_opt
 * @brief Metadata of one word character.
 *
 * @var s_word_item_opt::i Offset of the character in the original raw
 *                         word (used for position rules such as the
 *                         tilde prefix).
 * @var s_word_item_opt::quoted Enclosing quoting context
 *                              (@c CONTEXT_NONE when unquoted; only
 *                              quoting contexts and @c CONTEXT_HEREDOC
 *                              are kept, see @ref word_item_init).
 * @var s_word_item_opt::context Expansion construct the character
 *                               belongs to (@c CONTEXT_PARAM, ...),
 *                               @c CONTEXT_NONE for plain text.
 * @var s_word_item_opt::escaped Whether the character was escaped by a
 *                               backslash.
 * @var s_word_item_opt::context_len Length in items of the construct
 *                                   starting at this character
 *                                   (delimiters included).
 * @var s_word_item_opt::local_quoted Innermost quoting at the character
 *                                    (inside nested constructs), used by
 *                                    the pattern-based operators.
 * @var s_word_item_opt::is_expand_res Whether the character was produced
 *                                     by an expansion: it is never
 *                                     rescanned for substitution.
 */
typedef struct s_word_item_opt
{
	size_t		i;
	t_context	quoted;
	t_context	context;
	bool		escaped;
	size_t		context_len;
	t_context	local_quoted;
	bool		is_expand_res;
}	t_word_item_opt;

/**
 * @ingroup expander_word
 * @struct s_word_item
 * @brief One annotated word character.
 *
 * @var s_word_item::c The character.
 * @var s_word_item::opt Its metadata.
 */
typedef struct s_word_item
{
	char			c;
	t_word_item_opt	opt;
}	t_word_item;

/* ************************************************************************* */
/*                                LIFE_CYCLE                                 */
/* ************************************************************************* */

/**
 * @ingroup expander_word
 * @brief Initializes @p word as an empty word.
 *
 * @param word Word initialized by the function (borrowed).
 */
void		word_init(t_word *word);

/**
 * @ingroup expander_word
 * @brief Frees the storage of @p word (items hold no owned resources).
 *
 * @param word Already initialized word (borrowed).
 */
void		word_free(t_word *word);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup expander_word
 * @brief Deep-copies @p src into @p out.
 *
 * @param out Word initialized by the function (borrowed).
 * @param src Word to copy (borrowed, read-only).
 * @return @c ERR_LIBC if the copy fails, @c ERR_NO on success.
 */
t_error		word_dup(t_word *out, t_word *src);

/**
 * @ingroup expander_word
 * @brief Removes the first item of @p word and hands it to the caller.
 *
 * @param out Set to the removed item (borrowed).
 * @param word Already initialized word (borrowed).
 * @return @c ERR_EMPTY_STACK if @p word is empty, @c ERR_LIBC if the
 *         removal fails, @c ERR_NO on success.
 */
t_error		word_fpop(t_word_item *out, t_word *word);

/**
 * @ingroup expander_word
 * @brief Reads the item at @p index without removing it.
 *
 * @param out Set to a copy of the item (borrowed).
 * @param word Already initialized word (borrowed, read-only).
 * @param index Position of the item to read.
 * @return @c ERR_EMPTY_STACK if @p word is empty,
 *         @c ERR_INDEX_OUT_OF_BOUND if @p index is past the last item,
 *         @c ERR_NO on success.
 */
t_error		word_get(t_word_item *out, const t_word *word, size_t index);

/**
 * @ingroup expander_word
 * @brief Builds an item from @p c and @p opt, normalizing @c opt.quoted:
 *        anything that is not a quoting context or @c CONTEXT_HEREDOC
 *        becomes @c CONTEXT_NONE.
 *
 * @param c The character.
 * @param opt Its metadata.
 * @return The built item.
 */
t_word_item	word_item_init(char c, t_word_item_opt opt);

/**
 * @ingroup expander_word
 * @brief Appends @p item at the end of @p word.
 *
 * @param word Already initialized word (borrowed).
 * @param item Item to append (copied by value).
 * @return @c ERR_LIBC if the push fails, @c ERR_NO on success.
 */
t_error		word_push(t_word *word, t_word_item item);

/**
 * @ingroup expander_word
 * @brief Removes up to @p len items of @p word starting at @p start.
 *
 * @note Best-effort by design: removing past the end stops early and the
 *       function never reports a failure.
 * @param word Already initialized word (borrowed).
 * @param start Position of the first item to remove.
 * @param len Number of items to remove.
 * @return @c ERR_NO.
 */
t_error		word_remove(t_word *word, size_t start, size_t len);

/* ************************************************************************* */
/*                                CONVERTION                                 */
/* ************************************************************************* */

/**
 * @ingroup expander_word
 * @brief Builds a word from a C-string, tagging every item with @p opt.
 *
 * @param out Word initialized by the function (borrowed).
 * @param src Source text; NULL or empty yields an empty word
 *            (borrowed, read-only).
 * @param opt Metadata applied to every item.
 * @return @c ERR_LIBC if a push fails, @c ERR_NO on success.
 */
t_error		from_str(t_word *out, const t_string *src, t_word_item_opt opt);

/**
 * @ingroup expander_word
 * @brief Extracts @p len characters of @p src starting at @p start into a
 *        string.
 *
 * @param out String initialized by the function and freed on failure
 *            (borrowed).
 * @param src Source word (borrowed, read-only).
 * @param start Position of the first character to extract.
 * @param len Number of characters to extract.
 * @return @c ERR_INDEX_OUT_OF_BOUND if the range is out of @p src,
 *         @c ERR_LIBC on allocation failure, @c ERR_NO on success.
 */
t_error		to_str(t_string *out, const t_word *src, size_t start, size_t len);

#endif
