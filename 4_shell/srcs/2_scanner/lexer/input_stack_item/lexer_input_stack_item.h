#ifndef INPUT_STACK_ITEM_H
# define INPUT_STACK_ITEM_H

# include "libft.h"

/* ************************************************************************* */
/*                                  TYPES                                    */
/* ************************************************************************* */

/**
 * @ingroup lexer
 * @struct s_lexer_input_stack_item
 * @brief One input the lexer reads from: its text and read cursor.
 *
 * @var s_lexer_input_stack_item::i Offset of the next unread character in
 *                                  @c str.
 * @var s_lexer_input_stack_item::str Input text (owned).
 * @var s_lexer_input_stack_item::alias_position_exempt True when the
 *      previous alias expansion ended with a blank: the next word lexed
 *      from this input is checked for alias substitution even outside a
 *      command-word position (POSIX 2.3.1). Consumed (cleared) by the
 *      check of that one word.
 */
typedef struct s_lexer_input_stack_item
{
	size_t		i;
	t_string	str;
	bool		alias_position_exempt;
}	t_lexer_input_stack_item;

/* ************************************************************************* */
/*                                LIFE_CYCLE                                 */
/* ************************************************************************* */

/**
 * @ingroup lexer
 * @brief Zeroes @p item and initializes its text as an empty string.
 *
 * @param item Item to initialize; initialized by the function (borrowed).
 */
void	lexer_input_stack_item_init(t_lexer_input_stack_item *item);

/**
 * @ingroup lexer
 * @brief Frees the item text and resets the cursor state.
 *
 * @note Takes @c void* so it can serve as the free callback of the input
 *       stack vector.
 *
 * @param item Already initialized @ref t_lexer_input_stack_item (borrowed).
 */
void	lexer_input_stack_item_free(void *item);

#endif
