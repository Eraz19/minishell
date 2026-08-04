/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_adapter.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:08:21 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 17:24:26 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_ADAPTER_H
# define HISTORY_ADAPTER_H

# include "history_list.h"

/* ************************************************************************* */
/*                                  TYPES                                    */
/* ************************************************************************* */

typedef struct s_history_adapter
{
	t_error	err;
	ssize_t	max;
	size_t	count;
}	t_history_adapter;

/* ************************************************************************* */
/*                                LIFE_CYCLE                                 */
/* ************************************************************************* */

void	history_adapter_init(t_history_adapter *history_adapter);

void	history_adapter_free(t_history_adapter *history_adapter);

void	history_adapter_load(
			t_history_adapter *history_adapter,
			t_history_list *history_list);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

void	add_to_readline_history(
			t_history_adapter *history_adapter,
			t_history_list *history_list, size_t count);

#endif
