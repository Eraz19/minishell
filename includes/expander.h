/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 12:32:43 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/16 15:49:08 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "error.h"
# include "libft.h"
# include "token.h"

typedef enum e_expander_phase
{
	ALL,
	QUOTE_REMOVE_ONLY,
}	t_expander_mode;

typedef struct s_expander
{
	t_token		token;
	t_vector	words;
}	t_expander;

void	expander_init(t_expander *expander);
void	expander_free(t_expander *expander);
t_error	expander_load(t_expander *expander, t_token token);

t_error	expander_push(t_expander *state, char *word);
t_error	expander_get(t_expander *state, char **result,  size_t index);

t_error	expander_word(t_expansion *expansion, t_token token,
			t_expander_mode mode);

#endif
