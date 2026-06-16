/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 12:32:43 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/15 23:19:12 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "error.h"
# include "libft.h"

typedef enum e_expander_phase
{
	ALL,
	QUOTE_REMOVE_ONLY,
}	t_expander_mode;

typedef t_vector	t_expansion;

void	expander_init(t_expansion *expansion);
void	expander_free(t_expansion *expansion);
t_error	expander_load(t_expansion *expansion, char *word);

t_error	expander_push(t_expansion *expansion, char *word);
t_error	expander_get(t_expansion *expansion, char **result,  size_t index);

t_error	expander_word(t_expansion *expansion, char *word, t_expander_mode mode);

#endif
