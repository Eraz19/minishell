/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_substitutions.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 15:38:23 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/15 16:05:47 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_SUBSTITUTIONS_H
# define EXPANDER_SUBSTITUTIONS_H

# include "error.h"
# include "libft.h"

typedef struct s_expander_substitutions
{
	size_t	i;
	t_error	err;
	char	*word;
	bool	reached_EOW;
}	t_expander_substitutions;

t_error	expander_substitutions(char **expanded_word, char *word);

#endif
