/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_forbidden_internal.h                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:14:33 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 14:14:34 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALIAS_FORBIDDEN_INTERNAL_H
# define ALIAS_FORBIDDEN_INTERNAL_H

# include "libft.h"
# include "error.h"

typedef t_hashmap	t_alias_forbidden;

// life cycle

void	alias_forbidden_init(t_alias_forbidden *forbidden);
void	alias_forbidden_clear(t_alias_forbidden *forbidden);
void	alias_forbidden_free(t_alias_forbidden *forbidden);

// ops

t_error	alias_forbidden_set(
			t_alias_forbidden *forbidden,
			const char *name);
bool	alias_forbidden_contains(
			const t_alias_forbidden *forbidden,
			const char *name);
void	alias_forbidden_pop(t_alias_forbidden *forbidden);

#endif
