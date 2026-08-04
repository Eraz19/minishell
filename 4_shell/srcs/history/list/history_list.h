/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_list.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:08:56 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 17:33:19 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_LIST_H
# define HISTORY_LIST_H

# include "error.h"
# include "libft.h"

/* ************************************************************************* */
/*                                  TYPES                                    */
/* ************************************************************************* */

typedef t_vector	t_history_list;

/* ************************************************************************* */
/*                                LIFE_CYCLE                                 */
/* ************************************************************************* */

void	history_list_init(t_history_list *list);

void	history_list_free(t_history_list *list);

t_error	history_list_load(
			t_history_list *history_list,
			t_vector *entries,
			size_t start);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

t_error	history_list_push(t_history_list *list, const t_string *item);

void	history_list_get(t_history_list *list, const t_string **item, size_t i);

#endif
