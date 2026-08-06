/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:23:21 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 12:23:22 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# include "history_file.h"
# include "history_adapter.h"

/* ************************************************************************* */
/*                                  TYPES                                    */
/* ************************************************************************* */

typedef struct s_history
{
	t_error				err;
	t_history_file		file;
	t_history_list		list;
	t_history_adapter	adapter;
	t_string			current_input;
}	t_history;

/* ************************************************************************* */
/*                                LIFE_CYCLE                                 */
/* ************************************************************************* */

void	history_init(t_history *state);

t_error	history_load(t_history *state);

void	history_free(t_history *state);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

t_error	history_save(void);

t_error	history_save_entry(void);

t_error	history_append_to_entry(t_string *entry);

#endif
