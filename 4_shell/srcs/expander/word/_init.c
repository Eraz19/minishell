/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:48:17 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 17:48:18 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "word_.h"
#include "context.h"

void	word_init(t_word *word)
{
	vector_init(word, sizeof(t_word_item), 0);
}

void	word_free(t_word *word)
{
	vector_free(word, NULL);
}

t_word_item	word_item_init(char c, t_word_item_opt opt)
{
	t_word_item	item;

	item.c = c;
	if (!is_context_quoting(opt.quoted) && opt.quoted != CONTEXT_HEREDOC)
		opt.quoted = CONTEXT_NONE;
	item.opt = opt;
	return (item);
}
