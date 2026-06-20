/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_word_.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 10:23:27 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/19 15:34:27 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_WORD__H
# define EXPANDER_WORD__H

# include "error.h"
# include "libft.h"
# include "context.h"

typedef t_vector	t_expander_word;

typedef struct s_expander_word_item
{
	char		c;
	t_context	quoted;
	t_context	context;
	bool		is_expand_res;
}	t_expander_word_item;

void					expander_word_init(t_expander_word *word);
void					expander_word_free(t_expander_word *word);
t_expander_word_item	expander_word_item_init(char c, t_context quoted,
							t_context context, bool is_expand_res);

t_error					expander_word_peek(t_expander_word *word,
							t_expander_word_item *item);
t_error					expander_word_push(t_expander_word *word,
							t_expander_word_item item);
t_error					expander_word_pop(t_expander_word *word,
							t_expander_word_item *item);
t_error					expander_word_dup(t_expander_word *dst,
							t_expander_word *src);

#endif
	